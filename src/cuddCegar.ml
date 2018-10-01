(**
   - We forbid negative values of discrete variables since their encoding is cumbersome
   - Only sum and subtraction are implemented; no multiplication and division. We do not check whether
     we are subtracting X - Y with X >= Y. If this does not hold then
     the result is meaningless. Use care and put guards when using subtraction.
   - We have to enumarate all firable transitions either internal or synchronized ones.
     A large number of synchronizing pairs, even unreachable, can mean inefficient or unfeasible analysis.

   - TODO Reject models with simultaneous updates to same variable during sync transitions
          This would be executed by Uppaal sequentially while their transition relation would be conjoined
          in BDD algorithms

   - Possible Optimizations
   1) Use partitioned reset constraint. That would be meaningful for large number of clock predicate

   2) Use early quantification in compute_next_discrete
      Evaluate the cost of the image computation with local transitions

   3) After refinements:
       Reduce and reset constraints can be updated without computing all from scratch
*)
open Pdbm
open Common
open TimedAutomaton
open ClockPredicateAbstraction
open RobustReach
open ExactReach
open Batteries
open Printf
open Uta
open Cudd
open Uautomaton
open Str

open CuddEncoding

module Dbm = Pdbm.Guard
module CPA = ClockPredicateAbstraction

(** Some additional helper functions on TA semantics. *)
module TASemantics =
struct

  let guard_to_dbm bta g =
    let dbm  = Dbm.create ((nb_clocks bta)) in
    let aux = function
      | GuardLeq(Clock(c), Constant k) ->
        Dbm.assign_constraint dbm c 0 (Dbm.Alg.weak_from_int k)
      | GuardLess(Clock(c), Constant k) ->
        Dbm.assign_constraint dbm c 0 (Dbm.Alg.strict_from_int k)
      | GuardGeq(Clock(c), Constant k) ->
        Dbm.assign_constraint dbm 0 c (Dbm.Alg.weak_from_int (-k))
      | GuardGreater(Clock(c), Constant k) ->
        Dbm.assign_constraint dbm 0 c (Dbm.Alg.strict_from_int (-k))
      | GuardEqual(Clock(c), Constant k) ->
        Dbm.assign_constraint dbm 0 c (Dbm.Alg.weak_from_int (-k));
        Dbm.assign_constraint dbm c 0 (Dbm.Alg.weak_from_int k)

      (* diagonal guards *)
      | GuardLeq(Subtraction(Clock(c1), Clock(c2)), Constant k) ->
        Dbm.assign_constraint dbm c1 c2 (Dbm.Alg.weak_from_int k)
      | GuardLess(Subtraction(Clock(c1), Clock(c2)), Constant k) ->
        Dbm.assign_constraint dbm c1 c2 (Dbm.Alg.strict_from_int k)
      | GuardGreater(Subtraction(Clock(c1), Clock(c2)), Constant k) ->
        Dbm.assign_constraint dbm c2 c1 (Dbm.Alg.strict_from_int (-k))
      | GuardGeq(Subtraction(Clock(c1), Clock(c2)), Constant k) ->
        Dbm.assign_constraint dbm c2 c1 (Dbm.Alg.weak_from_int (-k))
      | GuardEqual(Subtraction(Clock(c1), Clock(c2)), Constant k) ->
        Dbm.assign_constraint dbm c2 c1 (Dbm.Alg.weak_from_int (-k));
        Dbm.assign_constraint dbm c1 c2 (Dbm.Alg.weak_from_int k)

      | _ as e -> failwith (sprintf "Bad Guard: %s" (string_of_guard bta [e]))
    in
    List.iter aux g;
    Dbm.reduce dbm;
    dbm

  let dbm_guard_of_edge bta e =
    guard_to_dbm bta e.edgeGuard

  let dbm_invariant_of_state = invariant_of_discrete_state

  let dbm_guard_of_trans bta = function
    | Single(e) -> dbm_guard_of_edge bta e
    | Pair(e1,e2) ->
      let d = dbm_guard_of_edge bta e1 in
      Dbm.intersect d (dbm_guard_of_edge bta e2);
      d

  let rec is_transition_committed ta = function
    |Single e1 -> ta.procs.(e1.edgeProc).procLocations.(e1.edgeSource).locCommitted
    |Pair(e1,e2) ->
      ta.procs.(e1.edgeProc).procLocations.(e1.edgeSource).locCommitted
      ||
      ta.procs.(e2.edgeProc).procLocations.(e2.edgeSource).locCommitted

  let get_resets = function
    |Single e1 -> ClockSet.elements e1.edgeReset
    |Pair(e1,e2) ->
      ClockSet.union e1.edgeReset e2.edgeReset
      |> ClockSet.elements

  let print_transition_pair ta =function
    |Single trans ->
      printf "%s\n" (string_of_edge ta trans)
    |Pair (t1,t2) ->
      printf "%s\n" (string_of_edge ta t1);
      printf "%s\n" (string_of_edge ta t2)

end


(** Model checker module: CEGAR with CUDD *)
module MC =
struct

  type t =
    {
      mutable mc_transitions : (edge single_or_pair * Bdd.dt * Bdd.dt * int list) Queue.t option
    }

  (** A symbolic path is a list of symbolic_state which is a pair made of
      1) the last operation applied
      2) current state
      so that the last operation has led to the current state.
      The operations are time up, or reset of given clock through an edge(s).
      A tau-transition along an edge e=(l,g,[r1;r2;r3),l') is encoded as follows (provided l not committed or urgent)

      Sym_Edge(l,(Single e), Some r1, false)
      Sym_Reset(l, (Single e), r2, false)
      Sym_Reset(l, (Single e), r3, true)
      Sym_Up(l,true)

      The last boolean being a flag indicating the last reset so that the invariant can be applied
  *)
  type symbolic_transition =
      Sym_Up of discrete_state * bool (* current location and whether time can elapse *)
    | Sym_Edge of discrete_state * edge single_or_pair * (clock_t option) * bool
    | Sym_Reset of discrete_state * edge single_or_pair * clock_t * bool


  let string_of_symbolic_transition bta =
    let string_of_clock_option = function
      None -> ""
      | Some(x) -> sprintf "%d" x
    in
    function
    | Sym_Up(loc, b) ->
      sprintf "%s\nUp(%b)" (string_of_state bta loc) b
    | Sym_Edge(lar, (Single e),res, b) ->
      sprintf "TAU: %s | Resetting <%s> | Last: %b\n%s\n"
        (string_of_edge bta e) (string_of_clock_option res)
        b          (string_of_state bta lar)

    | Sym_Edge(lar, Pair(e1,e2),res, b) ->
      sprintf "SYNC:\n%s\n%s\n\t| Resetting <%s> | Last: %b\n%s\n"
        (string_of_edge bta e1)  (string_of_edge bta e2) (string_of_clock_option res) b
         (string_of_state bta lar)
    | Sym_Reset(loc, edge, i, b) ->
      sprintf "Resetting: %d | Last: %b" i b


  let string_of_clock_constraint clocks (x,y,b) =
    sprintf "%s - %s %s"
      (VarContext.index2var clocks x)
      (VarContext.index2var clocks y)
      (Dbm.Alg.to_string b)

  let string_of_symbolic_path bta (init, path) =
    let buf = Buffer.create 1024 in
    let c = ref 1 in
    Buffer.add_string buf (sprintf "INIT STATE 0\n");
    let init_loc, init_ccl = init in
    Buffer.add_string buf (sprintf "%s\n"
                         (string_of_state bta init_loc)
                         (*
                         (Dbm.to_string (Dbm.from_constraints (nb_clocks bta) init_ccl))
                            *)
                      );
    List.iter (fun ccl ->
        Buffer.add_string buf (string_of_clock_constraint bta.clocks ccl);
        Buffer.add_string buf " /\\ "
      ) init_ccl;
    printf "\n";
    Buffer.add_string buf "\n";
    List.iter
      (fun (trans, constr) ->
         Buffer.add_string buf (sprintf "\nm\nSTATE %d:\n" !c);
         incr c;
         Buffer.add_string buf (string_of_symbolic_transition bta trans);
         Buffer.add_string buf "\n";
         List.iter (fun ccl ->
             Buffer.add_string buf (string_of_clock_constraint bta.clocks ccl);
             Buffer.add_string buf " /\\ "
           ) constr;
         printf "\n";
         (*
         Buffer.add_string buf (sprintf  "%s\n\n" (Dbm.to_string (Dbm.from_constraints (nb_clocks bta) constr)))
            *)
      ) path;
    Buffer.contents buf

  (* Just recompute the list of transitions by recomputing the clock guards *)
  let update_transitions enc trans =
    Queue.map
      (fun (tr,trbdd,_,resets) ->
         let grd =
           (match tr with
              Single(edge) ->
              Encoding.bdd_of_clock_guard enc edge.edgeGuard
            | Pair(e1,e2) ->
              Bdd.dand
              (Encoding.bdd_of_clock_guard enc e1.edgeGuard)
              (Encoding.bdd_of_clock_guard enc e2.edgeGuard)
           )
         in
         (tr,trbdd,grd,resets)
      ) trans

  (** Return a queue of all possible transitions and their bdds in the ta (single or pair).
      We filter out transitions with unsatisfiable clock guards
  *)
  let find_all_transitions enc =
    let ta = enc.Encoding.enc_ta in
    let edges = Queue.create() in
    let send_edges = Hashtbl.create 1000 in
    let recv_edges = Hashtbl.create 1000 in
    Array.iter
      (fun proc ->
         Array.iter
           (fun loc ->
              List.iter (fun edge ->
                  match edge.edgeSync with
                  | None ->
                    (try
                      ignore(TASemantics.guard_to_dbm ta edge.edgeGuard);
                      let disc_rel, guard = Encoding.bdd_of_disc_transition enc (Single edge) in
                      Queue.add
                        ((Single edge),
                         disc_rel,
                         guard,
                         ClockSet.elements edge.edgeReset
                        )
                        edges;
                    with EmptyDBM -> ());
                      (*
                    printf "Computing\n";
                    print_transition_pair enc.Encoding.enc_ta (Single edge);
                    let trb = (Encoding.bdd_of_disc_transition enc (Single edge)) in
                    print_bdd trb;
                    printf "\n";
                    let loc = Encoding.discrete_state_of_cube enc trb in
                    print_discrete_state stdout enc.Encoding.enc_ta loc
                         *)
                  | Some(Uta.SendChan(c)) ->
                    Hashtbl.add send_edges c edge
                  | Some(Uta.RecvChan(c)) ->
                    Hashtbl.add recv_edges c edge
                ) loc.locEdges
           )
           proc.procLocations
      ) ta.procs;
    Log.debug (sprintf "Computing transitions from %d internal, %d send, and %d recv transitions.\n"
      (Queue.length edges)
      (Hashtbl.length send_edges)
      (Hashtbl.length recv_edges));
    Hashtbl.keys send_edges
    |> Enum.iter
      (fun c ->
         let cr = Hashtbl.find_all recv_edges c in
         let cs = Hashtbl.find_all send_edges c in
         Enum.cartesian_product (List.enum cr) (List.enum cs)
         |>
         Enum.iter (fun (e1,e2) ->
             try
               ignore(TASemantics.dbm_guard_of_trans ta (Pair(e1,e2)));
               let disc_rel, guard = Encoding.bdd_of_disc_transition enc (Pair (e1,e2)) in

               Queue.add (
                 (Pair (e1,e2)),
                 disc_rel,
                 guard,
                 TASemantics.get_resets (Pair (e1,e2))
               ) edges
             with EmptyDBM -> ()
           )
      );
    edges

    let get_up_rel enc =
      let open Encoding in
      let res = ref(Bdd.dtrue enc.enc_man) in
      let nclocks = nb_clocks enc.enc_ta in 
      for x = 1 to nclocks -1 do
        DynArray.iter (fun k ->
            (* ~p(x-0<k) --> ~p'(x-0<k) *)
            res :=
              Bdd.dand !res
                (
                  Bdd.dor
                    (get_clock_literal enc x 0 k)
                    (Bdd.dnot (get_clock_literal ~primed:true enc x 0 k))
                )
          ) enc.enc_cpa.(x).(0)
      done;
      for x = 1 to nclocks -1 do
        for y = 1 to nclocks-1 do
          if x<> y then (
            DynArray.iter (
              fun k->
                (* p(x-y<k) <-> p'(x-y<k) *)
                res := Bdd.dand !res
                    (Bdd.eq
                       (get_clock_literal enc x y k)
                       (get_clock_literal ~primed:true enc x y k)
                    )
            ) enc.enc_cpa.(x).(y)
          )
        done
      done;
      !res


    (* Cube of all constraints related to given clock *)
    let get_free_cube enc =
      let open Encoding in
      let cc2var = snd enc.enc_clock_predicates in
      let nclocks = nb_clocks enc.enc_ta in
      Enum.map
        (fun i ->
           Enum.map
             (fun j ->
                if i = j then Bdd.dtrue enc.enc_man
                else (
                  Hashtbl.fold
                    (fun _ var acc ->
                       Bdd.dand acc var
                    ) cc2var.(i).(j)
                    (Bdd.dtrue enc.enc_man)
                  |>
                  Hashtbl.fold
                    (fun _ var acc ->
                       Bdd.dand acc var
                    ) cc2var.(j).(i)
                )
             ) (0--(nclocks-1))
           |> List.of_enum
           |> Bdd.dand_of_list enc.enc_man
        )
        (0--((nclocks)-1))
      |> Array.of_enum



    (** Constraint R(z) such that Free_z(states) /\ R(z) gives
      the reset of z in states.
      Gives the relation if rel is set to true.
      Use get_reset_relation for this
  *)
  let get_reset_constraint ?rel:(rel=false) enc z =
    let open Encoding in
    let result = ref(Bdd.dtrue enc.enc_man) in
    let preds = enc.enc_cpa in
    let nb_clocks = nb_clocks enc.enc_ta in
    DynArray.iter
      (fun k ->
         if (0,DBM_WEAK) <= k then (
           let constr = (get_clock_literal ~primed:rel enc z 0 k) in
           result := Bdd.dand !result constr
         )
      ) preds.(z).(0);
      for x = 1 to nb_clocks do
        if x <> z then (
          (* Conjunct 2 *)
          preds.(x).(z)
          |>
          DynArray.iter (fun k ->
              let lhs =
                ((DynArray.filter (fun l -> l <= k) preds.(x).(0))
                 |> DynArray.map (fun l -> get_clock_literal enc x 0 l)
                 |> DynArray.to_list
                 |> Bdd.dor_of_list enc.enc_man
                )
              in
              (* lhs is un primed and rhs is primed in the relation version *)
              let rhs = get_clock_literal ~primed:rel enc x z k in
              result := Bdd.dand !result
                  (Bdd.dor
                     (Bdd.dnot lhs)
                     rhs
                  );
            );
          (* Conjunct 3 *)
          let y = x in
          preds.(z).(y)
          |>
          DynArray.iter
            (fun k ->
               let lhs =
                 ((DynArray.filter (fun l -> l <= k) preds.(0).(y))
                  |> DynArray.map (fun l -> (get_clock_literal enc 0 y l))
                  |> DynArray.to_list
                  |> Bdd.dor_of_list enc.enc_man
                 )
               in
               let rhs = get_clock_literal ~primed:rel enc z y k in
               result := Bdd.dand !result
                   (Bdd.dor
                      (Bdd.dnot lhs)
                      rhs
                   );
               if k >= (0,DBM_WEAK) then (
                 result := Bdd.dand !result (get_clock_literal ~primed:rel enc z y k)
                     (*
                 fprintf out "\t\t\t& %s\n"
                   (next_of_lit (z,y,k))
                        *)
               );
            )
        );
      done;
    if rel then (
      for x = 0 to nb_clocks do
        for y = 0 to nb_clocks do
          if (x > y && x <> z && y <> z) then (
            preds.(x).(y)
            |> DynArray.iter (fun k ->
                result := Bdd.dand !result
                    (Bdd.eq
                       (get_clock_literal enc x y k)
                       (get_clock_literal ~primed:true enc x y k)
                    )
              )
          )
        done
      done
    );
    !result

  let get_reset_relation enc z =
    get_reset_constraint enc ~rel:true z

  let print_states enc states =
    let x = ref states in
    let count =  ref 0 in
    while not(Bdd.is_false !x) do
      let mt = (Bdd.pick_minterm !x) in
      incr(count);
      let p = Bdd.cube_of_minterm enc.Encoding.enc_man mt in
      try
        let dbm = Encoding.dbm_of_minterm enc mt in
        print_discrete_state stdout enc.Encoding.enc_ta (Encoding.discrete_state_of_cube enc p);
        (*
        printf "\n%s\n\n" (Dbm.to_string dbm);
           *)
        Encoding.print_clock_constraints enc p;
        printf "\n";
        x := Bdd.dand !x (Bdd.dnot p)
      with EmptyDBM ->
        printf "Following minterm is unsat:\n";
        Encoding.print_clock_constraint_mincube enc mt;
        raise EmptyDBM
    done

  let print_discrete_states enc states =
    let x = ref states in
    let count =  ref 0 in
    while not(Bdd.is_false !x) do
      let mt = (Bdd.pick_minterm !x) in
      incr(count);
      let p = Bdd.cube_of_minterm enc.Encoding.enc_man mt in
      print_discrete_state stdout enc.Encoding.enc_ta (Encoding.discrete_state_of_cube enc p);
      x := Bdd.dand !x (Bdd.dnot p)
    done;
    printf "\n"


  let check_all_satisfiable enc states =
    let x = ref states in
    let count =  ref 0 in
    while not(Bdd.is_false !x) do
      let mt = (Bdd.pick_minterm !x) in
      incr(count);
      let p = Bdd.cube_of_minterm enc.Encoding.enc_man mt in
      try
        ignore(Encoding.dbm_of_minterm enc mt);
        x := Bdd.dand !x (Bdd.dnot p)
      with EmptyDBM ->
        printf "Following minterm is unsat:\n";
        Encoding.print_clock_constraint_mincube enc mt;
        failwith ""
    done


  let check_all_included enc states dbm =
    let zones = Bdd.minterms enc.Encoding.enc_man states in
    Enum.iter
      (fun mt ->
           let d = Encoding.dbm_of_minterm enc mt in
           if not (Dbm.leq d dbm) then (
             printf "\nFollowing not included:\n";
             printf "%s\n\n in\n%s\n\n" (Dbm.to_string d)
             (Dbm.to_string dbm);
             failwith ""
           ) else (printf "."; flush stdout)

      ) zones

    let compute_reset ?reset_constraint_table enc =
      let open Encoding in
      let nclocks = nb_clocks enc.enc_ta in
      let reset_constraint_table = match reset_constraint_table with
          None ->
          Enum.map (get_reset_constraint enc) (0--(nclocks-1))
          |> Array.of_enum
        | Some(r) -> r
      in
      let free_cube = get_free_cube enc in
      fun ?do_reduce:(do_reduce=true) ri states ->
      let free = Bdd.exist free_cube.(ri) states in
      let result =
        Bdd.dand free reset_constraint_table.(ri)
      in
      if do_reduce  then
        apply_reduce enc result enc.enc_reduce
      else result


    let compute_discrete_next enc ?reset_constraint_table ~current_disc_state_cube ~committed ~reduce ~edges ~invariant states =
      let open Encoding in
      let apply_reset = match reset_constraint_table with
          Some(r) -> compute_reset ~reset_constraint_table:r enc
        | None -> compute_reset enc
      in
      let next = ref(Bdd.dfalse enc.enc_man) in
      Queue.iter
        (fun (trans, trans_rel, trans_grd, resets) ->
           (* If trans is not committed, then restrict to non-committed states *)
           let states =
             if not (TASemantics.is_transition_committed enc.Encoding.enc_ta trans) then (
               Bdd.dand states (Bdd.dnot committed)
             ) else states
           in
           let trans_bdd = Bdd.dand trans_rel trans_grd in
           (* TODO Use early quantification here *)
           let img =
             (Bdd.dand states trans_bdd)
             |> Bdd.exist current_disc_state_cube
             |> Encoding.unprime_locations_and_vars enc
           in
           (*
           printf "Applying following transitions:\n";
           TASemantics.print_transition_pair enc.enc_ta trans;
           printf "BDD contains following target state\n";
           let tgt_ds =
             trans_bdd
             |> Bdd.exist current_disc_state_cube
             |> Bdd.exist enc.enc_clock_cube
             |> Encoding.unprime_locations_and_vars enc
           in

           print_bdd tgt_ds;
           printf "\n";
           print_discrete_state stdout enc.enc_ta (Encoding.discrete_state_of_cube enc tgt_ds);
           printf "\n";
              *)
           (*
           printf "This ends in following location\n";
           print_discrete_state stdout enc.enc_ta (Encoding.discrete_state_of_cube enc img);
           printf "\n";
              *)
           if not(Bdd.is_false img) then (
             (*
             printf "By:\n";
             print_transition_pair enc.Encoding.enc_ta trans;
             printf "Trans_bdd:\n";
             print_bdd trans_bdd;
             printf "\n";

             printf "Image:\n";
             print_states enc img;
             printf "\n";
             print_bdd img;
             printf "\n";
                *)

             (* Apply Reset *)
             let img =
               List.fold_left
                 (fun acc rx ->
                    apply_reset ~do_reduce:false rx acc
                 ) img resets
             (* Apply invariant *)
               |> Bdd.dand invariant
             in
             next := Bdd.dor img !next
           )
        ) edges;
      apply_reduce enc !next reduce

    (* See Seshia, Bryant. CAV02
       Result is reduced
    *)
    let compute_up enc reduce time_can_pass =
      let open Encoding in
      let nclocks = nb_clocks enc.enc_ta in
      let up_preds = Queue.create () in
      let cc2bdd = snd enc.enc_clock_predicates in
      for x = 1 to nclocks -1 do
        Hashtbl.iter
          (fun b var ->
             Queue.add var up_preds
          )
          cc2bdd.(x).(0)
      done;
      fun states ->
        (* Apply up on states where time can pass, and
           take the union with states itself *)
        let states_up = Bdd.dand states time_can_pass in
        let res = ref states_up in
        Queue.iter
          (fun p ->
             let pos,neg = Bdd.cofactors (Bdd.topvar p) !res in
             res := Bdd.dor pos (Bdd.dand (Bdd.dnot p) neg);
          ) up_preds;
        res := Encoding.apply_reduce enc !res reduce;
        let ret = Bdd.dor states !res in
        ret


  type refinement_result = Refined | Genuine | CannotRefine

  module Refinement = struct
    (**
       Check whether the cex is realizable using zone computations.
       If not realizable, then add predicates so as to eliminate this cex.
       The alg. is as follows.

       Compute the zones representing the abstract states of the cex:

       AZ_0 --e_0--> AZ_1 --e_1--> ... --e_{n-1}--> AZn

       If AZ_i = empty for some i, then add predicates making sure the neg cycle
       in AZ_i is detected. CEX is spurious.

       Otherwise, compute the concrete successors along this trace:

       CZ_0 = vec(0), CZ_i = post_{e_i}(CZ_{i-1})

       If CZ_n != empty then the cex is realizable.
       Otherwise, let i be the min index such that CZ_i is empty.
       Define AZ_{i+1}' = AZ_{i+1}. We execute the following refinement procedure:

       for j = i downto 0 do
         refine abs so that
            abs(CZ_j) /\ abs(Pre(AZ_{j+1}')) = empty
            where Pre is the concrete pre operation
         set AZ_j' = AZ_j \ abs(Pre(AZ_{j+1}'))
       done

       The iterative refinement makes sure that the trace is entirely eliminated.

       N.B. We only abstract clock predicates currently. There is no predicate abstraction
       applied to the discrete variables (This can come later).

       @pre All invariants and guards are represented exactly in the abstraction
    *)
    let refine enc (cex_init_state, path) =
      let cex_init = snd cex_init_state in
      let debug_print_dbm dbm =
        if Dbm.is_empty dbm then printf "empty\n"
        else
          let dim = Dbm.dimension dbm in
          for i = 0 to dim -1 do
            for j = 0 to dim - 1 do
              printf "%s " (Dbm.Alg.to_string (Dbm.elementAt dbm i j));
              flush stdout;
            done;
            printf "\n"
          done
      in
      let open Encoding in
      let bta = enc.enc_ta in
      let exception BreakRefined of int in
      let exception BreakGenuine in
      let exception BreakCannotRefine in
      let path = Array.of_list path in
      let nclocks = (nb_clocks enc.enc_ta) - 1 in
      let npath= Array.length path in
      (* Zone successor through sym-action.
         Invariant is applied after the last reset
         and after time up
      *)
      let post (trans,_) dbm =
        let d = Dbm.copy dbm in
        (match trans with
           Sym_Up (ds, telapse) ->
           (* debug *)
           (*
           BTA.print_discrete_state Pervasives.stdout 
             bta {BTA.stateLocs = locs; BTA.stateVars = [||]};
           printf "\n";
              *)

           (*
           BTA.print_discrete_state Pervasives.stdout 
             bta {BTA.stateLocs = locs; BTA.stateVars = [||]};
           printf "\n";
              *)
           (* *)
           if telapse then (
             Dbm.posttime d;
             (* We can retrieve the invariant without the need
                to state vars since guards and invariants
                do not contain such expression *)
             let invar = TASemantics.dbm_invariant_of_state bta
                 ds
             in
             Dbm.intersect d invar;
           );

         | Sym_Edge(locs, edges, reset, flag_last) ->
           (* debug *)
           (*
           BTA.print_discrete_state Pervasives.stdout
             bta {BTA.stateLocs = locs; BTA.stateVars = [||]};
           printf "\n";
              *)
           (* *)
           Dbm.intersect d (TASemantics.dbm_guard_of_trans bta edges);
           (*
           (match edges with
              Pair(e1,e2) ->
              let g1 = TASemantics.dbm_guard_of_edge bta e1 in
              let g2 = TASemantics.dbm_guard_of_edge bta e2 in
              Dbm.intersect d g1;
              Dbm.intersect d g2;
            | Single(e1) ->
              let g = TASemantics.dbm_guard_of_edge bta e1 in
              Dbm.intersect d g;
           );
              *)
           (match reset with
              None -> ()
            | Some(x) -> Dbm.reset d (ClockSet.singleton x)
           );
           if flag_last then (
             let tr =  (match edges with
                   Pair(e1,e2) ->
                   (SyncTrans (locs, e1, e2))
                 | Single(e1) ->
                   (InternalTrans (locs, e1))
               )
             in
             let locs' = next_location_vector bta locs.stateLocs tr in
             let invar = TASemantics.dbm_invariant_of_state bta
                 {stateLocs = locs'; stateVars = [||]}
             in
             Dbm.intersect d invar;
           )
         | Sym_Reset (locs, edges, x, flag_last) ->
           Dbm.reset d (ClockSet.singleton x);
           if flag_last then (
             let invar = TASemantics.dbm_invariant_of_state bta
                 locs
             in
             Dbm.intersect d invar;
           )
        );
        d
      in
      let pre (trans,_) dbm =
        let d = Dbm.copy dbm in
        (match trans with
           Sym_Up (locs,telapse)->
           let invar = TASemantics.dbm_invariant_of_state bta
               locs
           in
           Dbm.intersect d invar;
           if Dbm.is_empty d then (
             printf "Invariant:\n";
             debug_print_dbm invar;
             printf "Following dbm was intersected with invariant:\n";
             debug_print_dbm dbm;
             failwith "Empty intersection with invariant"
           );
           if telapse then Dbm.pretime d;
         | Sym_Edge(locs, edges, reset, flag_last) ->
           (match reset with
              None -> ()
            | Some(x) ->
              Dbm.constrain d x 0 (0,DBM_WEAK);
              Dbm.free d (ClockSet.singleton x);
           );
           let g =
             (match edges with
                Pair(e1,e2) ->
                let g1 = TASemantics.dbm_guard_of_edge bta e1 in
                let g2 = TASemantics.dbm_guard_of_edge bta e2 in
                let g = (Dbm.copy g1) in
                Dbm.intersect g g2;
                g
              | Single(e1) ->
                TASemantics.dbm_guard_of_edge bta e1
             )
           in
           Dbm.intersect d g;
           let invar = TASemantics.dbm_invariant_of_state bta
               locs
           in
           Dbm.intersect d invar;
         | Sym_Reset(locs, edges, reset, flag_last) ->
           Dbm.constrain d reset 0 (0,DBM_WEAK);
           Dbm.free d (ClockSet.singleton reset);
        );
        d
      in
      (* Concrete init state *)
      let init =
        let dbm = Dbm.create (nclocks+1) in
        Dbm.set_zero dbm;
        let invar = (TASemantics.dbm_invariant_of_state bta bta.init) in
        Dbm.intersect dbm invar;
        dbm
      in
      try
        (* Abstract init state *)
        let ainit =
          try
            Guard.from_constraints (nb_clocks bta) cex_init
          with EmptyDBM ->
            (* Constraints describing initial constraints are unsat
               Must refine reduce *)
             Log.debug "The init abstract state is unsatisfiable: calling refine_empty\n";
            CPA.refine_empty enc.enc_cpa cex_init;
            raise (BreakRefined 1)
        in
      (*
      printf "Init:\nAbs:\n%s\n\nConc:\n%s\n\n"
        (Dbm.to_string ainit) (Dbm.to_string init);
         *)
        if !Log.cegar_verbose then (
          printf "\nINIT Abs:\n";
          Guard.pretty_print stdout bta.clocks ainit;
          printf "\nINIT Conc:\n";
          Guard.pretty_print stdout bta.clocks init;
          printf "\n"
        );

        (* Compute forward successors into cposts,
           while aposts is the zones as computed
           by smv
        *)
        let cposts = Array.make (npath+1) init in
        let aposts = Array.make (npath+1) ainit in

        (* aposts and cposts have additionally initial states:

           path   :     p0  p1  p2  p3 ...
           aposts : a0  a1  a2  a3  a4 ...
           cposts : c0  c1  c2  c3  c4 ...

           So e.g. a0 --p0--> a1, a1 --p1--> a2, etc.
        *)
        for i = 1 to npath do
          let (trans,constr) = path.(i-1) in
          (try
             aposts.(i) <- (Dbm.from_constraints (nb_clocks bta) constr);
           (*
           printf "Aposts(%d)\n" i;
           printf "%s\n" (Dbm.to_string aposts.(i));
              *)
           with EmptyDBM ->
             (* The intersection of the non-reduced constraints is empty.
                Must add predicates so that abstract reduction can capture this *)
             Log.debug "This abstract state is unsatisfiable: calling refine_empty\n";
             CPA.refine_empty enc.enc_cpa constr;
             raise (BreakRefined 1)
          );

          (try
             cposts.(i) <- Dbm.make_empty nclocks;
             cposts.(i) <- post path.(i-1) cposts.(i-1);
           (*
        printf "Cpost(%d)\n" i;
        printf "%s\n" (Dbm.to_string cposts.(i));
              *)

             (* The following intersection is non-trivial
                for Up and Reset which give some region of the time successors or
                reset target states *)
(*
        printf "Intersecting\n %s\n and\n%s\n"
          (Dbm.to_string cposts.(i))
          (Dbm.to_string aposts.(i));
*)
             Dbm.intersect cposts.(i) aposts.(i);
           (*
           printf "After /\\ is\n";
           printf "%s\n" (Dbm.to_string cposts.(i));
        printf "After /\\ aposts.(i):\n";
        printf "%s\n" (Dbm.to_string cposts.(i));
           *)
           with EmptyDBM -> ()
          );
          if ( not (Dbm.is_empty cposts.(i-1))) then(
            if !Log.cegar_verbose then (
              printf "*********** STATE %d *************\n%s\n" i
                (string_of_symbolic_transition bta (fst(path.(i-1))));
              printf "\nAbs:\n";
              Guard.pretty_print stdout bta.clocks aposts.(i);
              printf "Abs:\n";
              List.iter(fun cc -> printf "%s /\\ " (string_of_clock_constraint bta.clocks cc)) constr;
              printf "\n";
              printf "\nConc:\n";
              Guard.pretty_print stdout bta.clocks cposts.(i);
              printf ".\n"
            );
            (*
            printf "\nAbs:\n%s\nConc:\n%s\n"
              (Dbm.to_string aposts.(i))
              (Dbm.to_string cposts.(i));
               *)
            flush stdout;
            (*debug_print_dbm aposts.(i);*)
          );
        done;
        (* Check if the Cex is genuine *)
        if not (Dbm.is_empty cposts.(npath)) then (
          raise BreakGenuine
        );
        (* Now check the transitions *)
        (* i0 is the last index with non-empty cposts *)
        let i0 =
          let rec aux = function
            | i when (Dbm.is_empty cposts.(i+1)) -> i
            | i -> aux (i+1)
          in
          aux 0
        in
        if !Log.cegar_verbose then
          Log.debug (sprintf "i0 = %d\n" i0); flush stdout;
      (*
      printf "First trans:\n";
      printf "%s\n" (string_of_symbolic_transition bta (fst path.(i0)));
      *)
        (* Regular refinement check: *)
        (try
           let preAi01 = (pre path.(i0) aposts.(i0+1)) in
           if !Log.cegar_verbose then (
             printf "PRE of ai0_1 is:\n";
             (Guard.pretty_print stdout bta.clocks preAi01);
             printf "\n";
           );
           let preAi01_ai0 = Dbm.copy preAi01 in
           Dbm.intersect preAi01_ai0 aposts.(i0);
           (* If this set is not empty, we can refine regularly *)
           if !Log.cegar_verbose then (
             Log.debug "PRE(ai0_1) /\\ aposts.(i0) is:\n";
             (Guard.pretty_print stdout bta.clocks preAi01);
             printf "\n";
             Log.debug "We now separate this from cpost.(i0)\n";
           );
           CPA.refine_separate enc.enc_cpa preAi01_ai0 cposts.(i0);
           raise (BreakRefined 2)
         with EmptyDBM ->()
        );
        (* At this point, aposts.(i0) /\ pre(aposts.(i0+1)) = empty *)
        (* Irregular refinement step for non-precise abstraction *)
        (match path.(i0) with
           (Sym_Up(_,false),_) ->
           Log.fatal "Encountered Sym_Up(_,false) during refinement with empty predecessor";
           failwith "this must be a bug in the program"
         | (Sym_Up(_,true),_) ->
           Log.debug "Irregular refinement: Up\n";
           let ai0 = Dbm.copy aposts.(i0) in
           (*
           printf "Initial ai0:\n%s\n" (Dbm.to_string ai0);
              *)
           Dbm.posttime ai0;
           let ai0_1 = Dbm.copy aposts.(i0+1) in
           Dbm.pretime ai0_1;
           CPA.refine_separate enc.enc_cpa ai0 ai0_1
         | Sym_Reset(_,_,x,_),_ ->
           Log.debug "Irregular refinement: Reset\n";
           let ai0 = Dbm.copy aposts.(i0) in
           Dbm.free ai0 (ClockSet.singleton x);
           let ai0_1 = Dbm.copy aposts.(i0+1) in
           Dbm.free ai0_1 (ClockSet.singleton x);
           CPA.refine_separate enc.enc_cpa ai0 ai0_1

         | Sym_Edge(locs,edges,reset_opt,flag_last),_ ->
           Log.debug "Irregular refinement: Edge Reset\n";
           let ai0 = Dbm.copy aposts.(i0) in
           let ai0_1 = Dbm.copy aposts.(i0+1) in
           (match reset_opt with
              None ->
              failwith "Irregular refinement: Reset without reset"
            | Some x ->

              Dbm.free ai0 (ClockSet.singleton x);

              (try
                 Dbm.constrain (Dbm.copy ai0_1) x 0 (0, DBM_WEAK);
               with EmptyDBM ->
                 let d = Dbm.create (nb_clocks bta) in
                 Dbm.constrain d x 0 (0, DBM_WEAK);
                 CPA.refine_separate enc.enc_cpa ai0_1 d;
                 raise (BreakRefined(-1))
              );
            (*
            printf "Guard is:\n%s\n" (Guard.to_string g);
               *)
              Dbm.constrain ai0_1 x 0 (0, DBM_WEAK);
            (*
            printf "ai0_1 /\\ x=0 is\n%s\n" (Guard.to_string ai0_1);
               *)
              Dbm.free ai0_1 (ClockSet.singleton x);
            (*
            printf "free(ai0_1 /\\ x=0) is\n%s\n" (Guard.to_string ai0_1);
            printf "And reset(ai0) is\n%s\n" (Guard.to_string ai0);
               *)
           );
           CPA.refine_separate enc.enc_cpa ai0 ai0_1
        );
        raise (BreakRefined 3)

      (* e.g.
         path   :     p0  p1  p2   p3 ...
         cposts : c0  c1  c2  c3   c4 ...
                        i0  i0+1
      *)
      with BreakRefined(i) ->
        Log.debug (sprintf "Spurious cex eliminated by Refinement type %d\n" i);
        Refined
         | BreakGenuine -> Genuine
         | BreakCannotRefine -> CannotRefine
  end

    (* A lot of these transitions will be always unfirable.
       How can we detect and eliminate these?

       FIXME Use a type MC.t to store whatever is useful
       for these computations to avoid passing long lists of arguments
       to other functions
    *)
  let forward_reach enc =
    let open Encoding in
    let print_bdd_stats enc ~edges:edges
        ~reset_constraint_table:reset_constraint_table
        ~reduce_full:reduce_full ~reduce_up:reduce_up =
      Log.info "** BDD STATS\n";
      printf "Edge relation BDDs have sizes: ";
      Queue.iter
        (fun (_,transrel,transgrd,_) ->
           printf "(%d, %d)" (Bdd.size transrel) (Bdd.size transgrd)
        )
        edges;
      printf "\nReset table BDDs: ";
      Array.iteri
        (fun ri rbdd ->
           printf "%d, " (Bdd.size rbdd)
           (*
         printf "Reset(%d): %d\n" ri (Bdd.size rbdd)
              *)
        ) reset_constraint_table;
      printf "\nReduce: ";
      Queue.iter (fun r -> printf "%d, " (Bdd.size r)) reduce_full;
    (*
    printf "Monolithic reduce has size: %d\n" ((Bdd.dand_of_queue enc.enc_man reduce_full) |> Bdd.size);
    *)
      printf "\nReduce_up: ";
      Queue.iter (fun r -> printf "%d, " (Bdd.size r)) reduce_up;
      printf "\nNumber of clock predicates: %d\n" (CPA.size enc.enc_cpa);
      printf "Total number of BDD variables: %d\n" (Man.get_bddvar_nb enc.enc_man);
      Log.info "** End of BDD STATS\n"
    in

    let nclocks = nb_clocks enc.enc_ta in
    let man = enc.Encoding.enc_man in
    let edges = find_all_transitions enc in
    (* includes both discrete states and clock predicates *)
    (* BDDs concerning discrete states *)
    let current_disc_state_cube = Bdd.dand enc.Encoding.enc_loc_cube enc.Encoding.enc_var_cube in
    let target = Encoding.bdd_of_query enc enc.Encoding.enc_ta.query in
    let committed_ar = Encoding.bdd_array_of_committed enc in
    let committed = Bdd.dor_of_array man committed_ar in
    let ds_cube = Bdd.dand enc.enc_loc_cube enc.enc_var_cube in
    let ds_cube' = Bdd.dand enc.enc_ploc_cube enc.enc_pvar_cube in
    (* not Urgent and not committed states: *)
    let time_can_pass =
      (Bdd.dor
        (Bdd.dor_of_array man (Encoding.bdd_array_of_urgent enc))
        committed
      )
      |> Bdd.dnot
    in
    (* BDDs concerning clock predicates *)
    let invariant = Encoding.bdd_of_invariant enc in
    let reset_constraint_table =
      Enum.map (get_reset_constraint enc) (0--(nclocks-1))
      |> Array.of_enum
    in
    let reduce_up = encode_reduce ~threshold:Options.bdd_reduce_threshold ~mode:Reduce_Up enc in
    let reduce_full =  enc.enc_reduce in
(*encode_reduce ~threshold:Options.bdd_reduce_threshold ~mode:Reduce_All enc in*)

    (* Print statistics *)
    if !Log.cegar_print_bdd_stats then 
    print_bdd_stats enc ~edges:edges ~reset_constraint_table:reset_constraint_table
      ~reduce_full:reduce_full ~reduce_up:reduce_up;

    (* Prepare the exploration algorithm *)
    let layers = Queue.create () in
    let it = ref 0 in
    let verdict = ref false in
    let expand_edges = compute_discrete_next enc ~reset_constraint_table:reset_constraint_table
        ~current_disc_state_cube:current_disc_state_cube ~committed:committed
        ~reduce:reduce_full ~edges:edges ~invariant:invariant
    in
    let apply_up = compute_up enc reduce_full time_can_pass in
    let init_state =
      Enum.fold (fun acc i ->
          (* rectangular constraints *)
          Enum.fold(fun acc j ->
              if i=j then acc
              else (
                Bdd.dand acc
                  (over_approximate_clock_constraint enc (i,j,(0,DBM_WEAK)))
              )
            ) acc (0--(nclocks-1))
      ) (Bdd.dtrue man) (0--(nclocks-1))
      |> Bdd.dand invariant
      |> Bdd.dand (Encoding.bdd_of_init_discrete_state enc)
      |> (fun states -> apply_reduce enc states reduce_full)
    in
    let init_state_up =
      (*compute_up_rel init_state*)
      apply_up init_state
      |> Bdd.dand invariant
    in

    (*
    print_clock_constraints enc init_state;    printf "INIT:\n";
    print_states enc init_state_up;
    printf "\n";
       *)
    let reachable = ref init_state_up in
    let rec explore ?early_termination:(early_termination=true) states =
      if Bdd.is_false states then !verdict
      else (
        incr(it);
        if !Log.cegar_verbose_fwd_reach then(
          Log.info (sprintf "Iteration %d: Reachable has size %d\t\t\r" !it (Bdd.size !reachable));
          flush stdout;
        );
        let next = expand_edges states
                   |> apply_up
                   |> Bdd.dand invariant
        in
        let next = next
                   |> Bdd.dand (Bdd.dnot !reachable)
        in
        Queue.add next layers;
        let next' =
          if Options.bdd_use_restrict then
            Bdd.restrict next (Bdd.dnot !reachable)
          else
            next
        in
        if !Log.cegar_verbose_fwd_reach then(
          if (Bdd.size next) > (Bdd.size next') then
            Log.info (sprintf "\tNext: %d. Next': %d\n" (Bdd.size next) (Bdd.size next'))
        );
        reachable := Bdd.dor !reachable next';
        if (not(Bdd.is_inter_empty next' target)) then(
          verdict := true;
          if not early_termination then
            explore next'
          else true
        ) else
          explore next'
      )
    in
    (**
       @pre last element of layers contain target
    *)
    let extract_abstract_counterexample enc layers target =
      let reset_rel_table =
        Enum.map (get_reset_relation enc) (0--(nclocks-1))
        |> Array.of_enum
      in
      let up_rel = get_up_rel enc in
      let symtrace = Queue.enum layers |> Array.of_enum in
      let ntrace = Array.length symtrace in
      let apply_down states =
        Bdd.dand states time_can_pass
        |> Encoding.prime_clock_preds enc
        |> Bdd.dand up_rel
        |> Bdd.exist enc.enc_pclock_cube
        |> (fun s -> apply_reduce enc s reduce_full)
        |> Bdd.dor states
      in
      let apply_unreset states ri =
        Encoding.prime_clock_preds enc states
        |> Bdd.dand reset_rel_table.(ri)
        |> Bdd.exist enc.enc_pclock_cube
        |> (fun states -> apply_reduce enc states reduce_full)
      in
      let make_up_trans cube =
        let ds = Encoding.discrete_state_of_cube enc cube in
        Sym_Up(ds, not(Uautomaton.is_urgent_or_committed enc.enc_ta ds))
      in
      let conc_trace = Stack.create () in
      (* We add to conc_trace the last state which is the Up operation ending in target *)
      let mt = (Bdd.pick_minterm (Bdd.dand symtrace.(ntrace-1) target)) in
      let current_state = ref (Bdd.cube_of_minterm man mt) in

      for i = ntrace-1 downto 1 do
        (* Invariant: !current_state is a set of states that intersects symtrace.(i)
           We pick one particular state
           and comptue the predecessors of that state in layer.(i-1)
        *)
        let mt = (Bdd.pick_minterm (Bdd.dand !current_state symtrace.(i))) 
                 |> Bdd.fill_in_minterm_unprimed_positive in
        current_state := Bdd.cube_of_minterm man mt;
        (*
        current_state := Bdd.cube_of_minterm man mt';
        Array.iter2i (fun i m m' ->
            let str_of_tbool = function |Man.True -> "t"|Man.False -> "f"|Man.Top -> "_" in
            if (i mod 2) = 0 then
            if m<>m' then (
              printf "differ at %d: %s vs %s\n" i (str_of_tbool m) (str_of_tbool m')
            )
          ) mt mt';

           *)
        (*
        printf "current_state(%d):\n" i;
        print_states enc !current_state;
        printf "\n";
           *)

        (* Here we apply fill_in_minterm_positive to mt in order to make the clock zone
           tight. Otherwise some predicates can become don't cares, in which case
           the refinement algorithm may not succeed (e.g. the regular case)
        *)
        Stack.push
          ((make_up_trans !current_state),
           constraint_list_of_minterm enc mt
          ) conc_trace;

        let exception FoundEdge of edge single_or_pair in
        let apply_reset = compute_reset ~reset_constraint_table:reset_constraint_table
            enc
        in
        (*
        printf "current_state(%d):\n" i;
        print_states enc !current_state;
        printf "\n";

        let mt' = (Bdd.fill_in_minterm_positive mt) in
        Array.iter2i (fun i m m' ->
            let str_of_tbool = function |Man.True -> "t"|Man.False -> "f"|Man.Top -> "_" in
            if (i mod 2) = 0 then
            if m<>m' then (
              printf "differ at %d: %s vs %s\n" i (str_of_tbool m) (str_of_tbool m')
            )
          ) mt mt';
        current_state := Bdd.cube_of_minterm man mt;
        assert(false);
           *)

        (* Iterate over all transitions to find a feasible one
           that leads to current_state
           Once found one, compute the intermediate states and add them to conc_trace
        *)
        try
          (*
          let cube = enc.enc_var_cube in
          let cube' = prime_locations_and_vars enc cube in
          print_bdd cube;
          printf "\n";
          print_bdd cube';
          printf "\n";
             *)
          let tgt_ds_cube' = Bdd.exist enc.enc_clock_cube !current_state
                             |> prime_locations_and_vars enc
          in
          Queue.iter
            (fun (trans,trans_rel, trans_grd, resets) ->
               let trans_bdd = Bdd.dand trans_rel trans_grd in
               (*
               printf "Trying following transition:\n";
               TASemantics.print_transition_pair enc.enc_ta trans;
               printf "\n";
                  *)
               (* Try this trans only if trans_bdd /\ current_state' is sat *)
               if not(Bdd.is_inter_empty trans_bdd tgt_ds_cube') then (

                 let tgt_ds = (discrete_state_of_cube enc
                                 (unprime_locations_and_vars enc tgt_ds_cube')) in
                 let states = symtrace.(i-1) in
                 let states =
                   if not (TASemantics.is_transition_committed enc.Encoding.enc_ta trans) then (
                     Bdd.dand states (Bdd.dnot committed)
                   ) else states
                 in
                 let img =
                   (Bdd.dand states trans_bdd)
                   |> Bdd.exist current_disc_state_cube
                   |> Encoding.unprime_locations_and_vars enc
                 in
                 if not(Bdd.is_false img) then (
                   (* Apply Reset
                      Returns [reset2, reset1, img]
                   *)
                   let rev_steps =
                     List.fold_left
                       (fun acc rx ->
                          (apply_reset ~do_reduce:true rx (List.hd acc))
                          :: acc
                       ) [img] resets
                   in
                   let before_up = Bdd.dand invariant (List.hd rev_steps) in
                   let steps = (List.rev rev_steps) |> List.tl |> List.enum |> Array.of_enum in
                   let nsteps = Array.length steps in
                   (*
                   printf "BEFORE_UP. steps: %d:\n" nsteps;
                   print_states enc before_up;
                    *)
                   (* Let steps=[r1,r2,r3]. We have
                      0) symtrace.(i)
                      1) --guard--> (ds(img), Z)
                      2) --r1:=0--> r1
                      3) --r2:=0--> r2
                      4) --r3:=0--> r3
                      5) --&invar--> before_up    (we skip reduce)
                      6) --up--> symtrace.(i+1)     (we skip reduce)
                   *)
                   let cur_down = apply_down !current_state in
                   (*printf "Previous step before_up is:\n";
                   print_states enc before_up;
                   *)

                   if not(Bdd.is_inter_empty before_up cur_down) then (
                     (*
                     let fst_ccl = Encoding.constraint_list_of_minterm enc (Bdd.pick_minterm !current_state) in
                        *)
                     (*
                     printf "Chose following transition:\n";
                     TASemantics.print_transition_pair enc.enc_ta trans;
                     printf "\n";
                        *)
                   (*printf "Previous step before_up is:\n";
                   print_states enc before_up;
                   *)
                     (* The transition is feasible into current_state *)
                     let mt  = (Bdd.pick_minterm (Bdd.dand cur_down before_up)) 
                               |> Bdd.fill_in_minterm_unprimed_positive
                     in
                     (*
                     let snd_ccl = Encoding.constraint_list_of_minterm enc mt in
                        *)
                     (* At 4 and 5 *)
                     current_state := Bdd.cube_of_minterm man mt;
                     let cclist = ref (constraint_list_of_minterm enc mt) in
                     (*
                     printf "Time predecessor(%d):\n" i;
                     List.iter(fun cc -> printf "%s /\\ " (string_of_clock_constraint enc.enc_ta.clocks cc)) !cclist;
                        *)

                     (*
                        If current_state is in r_i, we want to find a predecessor in r_{i-1}.
                        We compute pred_{reset(r_i)}(current_state) /\\ steps.(i-1)
                        and pick a minterm in it
                     *)
                     (* If no reset at all *)
                     if nsteps = 0 then (
                       Stack.push
                         ((Sym_Edge (tgt_ds, trans, None,true)),!cclist)
                         conc_trace
                     ) else if nsteps = 1 then (
                       let last_clock = List.last resets in
                       Stack.push
                         (((Sym_Edge (tgt_ds, trans, Some last_clock, true))), !cclist)
                         conc_trace;
                       current_state := apply_unreset !current_state last_clock;
                     ) else (
                       let last_clock = List.last resets in
                       Stack.push
                         (((Sym_Reset (tgt_ds, trans, last_clock, true))), !cclist)
                         conc_trace;
                       current_state := apply_unreset !current_state last_clock;
                     );
                       (*
                       printf "After unreset %d, we get\n" last_clock;
                       print_states enc cur_unreset;
                       let mt = Bdd.pick_minterm (Bdd.dand cur_unreset steps.(nsteps-1)) in
                       current_state := Bdd.cube_of_minterm man mt;
                       printf "I picked:\n";
                       print_states enc !current_state;
                       cclist := constraint_list_of_minterm enc mt;
                          *)
                     for ri = nsteps-2 downto 0 do
                       let ri_clock = List.nth resets ri in
                       let mt = Bdd.pick_minterm (Bdd.dand !current_state steps.(ri)) 
                                |> Bdd.fill_in_minterm_unprimed_positive 
                       in
                       current_state := Bdd.cube_of_minterm man mt;
                       cclist := constraint_list_of_minterm enc mt;
                       if ri > 0 then (
                         Stack.push
                           (((Sym_Reset (tgt_ds, trans, ri_clock, false))), !cclist)
                           conc_trace
                       ) else (
                         Stack.push
                           (((Sym_Edge (tgt_ds, trans, Some ri_clock, false))), !cclist)
                           conc_trace
                       );
                       current_state := apply_unreset !current_state ri_clock
                     done;
                     (*
                     printf "New Clocks constraints:\n";
                     print_bdd (Bdd.support (Bdd.exist ds_cube !current_state));
                     printf "\nds'_cube:";
                     print_bdd ds_cube';
                     printf "\n";
                     print_bdd
                         (Bdd.support(Bdd.dand trans_bdd tgt_ds_cube'
                          |> Bdd.exist enc.enc_clock_cube
                          |> Bdd.exist ds_cube'
                         ));
                     printf "\n";
                        *)
                     current_state :=
                       (Bdd.exist ds_cube !current_state) (* clock constraints *)
                       |> Bdd.dand
                         (* source ds: there can be many of them*)
                         (Bdd.dand trans_bdd tgt_ds_cube'
                          (*|> Bdd.exist enc.enc_clock_cube*)
                          |> Bdd.exist ds_cube'
                         );
                     raise Found;
                   );
                 )
               );
            )
            edges;
          failwith "Could not compute counterexample edge"
          with Found -> ()
      done;
      (* Add (initial up) *)
      let mt = (Bdd.pick_minterm (Bdd.dand !current_state symtrace.(0))) 
               |> Bdd.fill_in_minterm_unprimed_positive
      in
      current_state := Bdd.cube_of_minterm man mt;
      Stack.push
        ((make_up_trans !current_state),
         constraint_list_of_minterm enc mt
        ) conc_trace;
      (* Now add the initial (before up *)
      let cur_down = apply_down !current_state in
      let mt  = (Bdd.pick_minterm (Bdd.dand cur_down init_state)) 
               |> Bdd.fill_in_minterm_unprimed_positive
      in
      current_state := Bdd.cube_of_minterm man mt;
      let cexinit = (Encoding.discrete_state_of_cube enc !current_state), (constraint_list_of_minterm enc mt) in
      let sym_path =
        (Stack.enum conc_trace |> List.of_enum)
      in
      if !Log.cegar_verbose then
        printf "Printing CEX\t\t\t\t\n%s\n\n"
          (string_of_symbolic_path enc.enc_ta (cexinit, sym_path));
      cexinit, sym_path
    in
    Queue.add init_state_up layers;
    let result = explore !reachable in
    if !Log.cegar_verbose_fwd_reach then
      Log.info (sprintf "Explored %d layers." (Queue.length layers));
    if !verdict then (
      Some(extract_abstract_counterexample enc layers target)
    ) else (
      None
    )


exception Cegar_result of string

let reach ta =
  let open Encoding in
  let cpa = ClockPredicateAbstraction.init_syntax ta in
  let max_iterations = 1000 in
  let count_peak = ref 0 in
  if !Log.log_level = Log.Debug then (
    VarContext.iter (fun name i -> printf "Clock(%d) = %s\n" i name) ta.clocks
  );
  try
    for count = 1 to max_iterations do
      Gc.full_major(); (* this forces BDD nodes to be destroyed *)
      (*
      printf "Before saturation\n";
      CPA.print ta cpa;
         *)
      saturate_clock_constraints cpa;
      let man = Cudd.Man.make_d()in
      (*Man.enable_autodyn man Man.REORDER_SIFT;*)
      let enc = Encoding.make ta cpa man in
      if !Log.cegar_verbose then Encoding.print_info enc;
      Stats.cegar_nb_iterations := count;
      Stats.cegar_nb_clock_predicates :=
        Hashtbl.length (fst (enc.enc_clock_predicates));
      Stats.print_cegar_stats();
      count_peak := max !count_peak (Cudd.Man.get_node_count_peak man);
      (match forward_reach enc with
       | None -> raise (Cegar_result "false")
       | Some(cex) ->
         (match Refinement.refine enc cex with
          | CannotRefine -> failwith "Refinement is impossible: Result is inconclusive"
          | Refined -> Log.info "Refined successfully\n";
          | Genuine ->
            Log.info "Counter-example confirmed\n";
            raise (Cegar_result "true")
         )
      )
    done;
    ""
  with Cegar_result(s) ->
    printf "** Node peak: %d\n" !count_peak;
    Stats.print_cegar_stats();
    s
end

let reach = MC.reach
