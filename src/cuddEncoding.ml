open Pdbm
open Common
open TimedAutomaton
open ClockPredicateAbstraction
open Batteries
open Printf
open Uta
open Cudd
open Uautomaton
open Str

module Dbm = Pdbm.Guard
module CPA = ClockPredicateAbstraction

exception IncompatibleModelError

module Bdd =
struct
  include Bdd

  let dor_of_array enc e =
    Array.fold_left (fun bdd bit -> Bdd.dor bdd bit) (Bdd.dfalse enc) e
  let dor_of_list enc e =
    List.fold_left (fun bdd bit -> Bdd.dor bdd bit) (Bdd.dfalse enc) e

  let dand_of_array enc e =
    Array.fold_left (fun bdd bit -> Bdd.dand bdd bit) (Bdd.dtrue enc) e
  let dand_of_list enc e =
    List.fold_left (fun bdd bit -> Bdd.dand bdd bit) (Bdd.dtrue enc) e

  let dand_of_queue enc e =
    Queue.fold (fun bdd bit -> Bdd.dand bdd bit) (Bdd.dtrue enc) e

  let dor_of_queue enc e =
    Queue.fold (fun bdd bit -> Bdd.dor bdd bit) (Bdd.dfalse enc) e

  let rec minterms man bdd =
    let x = ref bdd in
    let next =
      fun () ->
        if Bdd.is_false !x then
          raise BatEnum.No_more_elements
        else (
          let mt = (Bdd.pick_minterm !x) in
          let p = Bdd.cube_of_minterm man mt in
          x := Bdd.dand !x (Bdd.dnot p);
          mt
        )
    in
    Enum.make ~next:next ~count:(fun()->int_of_float(Bdd.nbminterms (Man.get_bddvar_nb man) bdd))
      ~clone:(fun ()->(minterms man !x))

  let print_bdd bdd =
    flush stdout;
    Bdd.print_minterm (fun fmt i -> Format.pp_print_string Format.std_formatter (sprintf "%d " i)) Format.std_formatter bdd;
    Format.pp_print_flush Format.std_formatter ();
    Format.print_flush()

  let print_bdd_array bar = 
    flush stdout;
    print_string "\t";
    Array.iter (fun b -> print_bdd b; print_string "\n\t") bar;
    Format.pp_print_flush Format.std_formatter ()

  let fill_in_minterm_unprimed_positive =
    Array.mapi
      (fun i b -> if (i mod 2)=1 then b else
          match b with
            Man.True -> Man.True
          | Man.False -> Man.False
          | Man.Top -> Man.True
      )
end

let print_bdd = Bdd.print_bdd


(**
   Bdd encoding of timed automata.

   Note concerning clock predicates.
   ClockPredicateAbstraction module is meant to contain all constraints one can write
   given an abstraction regardless of their encoding in BDDs.
   In particular, if x>2 appears in the guards, init_syntax would initialize the abstraction 
   by adding <=2 to (x,0), ????
*)
module Encoding =
struct
  type t =
    {
      enc_ta  : timed_automaton;
      enc_cpa : ClockPredicateAbstraction.t;
      enc_man : Cudd.Man.d Cudd.Man.t;
      (** Array of Bdds encoding the variable given by its VarContext index with low-bit encoding *)
      mutable enc_vars : (Bdd.dt array) array;
      (** The primed version of the above *)
      mutable enc_pvars : (Bdd.dt array) array;
      (** Array of location of given process *)
      mutable enc_loc : (Bdd.dt array) array;
      mutable enc_ploc : (Bdd.dt array) array;
      mutable enc_loc_cube : Bdd.dt;
      mutable enc_ploc_cube : Bdd.dt;
      mutable enc_var_cube : Bdd.dt;
      mutable enc_pvar_cube : Bdd.dt;
      mutable enc_clock_cube : Bdd.dt;
      mutable enc_pclock_cube : Bdd.dt;
      (*mutable enc_clock_constraints : Dbm.Alg.t list array array;*)
      enc_clock_predicates : (int, Guard.clock_constraint) Hashtbl.t *  (Dbm.Alg.t, Bdd.dt) Hashtbl.t array array;
      mutable enc_reduce : Bdd.dt Queue.t;
      (* General cache for storing Bdds *)
      mutable enc_cache : (string, Bdd.dt) Hashtbl.t
    }


  (** Clock Predicates *)

  (** From the abstraction abs, add all constraints that
      can be expressed as well by negating the given predicates.
      For instance, if abs contains (x-0<2) then one can
      express (0-x<=-2) since this is its negation.

      We also keep the constraint (0-y<=0)
      here which is required for computing the reduce constraint
      although we will not instantiate the corresponding predicate (y-0<0)
      in BDD encodings as it is always false
  *)
  let saturate_clock_constraints abs =
    let module Dbm = Pdbm.Guard in
    let module ConstrSet =Set.Make(struct type t = Dbm.Alg.t let compare=compare end) in
    (* so that we iterate through 0..nb_clocks *)
    let nb_clocks = (Array.length abs) - 1 in
    for x = 0 to nb_clocks -1 do
      for y = 0 to nb_clocks -1 do
        if x <> y then (
          DynArray.iter
            (fun k ->
               let k' = (Dbm.Alg.invert_raw k) in
               if not(x=0 && k' < Dbm.Alg.zero)
               then
                 CPA.add_predicate abs (y,x) k'
            ) abs.(x).(y)
        )
      done
    done




  let apply_reduce enc states reduce_queue =
    let a = ref states in
    Queue.iter (fun r -> a := Bdd.dand !a r) reduce_queue;
    !a

  let dbm_of_minterm enc mt =
    let dim = nb_clocks enc.enc_ta in
    let dbm = Dbm.create dim in
    let var2cc = fst enc.enc_clock_predicates in
    Array.iteri
      (fun i b ->
         (try
            let (x,y,cc) = Hashtbl.find var2cc i in
            (match b with
             |Man.True ->
               (*
               printf "%d %d %s\n" x y (Dbm.Alg.to_string cc);
                  *)
               Dbm.constrain dbm x y cc
             |Man.False ->
               (*
               printf "~(%d %d %s)\n" x y (Dbm.Alg.to_string cc);
               printf "\t%d %d %s\n" y x (Dbm.Alg.to_string  (Dbm.Alg.invert_raw cc));
                  *)
               Dbm.constrain dbm y x (Dbm.Alg.invert_raw cc)
             |Man.Top -> ()
            )
          with Not_found ->())
      ) mt;
    dbm

  let constraint_list_of_minterm enc mt =
    let cclist = Queue.create () in
    let var2cc = fst enc.enc_clock_predicates in
    Array.iteri
      (fun i b ->
         (try
            let (x,y,cc) = Hashtbl.find var2cc i in
            (match b with
             |Man.True ->
               (*
               printf "%d %d %s\n" x y (Dbm.Alg.to_string cc);
                  *)
               Queue.add (x,y,cc) cclist
             |Man.False ->
               (*
               printf "~(%d %d %s)\n" x y (Dbm.Alg.to_string cc);
               printf "\t%d %d %s\n" y x (Dbm.Alg.to_string  (Dbm.Alg.invert_raw cc));
                  *)
               Queue.add (y,x,(Dbm.Alg.invert_raw cc)) cclist
             |Man.Top -> ()
            )
          with Not_found ->())
      ) mt;
    cclist
    |> Queue.enum
    |> List.of_enum


  let print_cpa_encoding ta clock_maps =
    printf "Clock Predicate Variables:\n";
    let (bdd2cc, cc2bdd) = clock_maps in
    let nclocks = nb_clocks ta in
    for x = 0 to nclocks-1 do
      for y = 0 to nclocks-1 do
        Hashtbl.iter
          (fun cc bdd ->
             printf "%d - %d %s : <%d>\n" x y (Dbm.Alg.to_string cc) (Bdd.topvar bdd)
          ) cc2bdd.(x).(y)
      done
    done

  let rec get_clock_literal enc ?primed:(primed=false) x y b =
    (*
    printf "get_clock_literal %d %d %s\n" x y (Dbm.Alg.to_string b);
       *)
    if x = y then (
      let cmp = Dbm.Alg.compare b Dbm.Alg.zero in
      if cmp >= 0 then Bdd.dtrue enc.enc_man
      else Bdd.dfalse enc.enc_man
    ) else if x = 0 && b = Dbm.Alg.zero then (
      (* trivial constraint <-> ~(x<0)*)
      Bdd.dtrue enc.enc_man
    ) else (
      let (x,y,b,negate) =
        if x > y then (x,y,b,false)
        else (
          (y,x,Dbm.Alg.invert_raw b, true)
        )
      in
      (*printf "\t %d %d %s\n" x y (Dbm.Alg.to_string b);*)
      let varbdd =
        let bdd = Hashtbl.find (snd enc.enc_clock_predicates).(x).(y) b in
        if primed then (
          Bdd.ithvar enc.enc_man((Bdd.topvar bdd)+1)
        ) else bdd
      in
      if negate then Bdd.dnot varbdd
      else varbdd
    )


  let over_approximate_clock_constraint enc (x,y,b) =
(*    printf "over_appr %d %d %s : " x y (Dbm.Alg.to_string b);*)
    match CPA.over_approximate enc.enc_cpa x y b with
      None ->
      Bdd.dtrue enc.enc_man
    | Some(b') ->
      (*printf "%s\n" (Dbm.Alg.to_string b');
      let bdd = get_clock_literal enc x y b' in
      print_bdd bdd;
      printf "\n";
      bdd
      *)
      get_clock_literal enc x y b'

  let under_approximate_clock_constraint enc (x,y,b) =
    match CPA.under_approximate enc.enc_cpa x y b with
      None -> Bdd.dtrue enc.enc_man
    | Some(b') ->
      get_clock_literal enc x y b'

  let print_clock_constraint_mincube enc mt = 
    let clock_name x =
      VarContext.index2var enc.enc_ta.clocks x in
    Array.iteri
      (fun i bt ->
         (try
            let (x,y,b) = Hashtbl.find (fst enc.enc_clock_predicates) i in
            (match bt with
               Man.True ->
               printf "%s - %s %s /\\ " (clock_name x) (clock_name y) (Dbm.Alg.to_string b)
             | Man.False ->
               printf "%s - %s %s /\\ " (clock_name y) (clock_name x) (Dbm.Alg.to_string (Dbm.Alg.invert_raw b))
             | Man.Top -> ()
            )
          with Not_found -> ());
      )
      mt;
    printf "\n"


  let print_clock_constraints enc states =
    let cstates =
      Bdd.exist enc.enc_loc_cube states
      |> Bdd.exist enc.enc_var_cube
    in
    let x = ref cstates in
    let count = ref 0 in
    while not(Bdd.is_false !x) do
      let mt = (Bdd.pick_minterm !x) in
      print_clock_constraint_mincube enc mt;
      let p = Bdd.cube_of_minterm enc.enc_man mt in
      incr(count);
      x := Bdd.dand !x (Bdd.dnot p)
    done(*
    printf "Printed %d minterms\n" !count*)

  (* Reduced *)
  let cube_of_dbm enc dbm =
    let cube = ref (Bdd.dtrue enc.enc_man) in
    let dim = Dbm.dimension dbm in
    for x = 0 to dim-1 do
      for y = 0 to dim-1 do
        cube := Bdd.dand !cube
          (over_approximate_clock_constraint enc (x,y,Dbm.elementAt dbm x y))
      done
    done;
    apply_reduce enc !cube enc.enc_reduce



  (** Constructors *)

  (** how many bits do we need to represent 0..a *)
  let rec bitsize_of_number a =
    assert(a>=0);
    if a = 0 then 0
    else (bitsize_of_number (a/2))+1

  (* low-bit encoding of a number *)
  let encoding_of_number ?size a =
    assert(a>=0);
    let size =
      (match size with
         None -> (bitsize_of_number a)
       | Some s -> s
      )
    in
    let bits = Array.make size true in
    let a = ref a in
    for i = 0 to size-1 do
      bits.(i) <- (!a mod 2) = 1;
      a := !a / 2
    done;
    assert(!a = 0);
    bits

  let _make_var_encoding enc size =
    let bits = Array.make size (Bdd.dfalse enc.enc_man) in
    let pbits = Array.make size (Bdd.dfalse enc.enc_man) in
    Enum.iter
      (fun i ->
         bits.(i) <- Bdd.newvar enc.enc_man;
         pbits.(i) <- Bdd.newvar enc.enc_man
      ) (0--(size-1)); (*((size-1)---0);*)
    (bits,pbits)


  (* Make primed and unprimed bits for each discrete variable with low bit encoding *)
  let register_vars enc =
    enc.enc_vars <- Array.make (VarContext.size enc.enc_ta.vars) [|Cudd.Bdd.dfalse enc.enc_man|];
    enc.enc_pvars <- Array.make (VarContext.size enc.enc_ta.vars) [|Cudd.Bdd.dfalse enc.enc_man|];
    let cube = ref (Bdd.dtrue enc.enc_man) in
    let cube' = ref (Bdd.dtrue enc.enc_man) in
    enc.enc_ta.vars
    |> VarContext.iter
      (fun var ivar ->
         match VarContext.range_of_index enc.enc_ta.vars ivar with
         | None -> failwith (sprintf "Range not found for var %s" var)
         | Some(l,r) ->
           (* FIXME For now we restrict to this case *)
           assert(l=0 && r > 0);
           let size = bitsize_of_number (r-l) in
           let (bits,pbits) = _make_var_encoding enc size in
           enc.enc_vars.(ivar) <- bits;
           cube := Bdd.dand !cube (Bdd.dand_of_array enc.enc_man bits);
           enc.enc_pvars.(ivar) <- pbits;
           cube' := Bdd.dand !cube' (Bdd.dand_of_array enc.enc_man pbits);
      );
    enc.enc_var_cube <- !cube;
    enc.enc_pvar_cube <- !cube'

  let register_locations enc =
    enc.enc_loc <- Array.make (Array.length enc.enc_ta.procs) [|Cudd.Bdd.dfalse enc.enc_man|];
    enc.enc_ploc <- Array.make (Array.length enc.enc_ta.procs) [|Cudd.Bdd.dfalse enc.enc_man|];
    let cube = ref(Bdd.dtrue enc.enc_man) in
    let cube' = ref(Bdd.dtrue enc.enc_man) in
    enc.enc_ta.procs
    |> Array.iteri
      (fun iproc proc ->
           let size = bitsize_of_number ((Array.length proc.procLocations)) in
         let (bits,pbits) = _make_var_encoding enc size in
         enc.enc_loc.(iproc) <- bits;
         enc.enc_ploc.(iproc) <- pbits;
         cube := Bdd.dand !cube (Bdd.dand_of_array enc.enc_man bits);
         cube' := Bdd.dand !cube' (Bdd.dand_of_array enc.enc_man pbits);
      );
    enc.enc_loc_cube <- !cube;
    enc.enc_ploc_cube <- !cube'

  let register_clock_preds man preds =
    let nclocks = Array.length preds in
    let bddvar2clock_constraint = Hashtbl.create 1000 in
    let clock_constraint2bddvar =
      Array.init (nclocks)
        (fun x -> Array.init (nclocks) (fun y -> Hashtbl.create 1000))
    in
    for x = 1 to (Array.length preds)-1 do
      for y = 0 to x-1 do
        DynArray.iter (fun cc ->
            let var = Bdd.newvar man in
            let _ = Bdd.newvar man in
            Hashtbl.add bddvar2clock_constraint (Bdd.topvar var) (x,y,cc);
            Hashtbl.add clock_constraint2bddvar.(x).(y) cc var;
          ) preds.(x).(y)
      done;
    done;
    (bddvar2clock_constraint, clock_constraint2bddvar)

  let merge_bdd_array_threshold enc queue thr =
    let q = Queue.create () in
    let last =
      Queue.fold
      (fun acc conj ->
         let acc = Bdd.dand acc conj in
         if Bdd.size acc >= thr then(
           Queue.add acc q;
           Bdd.dtrue enc.enc_man
         ) else (
           acc
         )
      ) (Bdd.dtrue enc.enc_man) queue
    in
    if not(Bdd.is_true last) then
      Queue.add last q;
    q

  type encode_reduce_mode = Reduce_All | Reduce_Up
  (** Returns an encoding of the 2-reduction formula associated to given abstraction preds

      Returns queue of (lhs,rhs) such that
      /\ (lhs -> rhs) is the required reduce constraint

      If threshold is specified, then the conjuncts are merged
      from left to right until they exceed BDD size threshold

  *)
  let encode_reduce ?mode:(mode=Reduce_All) ?threshold enc =
    (*
    let preds = enc.enc_clock_constraints in
       *)
    let bta = enc.enc_ta in
    let preds = enc.enc_cpa in
    let nbclocks = (nb_clocks bta)-1 in
    let conj = Queue.create () in
    for x = 0 to nbclocks do
      for y = 0 to nbclocks do
        if x=0 && y =0 then ()
        else if mode=Reduce_Up && (y<>0) then ()
        else(
          let add_conjunct k =
            let disj = Queue.create () in
            (* first term *)
            DynArray.iter (fun l ->
                if l <= k then (
                  (*printf "%d %d %s <- %s\n" x y (Dbm.Alg.to_string k) (Dbm.Alg.to_string l);*)
                  Queue.add (get_clock_literal enc x y l ) disj
                )
              ) preds.(x).(y);
            (*
            Queue.iter (fun expr -> printf "\t disj: %s\n" (string_of_bool_expr expr)) disj;
            printf "Now the second disj.\n";
               *)
            (* second term *)
            for z = 0 to nbclocks do
              DynArray.iter
                (fun l ->
                   DynArray.iter
                     (fun l' ->
                        if (Dbm.Alg.add l l' <= k) then(
                          let term =
                            (Bdd.dand (get_clock_literal enc x z l)
                               (get_clock_literal enc z y l'))
                          in
                        (*
                        printf "%d %d %s <- (%d %d %s) /\\ (%d %d %s)\n" 
                            x y (Dbm.Alg.to_string k)
                            x z (Dbm.Alg.to_string l)
                            z y (Dbm.Alg.to_string l');
                           *)
                          Queue.add term disj
                        )
                     ) preds.(z).(y)
                ) preds.(x).(z)
            done;
            (* Do the above loop for z=0, y<>0, and l'=0.
               This is because the constraint 0-y<=0 is missing from the predicates
            *)
            DynArray.iter
              (fun l ->
                 let l' = Dbm.Alg.zero in
                 let y = 0 in
                 let z = 0 in
                 (*
                 printf "%d %d %s <- (%d %d %s) /\\ (%d %d %s)\n" 
                   x y (Dbm.Alg.to_string k)
                   x z (Dbm.Alg.to_string l)
                   z y (Dbm.Alg.to_string l');
                    *)
                 if (Dbm.Alg.add l l' <= k) then(
                   let term =
                     (Bdd.dand (get_clock_literal enc x z l)
                        (get_clock_literal enc z y l'))
                   in
                   (*printf "%d %d %s <- (%d %d %s) /\\ (%d %d %s)\n" *)
                   Queue.add term disj
                 )
              ) preds.(x).(0);

            (*
            printf "LHS:\n"; flush stdout;
            Queue.iter (fun b -> print_bdd b; printf "\n\n"; flush stdout) disj;
            printf "RHS:\n"; flush stdout;
            print_bdd (get_clock_literal enc x y k);
            printf "\n";
               *)
            (* Make the implication (not disj --> (x,y,k)) *)
            let not_disj = Bdd.dnot (Bdd.dor_of_queue enc.enc_man disj)
            in
            let bdd = (Bdd.dor not_disj (get_clock_literal enc x y k)) in
            Queue.add bdd conj
          in
          DynArray.iter add_conjunct preds.(x).(y)
        )
      done;
    done;
    (match threshold with
       None -> conj
     | Some th ->
       merge_bdd_array_threshold enc conj th
    )
    (*
    Bdd.dand_of_queue enc.enc_man conj
       *)

  let make ta cpa man =
    (*let preds = (get_predicates cpa) in*)
    (*
    printf "Current clock abstraction:\n";
    for x = 0 to (nb_clocks ta)-1 do
      for y = 0 to (nb_clocks ta)-1 do
        printf "(%d,%d): " x y;
        DynArray.iter(fun b -> printf "%s " (Dbm.Alg.to_string b)) cpa.(x).(y);
        printf "\n";
      done;
    done;
       *)
    let (bddvar2clock_constraint, clock_constraint2bddvar)
      = register_clock_preds man cpa in
    if !Log.cegar_verbose then
      print_cpa_encoding ta (bddvar2clock_constraint, clock_constraint2bddvar);
    let enc =
      {enc_ta = ta;
       enc_cpa = cpa;
       enc_man = man;
       enc_vars = [||];
       enc_pvars = [||];
       enc_loc = [||];
       enc_ploc = [||];
       enc_loc_cube = Bdd.dtrue man;
       enc_ploc_cube = Bdd.dtrue man;
       enc_var_cube = Bdd.dtrue man;
       enc_pvar_cube = Bdd.dtrue man;
       enc_clock_cube = Bdd.dtrue man;
       enc_pclock_cube = Bdd.dtrue man;
       (*enc_clock_constraints = preds;*)
       enc_clock_predicates = (bddvar2clock_constraint, clock_constraint2bddvar);
       enc_reduce = Queue.create();
       enc_cache = Hashtbl.create 100
      }
    in
    (* Make clock cubes *)
    Hashtbl.keys bddvar2clock_constraint
    |>
    Enum.iter
      ( fun i->
          enc.enc_clock_cube <- Bdd.dand enc.enc_clock_cube (Bdd.ithvar man i);
          enc.enc_pclock_cube <- Bdd.dand enc.enc_pclock_cube (Bdd.ithvar man (i+1));
      );
    enc.enc_reduce <- encode_reduce ~threshold:Options.bdd_reduce_threshold enc;
    register_vars enc;
    register_locations enc;
    enc

  let print_info enc =
    (* Show discrete var encodings *)
    VarContext.iter
      (fun var i ->
         printf "<%s>: " var;
         Array.iter (fun b -> printf "%d " (Bdd.topvar b)) enc.enc_vars.(i);
         printf "\n";
         printf "<%s'>: " var;
         Array.iter (fun b -> printf "%d " (Bdd.topvar b)) enc.enc_pvars.(i);
         printf "\n"
      ) enc.enc_ta.vars;
    enc.enc_ta.procs
    |> Array.iteri (fun i proc ->
        printf "Encoding of locs of proc <%s> (w/ %d locs): " (proc.procName) (Array.length proc.procLocations);
        Array.iter (fun b -> printf "%d " (Bdd.topvar b)) enc.enc_loc.(i);
        printf " and ";
        Array.iter (fun b -> printf "%d " (Bdd.topvar b)) enc.enc_ploc.(i);
        printf "\n";
      )


  (* Utilities *)
  let bdd_of_location enc ?primed:(primed=false) proci loci =
    let bits = encoding_of_number ~size:(Array.length enc.enc_loc.(proci)) loci in
    let res =
      bits
      |>
      Array.fold_lefti
        (fun bdd i b ->
           let t =
             if primed then Bdd.dand bdd enc.enc_ploc.(proci).(i)
             else (
               enc.enc_loc.(proci).(i)
             )
           in
           if b then Bdd.dand bdd t
           else Bdd.dand bdd (Bdd.dnot t)
        ) (Bdd.dtrue enc.enc_man)
    in
    res

  let bdd_of_var enc ?primed:(primed=false) vari value =
    let bits = encoding_of_number ~size:(Array.length enc.enc_vars.(vari)) value in
    bits
    |>
    Array.fold_lefti
      (fun bdd i b ->
         let t =
           if primed then Bdd.dand bdd enc.enc_pvars.(vari).(i)
           else (
             enc.enc_vars.(vari).(i)
           )
         in
         if b then Bdd.dand bdd t
         else Bdd.dand bdd (Bdd.dnot t)
      ) (Bdd.dtrue enc.enc_man)

  let bdd_of_var_vector enc ?primed:(primed=false) vars =
      Array.mapi (bdd_of_var enc ~primed:primed) vars
      |>
      Bdd.dand_of_array enc.enc_man

    let bdd_of_location_vector enc ?primed:(primed=false) locs =
      Array.mapi (fun proci loci -> bdd_of_location enc ~primed:primed proci loci) locs
      |>
      Bdd.dand_of_array enc.enc_man
      (*Array.fold_left (fun bdd b -> Bdd.dand bdd b) (Bdd.dtrue enc.enc_man)*)

    let bdd_of_discrete_state ?primed:(primed=false) enc ds =
      let loc_bdd = bdd_of_location_vector enc ~primed:primed
          (Array.map (fun l-> l.locId) ds.stateLocs) in
      let var_bdd = bdd_of_var_vector enc ~primed:primed ds.stateVars in
      Bdd.dand var_bdd loc_bdd

    (** Extend_Size the given bit vector by padding most-significant bits with value false *)
    let extend_size enc e newsize =
      assert(newsize >= Array.length e);
      let e' = Array.make newsize (Bdd.dfalse enc.enc_man) in
      e
      |>
      Array.iteri
        (fun i b ->
           e'.(i) <- b
        );
      e'

    let rec bdd_of_disc_expression enc = function
      | Constant k ->
        if k < 0 then (
          Log.fatalf "Constant %d: Negative integers are not supported at this point" k;
          raise IncompatibleModelError
        );
        encoding_of_number k
        |> Array.map (fun b -> if b then Bdd.dtrue enc.enc_man else Bdd.dfalse enc.enc_man)
      | Variable id ->
        enc.enc_vars.(id)
      | Clock _ -> failwith "Clock found in discrete expression"
      | Product _ -> failwith "Product not yet supported"
      | Division _ -> failwith "Division not yet supported"
      | BoolNot e ->
        let b = bdd_of_disc_expression enc e in
        [|
          Array.fold_left (fun bdd bit -> Bdd.dand (Bdd.dnot bit) bdd) (Bdd.dtrue enc.enc_man) b
        |]
      | BoolAnd (e1,e2) ->
        let be1 = bdd_of_disc_expression enc e1 in
        let be2 = bdd_of_disc_expression enc e2 in
        let b1 = Bdd.dor_of_array enc.enc_man be1 in
        let b2 = Bdd.dor_of_array enc.enc_man be2 in
        [| Bdd.dand b1 b2 |]
      | BoolEq(e1,e2) ->
        let be1 = bdd_of_disc_expression enc e1 in
        let be2 = bdd_of_disc_expression enc e2 in
        let size = max (Array.length be1) (Array.length be2) in
        let be1 = extend_size enc be1 size in
        let be2 = extend_size enc be2 size in
        [|Bdd.dand_of_array enc.enc_man (Array.map2 (fun b1 b2 -> Bdd.eq b1 b2) be1 be2)|]
      | BoolNeq(e1,e2) ->
        bdd_of_disc_expression enc (BoolNot(BoolEq(e1,e2)))
      | Sum(e1,e2) ->
        (* https://en.wikipedia.org/wiki/Adder_(electronics) *)
        let be1 = bdd_of_disc_expression enc e1 in
        let be2 = bdd_of_disc_expression enc e2 in
        let size = max (Array.length be1) (Array.length be2) in
        let be1 = extend_size enc be1 size in
        let be2 = extend_size enc be2 size in
        let res = Array.make (size+1) (Bdd.dfalse enc.enc_man) in
        let retenue = ref (Bdd.dfalse enc.enc_man) in
        for i = 0 to size-1 do
          res.(i) <- Bdd.xor (Bdd.xor be1.(i) be2.(i)) !retenue;
          retenue := Bdd.dor (Bdd.dand be1.(i) be2.(i))
              (Bdd.dand !retenue (Bdd.xor be1.(i) be2.(i)))
        done;
        res.(size) <- !retenue;
        res
      | Subtraction(e1,e2) ->
        (* https://en.wikipedia.org/wiki/Adder_(electronics) *)
        let be1 = bdd_of_disc_expression enc e1 in
        let be2 = bdd_of_disc_expression enc e2 in
        let size = max (Array.length be1) (Array.length be2) in
        let be1 = extend_size enc be1 size in
        let be2 = extend_size enc be2 size in
        let res = Array.make (size) (Bdd.dfalse enc.enc_man) in
        let borrow = ref (Bdd.dfalse enc.enc_man) in
        for i = 0 to size-1 do
          res.(i) <- Bdd.xor (Bdd.xor be1.(i) be2.(i)) !borrow;
          borrow := Bdd.dor_of_array enc.enc_man
              [|Bdd.dand (Bdd.dnot be1.(i)) !borrow;
                Bdd.dand (Bdd.dnot be1.(i)) be2.(i);
                Bdd.dand be2.(i) !borrow
              |]
        done;
        res
    (** Make BDD for the following cases:
        outcome = 0 -> be1 == be2
        outcome > 0 -> be1 > be2
        outcome < 0 -> be1 < be2
    **)
    let make_comparator enc outcome be1 be2 = 
      let size = max (Array.length be1) (Array.length be2) in
      let be1 = extend_size enc be1 size in
      let be2 = extend_size enc be2 size in
      let x = Array.map2 Bdd.eq be1 be2 in
      if outcome = 0 then (
        Bdd.dand_of_array enc.enc_man x
      ) else (
        let bdd = ref (Bdd.dfalse enc.enc_man) in
        for i = 0 to size - 1 do
          let q = Queue.create () in
          if outcome < 0 then (
            Queue.add (Bdd.dnot be1.(i)) q;
            Queue.add be2.(i) q;
          ) else (
            Queue.add be1.(i) q;
            Queue.add (Bdd.dnot be2.(i)) q;
          );
          for j = i+1 to size -1 do
            Queue.add x.(j) q
          done;
          bdd := Bdd.dor !bdd (Bdd.dand_of_array enc.enc_man (Array.of_enum(Queue.enum q)))
        done;
        !bdd
      )

    (* https://en.wikipedia.org/wiki/Digital_comparator *)
    let rec bdd_of_atomic_disc_guard enc = function
      | GuardEqual(e1,e2) ->
        let b = bdd_of_disc_expression enc (BoolEq(e1,e2)) in
        b.(0)
      | GuardNeq(e1,e2) ->
        let b = bdd_of_disc_expression enc (BoolNeq(e1,e2)) in
        b.(0)
      | GuardLess(e1,e2) ->
        let be1 = bdd_of_disc_expression enc e1 in
        let be2 = bdd_of_disc_expression enc e2 in
        make_comparator enc (-1) be1 be2
      | GuardGreater(e1,e2) ->
        let be1 = bdd_of_disc_expression enc e1 in
        let be2 = bdd_of_disc_expression enc e2 in
        make_comparator enc 1 be1 be2
      | GuardLeq(e1,e2) ->
        Bdd.dor (bdd_of_atomic_disc_guard enc (GuardEqual(e1,e2)))
          (bdd_of_atomic_disc_guard enc (GuardLess(e1,e2)))
      | GuardGeq(e1,e2) ->
        Bdd.dor (bdd_of_atomic_disc_guard enc (GuardEqual(e1,e2)))
          (bdd_of_atomic_disc_guard enc (GuardGreater(e1,e2)))

    let bdd_of_disc_guard enc g =
      g
      |> List.map (bdd_of_atomic_disc_guard enc)
      |> List.enum
      |> Array.of_enum
      |> Bdd.dand_of_array enc.enc_man


    (** Not reduced *)
    let bdd_of_clock_guard enc g =
      let rec of_ag = function
        | GuardLeq(Clock(c),Constant k) ->
          over_approximate_clock_constraint enc (c,0,Dbm.Alg.weak_from_int k)
        | GuardLess(Clock(c),Constant k) ->
          over_approximate_clock_constraint enc (c,0,Dbm.Alg.strict_from_int k)
        | GuardGeq(Clock(c),Constant k) ->
          over_approximate_clock_constraint enc (0,c,Dbm.Alg.weak_from_int (-k))
        | GuardGreater(Clock(c),Constant k) ->
          over_approximate_clock_constraint enc (0,c,Dbm.Alg.strict_from_int (-k))
        | GuardEqual(Clock(c),Constant k) ->
          Bdd.dand
            (of_ag (GuardGeq(Clock(c), Constant k)))
            (of_ag (GuardLeq(Clock(c), Constant k)))

        (* diagonal guards *)
        | GuardLeq(Subtraction(Clock(c1), Clock(c2)), Constant k) ->
          over_approximate_clock_constraint enc (c1,c2,(Dbm.Alg.weak_from_int k))
        | GuardLess(Subtraction(Clock(c1), Clock(c2)), Constant k) ->
          over_approximate_clock_constraint enc (c1,c2,(Dbm.Alg.strict_from_int k))
        | GuardGreater(Subtraction(Clock(c1), Clock(c2)), Constant k) ->
          over_approximate_clock_constraint enc (c2,c1,(Dbm.Alg.strict_from_int (-k)))

        | GuardGeq(Subtraction(Clock(c1), Clock(c2)), Constant k) ->
          over_approximate_clock_constraint enc (c2,c1,(Dbm.Alg.weak_from_int (-k)))

        | GuardEqual(Subtraction(Clock(c1), Clock(c2)), Constant k) ->
          Bdd.dand
          (over_approximate_clock_constraint enc (c2,c1,(Dbm.Alg.weak_from_int (-k))))
          (over_approximate_clock_constraint enc (c1,c2,(Dbm.Alg.weak_from_int k)))
        | ag ->
          failwith "This should be a pure clock guard"
      in
      let bdd_guard =
        List.map of_ag g
        |> Bdd.dand_of_list enc.enc_man
      in
      (*
      printf "Guard: %s\n" (string_of_guard enc.enc_ta g); flush stdout;
      print_bdd bdd_guard;
      printf "\n";
         *)
      bdd_guard
        (*
      let compute_up_next =
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
          let res = ref states in
          Queue.iter
            (fun p ->
               let pos,neg = Bdd.cofactors (Bdd.topvar p) !res in
               res := Bdd.dor pos (Bdd.dand (Bdd.dnot p) neg)
            ) up_preds;
          !res
      in
      (* test *)
      printf "Guard: %s\n" (string_of_guard enc.enc_ta g); flush stdout;
      print_bdd bdd_guard;
      let dbm = (dbm_of_minterm enc (Bdd.pick_minterm bdd_guard)) in
      printf "\nDbm derived from the bdd:\n%s\n" (Dbm.to_string dbm);
      Dbm.posttime dbm;
      printf "\nUp:\n%s\n" (Dbm.to_string dbm);
      (*
      let cube = cube_of_dbm enc dbm in
         *)
      let reduce = encode_reduce ~mode:Reduce_All enc in
      let reduce_up = encode_reduce ~mode:Reduce_Up enc in
      printf "|reduce|=%d\n" (Bdd.size reduce);
      printf "|reduce_up|=%d\n" (Bdd.size reduce_up);
      (*
      printf "|reduce|=%d\n" (Bdd.size reduce);
         *)
      let up = Bdd.dand reduce_up (compute_up_next (Bdd.dand reduce bdd_guard)) in
      (*
      printf "|reduce|=%d\n" (Bdd.size reduce);
      printf "|up|=%d\n" (Bdd.size up);
         *)

      printf "Enumerating all up regions by BDD op:\n";
      let zones = Bdd.minterms enc.enc_man up in
      Enum.iter
        (fun mt ->
           (*
           print_clock_constraint_mincube enc mt;
              *)
           let d = dbm_of_minterm enc mt in
           if not (Dbm.leq d dbm) then (
             printf "\nFollowing not included:\n";
             printf "%s\n\n" (Dbm.to_string d);
             failwith ""
           ) else (printf "."; flush stdout)
        ) zones;
      (*
      printf "BDD derived from that dbm: ";  flush stdout;
      print_bdd cube;
      printf "\n"; flush stdout;
      let dbm = (dbm_of_minterm enc (Bdd.pick_minterm bdd_guard)) in
      printf "\nLast sanity check:\n%s\n" (Dbm.to_string dbm);
         *)
      bdd_guard
           *)

    (** Not reduced *)
    let bdd_of_invariant enc =
      let invar = ref (Bdd.dtrue enc.enc_man) in
      Array.iter
        (fun proc ->
           Array.iter
              (fun loc ->
                if (loc.locInvar <> []) then (
                  let loc_cube = bdd_of_location enc proc.procId loc.locId in
                  invar :=
                    Bdd.dand !invar
                      (* loc_cube -> invar of loc *)
                      (Bdd.dor
                         (Bdd.dnot loc_cube)
                         (bdd_of_clock_guard enc loc.locInvar)
                      )
                )
              )
              proc.procLocations
        ) enc.enc_ta.procs;
      !invar


    (* check *)
    let bdd_of_disc_update enc ups =
      ups
      |> List.map
        (fun (vari,exp) ->
           let pvar =  enc.enc_pvars.(vari) in
           let nexp = ref (bdd_of_disc_expression enc exp) in
           if Array.length !nexp > Array.length pvar then (
             Log.warningf "Following expression assigned to %s requires more bits than the variable itself" (VarContext.var_of_index enc.enc_ta.vars vari);
             Log.warningf "%s\n" (Uautomaton.string_of_exp enc.enc_ta exp);
             nexp := Array.sub !nexp 0 (Array.length pvar)
           ) else if (Array.length !nexp < Array.length pvar) then(
             nexp := extend_size enc !nexp (Array.length pvar)
           );
           (*
             Log.warning (sprintf "Expression assigned to %s requires %d bits and the variable is %d\n" (VarContext.var_of_index enc.enc_ta.vars vari) (Array.length nexp) (Array.length pvar));
             Log.warningf "\t%s\n" (Uautomaton.string_of_exp enc.enc_ta exp);
              *)
           make_comparator enc 0 pvar !nexp
        )
      |> Array.of_list
      |> Bdd.dand_of_array enc.enc_man

    (** Transition relation of a single discrete transition with the clock guards but not
        resets.
        Not reduced.
    *)
    let rec bdd_of_disc_transition enc trans =
      (* make a bdd /\ l=l' for all processes except for excluded_procs *)
      let identity excluded_procs excluded_vars =
        let id_loc =
          Array.fold_lefti
            (fun acc pi p ->
               if List.mem pi excluded_procs then
                 acc
               else
                 make_comparator enc 0 enc.enc_loc.(pi) enc.enc_ploc.(pi)
                 |> Bdd.dand acc
            ) (Bdd.dtrue enc.enc_man) enc.enc_ta.procs
        in
        let id_var =
          Enum.fold
            (fun acc i ->
               if List.mem i excluded_vars then
                 acc
               else
                 Bdd.dand acc (make_comparator enc 0 enc.enc_vars.(i) enc.enc_pvars.(i))
                 (*
                 let tmp = make_comparator enc 0 enc.enc_vars.(i) enc.enc_pvars.(i)
                 in
                 printf "acc:"; flush stdout; print_bdd acc; printf "\n"; flush stdout;
                 printf "eq:"; flush stdout; print_bdd tmp; printf "\n"; flush stdout;
                 let acc' = Bdd.dand tmp acc in
                 printf "acc':";flush stdout; print_bdd acc'; printf "\n"; flush stdout; 
                 acc'
                    *)
            ) (Bdd.dtrue enc.enc_man) (0--((VarContext.size enc.enc_ta.vars)-1))
        in
        (*
        printf "id_loc:\n"; flush stdout;
        print_bdd id_loc;
        printf "\n";
        printf "id_var:\n"; flush stdout;
        print_bdd id_var;
        printf "-\n"; flush stdout;
           *)
        let res = Bdd.dand id_var id_loc in
        (*
        printf "id_loc:\n"; flush stdout;
        print_bdd res;
        printf "\n--\n"; flush stdout;
           *)
        res
      in
      (* This does not include the identity relation for remaining processes 
         Returns pairs of disc_edge_rel * clock_guard
      *)
      let local_edge edge =
          let src = bdd_of_location enc edge.edgeProc edge.edgeSource in
          let tgt = bdd_of_location enc ~primed:true edge.edgeProc edge.edgeTarget in
          let grd = bdd_of_disc_guard enc edge.edgeDiscGuard in
          let clock_grd = bdd_of_clock_guard enc edge.edgeGuard in
          let up = bdd_of_disc_update enc edge.edgeDiscUpdate in
          (Bdd.dand_of_array enc.enc_man [|src;tgt;grd;up;clock_grd|]), clock_grd
      in
      (* The final bdd is obtained by adding the identity relation for locations not participating*)
      let result =
        match trans with
        | Single edge ->
          let up_vars = List.map fst edge.edgeDiscUpdate in
          let disc_rel, grd = (local_edge edge) in
          (Bdd.dand disc_rel (identity [edge.edgeProc] up_vars)), grd
        | Pair(edge1,edge2) ->
          let up_vars = List.map fst edge1.edgeDiscUpdate @ List.map fst edge2.edgeDiscUpdate in
          let disc_rel1, grd1 = (local_edge edge1) in
          let disc_rel2, grd2 = (local_edge edge2) in
          (Bdd.dand_of_array enc.enc_man
            [|disc_rel1; disc_rel2;
              identity [edge1.edgeProc; edge2.edgeProc] up_vars|]),
          (Bdd.dand grd1 grd2)
      in
      (*
      print_bdd result;
      print_string "\n"; Format.print_flush();
         *)
      result

    (* test *)
    let bdd_array_of_committed enc =
      enc.enc_ta.procs
      |>
      Array.map
        (fun proc ->
           Array.filter (fun l -> l.locCommitted) proc.procLocations
           |> Array.map (fun l -> bdd_of_location enc proc.procId l.locId)
           |> Bdd.dor_of_array enc.enc_man
        )

    (* test *)
    let bdd_array_of_urgent enc =
      enc.enc_ta.procs
      |>
      Array.map
        (fun proc ->
           Array.filter (fun l -> l.locUrgent) proc.procLocations
           |> Array.map (fun l -> bdd_of_location enc proc.procId l.locId)
           |> Bdd.dor_of_array enc.enc_man
        )

    let bdd_of_init_discrete_state enc =
      bdd_of_discrete_state enc enc.enc_ta.Uautomaton.init

    (* TODO Rewrite using get_minterm and ignore top variables*)
    let discrete_state_of_cube enc mt =
      let nb_procs = (Array.length enc.enc_ta.procs) in
      let nb_vars = (VarContext.size enc.enc_ta.vars) in
      let locs = Array.make nb_procs 0 in
      let vars = Array.make nb_vars 0 in
      let x = ref 1 in
      for i = 0 to nb_procs - 1 do
        x := 1;
        for j = 0 to (Array.length enc.enc_loc.(i)) - 1 do
          let inter = (Bdd.dand enc.enc_loc.(i).(j) mt) in
          if not(Bdd.is_false inter) then(
            locs.(i) <- locs.(i) + !x;
          );
          x := !x * 2;
        done;
      done;
      for i = 0 to nb_vars - 1 do
        x := 1;
        for j = 0 to (Array.length enc.enc_vars.(i)) - 1 do
          if not(Bdd.is_false (Bdd.dand enc.enc_vars.(i).(j) mt)) then(
            vars.(i) <- vars.(i) + !x;
          );
          x := !x * 2;
        done;
      done;
      {stateLocs = (Array.mapi (fun i il ->
           (*printf "Proc(%d) at %d\n" i il;*)
           enc.enc_ta.procs.(i).procLocations.(il)
         )) locs;
       stateVars = vars
      }


    let unprime_locations_and_vars enc bdd =
      (* TODO use memoization if useful.
         see varmap, and ~memo argument in permute *)
      let ar = Array.init (Man.get_bddvar_nb enc.enc_man) (fun i -> i) in
      for pi = 0 to (Array.length enc.enc_ta.procs)-1 do
        Array.iter2 (fun bi bi' -> ar.(Bdd.topvar bi') <- Bdd.topvar bi)
          enc.enc_loc.(pi)
          enc.enc_ploc.(pi)
      done;
      for i = 0 to (Array.length enc.enc_vars)-1 do
        Array.iter2 (fun bi bi' -> ar.(Bdd.topvar bi') <- Bdd.topvar bi)
          enc.enc_vars.(i)
          enc.enc_pvars.(i)
      done;
      Bdd.permute bdd ar

    let prime_locations_and_vars enc bdd =
      let ar = Array.init (Man.get_bddvar_nb enc.enc_man) (fun i -> i) in
      for pi = 0 to (Array.length enc.enc_ta.procs)-1 do
        Array.iter2 (fun bi bi' -> ar.(Bdd.topvar bi) <- Bdd.topvar bi')
          enc.enc_loc.(pi)
          enc.enc_ploc.(pi)
      done;
      for i = 0 to (Array.length enc.enc_vars)-1 do
        Array.iter2 (fun bi bi' -> ar.(Bdd.topvar bi) <- Bdd.topvar bi')
          enc.enc_vars.(i)
          enc.enc_pvars.(i)
      done;
      Bdd.permute bdd ar

    let unprime_clock_preds enc bdd =
      let ar = Array.init (Man.get_bddvar_nb enc.enc_man) (fun i -> i) in
      Hashtbl.keys (fst enc.enc_clock_predicates)
      |>
      Enum.iter
        ( fun i->
            ar.(i+1) <- i;
            ar.(i) <- i
        );
      Bdd.permute bdd ar

    let prime_clock_preds enc bdd =
      let ar = Array.init (Man.get_bddvar_nb enc.enc_man) (fun i -> i) in
      Hashtbl.keys (fst enc.enc_clock_predicates)
      |>
      Enum.iter
        ( fun i->
            ar.(i) <- i+1;
        );
      Bdd.permute bdd ar


    let rec bdd_of_query enc = function
      | EmptyQuery -> Bdd.dfalse enc.enc_man
      | AndQuery(q1,q2) -> Bdd.dand (bdd_of_query enc q1) (bdd_of_query enc q2)
      | OrQuery(q1,q2) -> Bdd.dor (bdd_of_query enc q1) (bdd_of_query enc q2)
      | NotQuery(q) -> Bdd.dnot (bdd_of_query enc q)
      | AtomicQuery(proci,loc) -> bdd_of_location enc proci loc.locId


end
