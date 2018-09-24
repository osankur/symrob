open Batteries
open Printf
open ClockPredicateAbstraction
open Uta
open Common
open Str
open Pdbm
open Stats
open TimedAutomaton

(** Raised when the present algorithm rejects the given model 
    based on syntactic criteria *)
exception IncompatibleModelError

let bdd_config = "flatten_hierarchy\n
encode_variables\n
build_model -m Iwls95CP\n
dynamic_var_ordering -f sift_converge\n
check_invar\n
show_traces -v\n
quit\n
"

let ic3_config = "flatten_hierarchy\n
encode_variables\n
build_boolean_model\n
check_invar_ic3\n
show_traces -v\n
quit\n
"

(** From the abstraction abs, extract the constraints that will appear
    as variables (predicates) in the abstract model.
    Recall that we only keep predicates on pairs (x,y) with x>y.
    Entries of (x,y) with x<y in the abstraction table are translated
    to a predicate on y - x (via x-y<k <=> not (y-x<=-k))

    FIXME There is a bug here.
    We remove the constraints of type (0 - y <= 0) since they are useless and
    we don't want to create the variable p_0_y_w0 which is always true.
    However these constraints are required in the reduce constraint
    to compute all triangular inequalities

    FIXME Refactoring on the way. This is to be accessed both by CuddCegar and 
    SymbolicCegar modules.
*)
let get_predicates abs =
  let module Dbm = Pdbm.Guard in
  let module ConstrSet =Set.Make(struct type t = Dbm.Alg.t let compare=compare end) in
  (* so that we iterate through 0..nb_clocks *)
  let nb_clocks = (Array.length abs) - 1 in
  let ar =
    Array.mapi
      (fun x ar ->
         (Array.mapi
            (fun y vls ->
               if ( x > y ) then (
                 let s1 =
                   DynArray.to_list abs.(x).(y)
                   |> List.fold_left (fun acc vl -> ConstrSet.add vl acc) ConstrSet.empty
                 in
                 (* y-x <= k <-> x-y < -k  and y-x < k <-> x-y <= -k *)
                 DynArray.to_list abs.(y).(x)
                 |> List.map Dbm.Alg.invert_raw
                 |> List.fold_left (fun acc vl -> ConstrSet.add vl acc) s1
                 |> ConstrSet.elements
                 (* We have x > 0. Eliminate p_x_0_s_0 *)
                 |> (fun l -> if y = 0 then
                        List.filter (fun r -> r >= (0,DBM_WEAK)) l
                      else l)
               ) else (
                 []
               )
            )
         ) ar
      ) abs
  in
  for x = 0 to nb_clocks do
    for y = x+1 to nb_clocks do
      ar.(x).(y) <- List.map
          (fun b -> Dbm.Alg.invert_raw b)
          ar.(y).(x)
    done
  done;
  printf "Printing clock *predicates*:\n";
  for x = 0 to nb_clocks do
    for y = 0 to nb_clocks do
      printf "(%d,%d): " x y;
      List.iter(fun b -> printf "%s " (Dbm.Alg.to_string b)) ar.(x).(y);
      printf "\n";
    done;
  done;
  ar




(**
   Encodes timed automata models into SMV and reads back counter examples.

   All discrete variables are encoded straighforwardly,
   and the guard and update expressions are copied directly from the Uppaal model.
   Clocks are represented using only a restricted set of constraint x-y<k
   given by a CPABSTRACTION module.
   One step of the timed automaton is performed between 2 and 3+k cycles depending
   on the number of clocks that are reset. These are called reset, reset1, ..,resetk,up.

   At each step, the mode is the next operation to be applied.

   Example.
   In order to simulate a tau-transition e :(l, v) -- g, R --> (l',v'), say R={1,2}

   s1 : [mode = up; loc0 = l; e1 = e; P1]        -- provided next(P1) |= g.
        Choice of edges in the next state
   s2 : [mode = reset1; P2; ..]                  -- with P2 = up(P1)
   s3 : [mode = reset; P3; ..]                   -- with P3 in reset_1(P2)
        Update of locations in the next state
   s4 : [mode = up; P4; loc0=l'; e1=e'; ..]      -- with P4 in reset_2(P3), choice of new e' provided next(P5) |= g(e')


   Thus the clocks are reset one by one. This order is arbitrarily chosen and is induced by the
   array in the smv_encoding structure (they are reset from last to first).
   For n clock resets, the system visits modes reset(n), reset(n-1), ..., reset1, reset
   If there is no clock reset, then it immediately moves to reset. Disc updates are also 
   done during mode reset.
*)

module SMVInterfaceMaker =
struct
  module Dbm = Pdbm.Guard
  module CPAbs = ClockPredicateAbstraction
  module TA = TimedAutomaton.Uautomaton
  module EdgeIndexer = Indexer(struct type t = TA.edge end)
      (struct
        type t = TA.edge
        let equal = (==)
        let hash = Hashtbl.hash
      end
      )
  module EdgeMap = Hashtbl.Make(struct
      type t = TA.edge
      let equal = (==)
      let hash = Hashtbl.hash
    end
    )

  (** Additional or custom syntactic utilities for BTA *)
  module TAUtilities = 
    struct

    (**
       Evaluation of an expression with constants and constant variables.
       This is a custom implementation of similar functions in the Uppaalta module.
       @param reject_nonconst when set to true, an exception is raised whenever
       the expression contains non-constant elements such as Variable(i) otherwise
       these are kept
    *)
    let rec const_eval_exp ?reject_nonconst:(reject_nonconst=true) bta =
      let reject () =
        Log.fatal "Only constant expressions or variables can be used as array indices";
        raise IncompatibleModelError
      in
      let open TA in
      function
      | Constant c -> Constant c
      | Clock c -> Clock c
      | Variable(i) ->
        if reject_nonconst then (
          Log.fatal
            (sprintf "Found \"Variable(%d)=%s\". Only constants or constant variables are allowed inside guards." i 
               (VarContext.var_of_index bta.TA.vars i));
          raise IncompatibleModelError
        ) else (
          Variable(i)
        )
      | Product(e1, e2) -> (match const_eval_exp bta e1, const_eval_exp bta e2 with
          | (Constant c1), (Constant c2) -> Constant (c1 * c2)
          | e1', e2' ->
            if reject_nonconst then reject()
            else Product(e1',e2')
        )
      | Sum(e1,e2) ->
        (match const_eval_exp bta e1, const_eval_exp bta e2 with
         | (Constant c1), (Constant c2) -> Constant (c1 + c2)
         | e1', e2' ->
           if reject_nonconst then reject()
           else Sum(e1',e2')
        )
      | Subtraction(e1,e2) ->
        (match const_eval_exp bta e1, const_eval_exp bta e2 with
         | (Constant c1), (Constant c2) -> Constant (c1 - c2)
         | e1', e2' ->
           if reject_nonconst then reject()
           else Subtraction(e1',e2')
        )
      | Division(e1,e2)->
        (match const_eval_exp bta e1, const_eval_exp bta e2 with
         | (Constant c1), (Constant c2) -> Constant (c1 / c2)
         | e1', e2' ->
           if reject_nonconst then reject()
           else Division(e1',e2')
        )
      | BoolNot(e) ->
        (match const_eval_exp bta e with
        | (Constant c) -> if c <> 0 then (Constant 1) else Constant 0
        | _ as e' -> if reject_nonconst then reject() else (BoolNot e'))
      | BoolAnd(e1,e2) ->
        (match const_eval_exp bta e1, const_eval_exp bta e2 with
         | (Constant c1), (Constant c2) ->
           if c1 <> 0 && c2 <> 0 then (Constant 1)
           else (Constant 0)
         | (e1',e2') -> if reject_nonconst then reject()
               else (BoolAnd (e1',e2'))
        )
      | BoolEq(e1,e2) ->
        (match const_eval_exp bta e1, const_eval_exp bta e2 with
         | (Constant c1), (Constant c2) ->
           if c1 = c2 then (Constant 1)
           else (Constant 0)
         | (e1',e2') -> if reject_nonconst then reject()
               else (BoolEq (e1',e2'))
        )
      | BoolNeq(e1,e2) ->
        (match const_eval_exp bta e1, const_eval_exp bta e2 with
         | (Constant c1), (Constant c2) ->
           if c1 <> c2 then (Constant 1)
           else (Constant 0)
         | (e1',e2') -> if reject_nonconst then reject()
               else (BoolNeq (e1',e2'))
        )

    let rec eval_bta_ag ta ag =
      let eval = const_eval_exp ta in
      (match ag with
       | TA.GuardLeq(a,b) -> TA.GuardLeq(eval a, eval b)
       | TA.GuardLess(a,b) -> TA.GuardLess(eval a, eval b)
       | TA.GuardEqual(a,b) -> TA.GuardEqual(eval a, eval b)
       | TA.GuardNeq(a,b) -> TA.GuardNeq(eval a, eval b)
       | TA.GuardGeq(a,b) -> TA.GuardGeq(eval a, eval b)
       | TA.GuardGreater(a,b) -> TA.GuardGreater(eval a, eval b)
      )

  end

  (** Provides semantic functions for BTA such as
      DBM encoding for guards *)
  module BTASemantics =
  struct

    let dbm_of_constraints bta constrlist =
      let nclocks = TA.nb_clocks bta in
      let dbm = Dbm.create nclocks in
      List.iter (fun (x,y,b) -> (Dbm.constrain dbm x y b)) constrlist;
      dbm

    let guard_to_dbm bta g =
      let dbm  = Dbm.create ((TA.nb_clocks bta)) in
      let open TA in
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
      guard_to_dbm bta e.TA.edgeGuard

    let dbm_invariant_of_state = TA.invariant_of_discrete_state

  end



  (** Light bool_expr type that helps dump formulas *)
  type bool_expr = And of bool_expr list |
                   Or of bool_expr list |
                   Not of bool_expr |
                   Value of string

  (** A symbolic path is a list of symbolic_state which is a pair made of
      1) the last operation applied
      2) current state
      so that the last operation has led to the current state.
      The operations are time up, or reset of given clock through an edge(s).
      A tau-transition along an edge e=(l,g,[r1;r2;r3),l') is encoded as follows (provided l not committed or urgent)

      Sym_Up(l,true)
      Sym_Edge(l,(Single e), Some r1, false)
      Sym_Reset(l, (Single e), r2, false)
      Sym_Reset(l, (Single e), r3, true)

      The last boolean being a flag indicating the last reset so that the invariant can be applied

  type symbolic_transition =
      Sym_Up of BTA.location array * bool (* current location and whether time can elapse *)
    | Sym_Reset of BTA.location array * BTA.edge * clock_t * bool
    | Sym_Tau of BTA.location array * BTA.edge * (clock_t option) * bool
    | Sym_Sync of BTA.location array * BTA.edge * BTA.edge * (clock_t option) * bool
  *)
  type 'a single_or_pair = 
    Single of 'a
    | Pair of 'a * 'a

  type symbolic_transition =
      Sym_Up of TA.location array * bool (* current location and whether time can elapse *)
    | Sym_Edge of TA.location array * TA.edge single_or_pair * (clock_t option) * bool
    | Sym_Reset of TA.location array * TA.edge single_or_pair * clock_t * bool

  type symbolic_state = symbolic_transition * Guard.Alg.t list

  let string_of_symbolic_transition bta =
    let string_of_clock_option = function
      None -> ""
      | Some(x) -> sprintf "%d" x
    in
    function
    | Sym_Up(loc, b) -> sprintf "Up(%b)" b
    | Sym_Edge(lar, (Single e),res, b) ->
      sprintf "TAU: %s | Resetting <%s> | Last: %b"
        (TA.string_of_edge bta e) (string_of_clock_option res) b
    | Sym_Edge(lar, Pair(e1,e2),res, b) ->
      sprintf "SYNC:\n%s\n%s\n\t| Resetting <%s> | Last: %b"
        (TA.string_of_edge bta e1)  (TA.string_of_edge bta e2) (string_of_clock_option res) b
    | Sym_Reset(loc, edge, i, b) ->
      sprintf "Resetting: %d | Last: %b" i b

  let string_of_symbolic_path bta path =
    let buf = Buffer.create 1024 in
    let c = ref 1 in
    List.iter
      (fun (trans, constr) ->
         Buffer.add_string buf (sprintf "STATE %d:\n" !c);
         incr c;
         Buffer.add_string buf (string_of_symbolic_transition bta trans);
         Buffer.add_string buf "\n";
         List.iter (fun (x,y,r) ->
             Buffer.add_string buf (sprintf "x%d - x%d %s\n" x y (Dbm.Alg.to_string r))
           ) constr
      ) path;
    Buffer.contents buf

  let check_syntax bta = true
  (* TODO
     Reject chan arrays with non-constant expressions
     (this cannot be encoded in nusmv)
     Reject non-constant guards
     Only accept rectangular guards
     Reject chan arrays for now, we should later authorize constant indices
     Reject clock arrays (already the case)
     Reject clock updates other than resets
     Reject discrete variables with no range
     Reject reserved keywords such as mode, e1, e2, ...
  *)


  let string_of_edge_id bta indexer id =
    let edge = EdgeIndexer.get_key indexer id in
    TA.string_of_edge bta edge

  (**
     Returns the predicate name encoding the given constraint. 
     Encoding:
        x - y < 10     ->     p_x_y_s_10
        x - y <= 10    ->     p_x_y_w_10
        x - y < -10    ->     p_x_y_s_m10

     @pre x > y (this is the convention)
     @see literal_of_constraint
     @see constraint_of_predicate
  *)
  let predicate_of_constraint (x,y,(k,ineq)) =
    if x > y then (
        sprintf "p_%d_%d_%s_%s" x y
          (if ineq = DBM_WEAK then "w" else "s")
          (if k < 0 then sprintf "m%d" (-k) else string_of_int k)
    ) else (
      failwith "Clock predicates in the CEGAR algorithm are only defined for 
constraints (x,y,_) with x>y"
    )

  (** Returns the literal corresponding to the given constraint *)
  let literal_of_constraint ((x,y,(k,ineq)) as c) =
    let not_ineq = match ineq with DBM_WEAK -> DBM_STRICT | DBM_STRICT -> DBM_WEAK in
    if x > y then (
      Value (predicate_of_constraint c)
    ) else
      Not( Value (predicate_of_constraint (y,x,(-k, not_ineq))))

  (** Parses given predicate name into a clock constraint
  *)
  let constraint_of_predicate pr =
    let re = regexp "p_\\([0-9]*\\)_\\([0-9]*\\)_\\(s\\|w\\)_\\([0-9]*\\)" in
    if not (string_match re pr 0 ) then
      failwith (sprintf "Following string could not be parsed as a clock predicate: %s" pr);
    let x = matched_group 1 pr |> int_of_string in
    let y = matched_group 2 pr |> int_of_string in
    let ineq = match matched_group 3 pr with
        "w" -> DBM_WEAK
      | "s" -> DBM_STRICT
      | _ -> failwith "should not happen"
    in
    let b = matched_group 4 pr |> int_of_string in
    (x,y,(b,ineq))

  let next_literal_of_constraint ((x,y,(k,ineq)) as c) =
    let not_ineq = match ineq with DBM_WEAK -> DBM_STRICT | DBM_STRICT -> DBM_WEAK in
    if x > y then (
      Value (sprintf "next(%s)" (predicate_of_constraint c))
    ) else
      Not( Value (sprintf "next(%s)" (predicate_of_constraint (y,x,(-k, not_ineq)))))

  let rec string_of_bool_expr =
      function
      | Value s -> s
      | Or([]) -> "FALSE"
      | Or(l) ->
        sprintf "(%s)"
          (
            (List.map string_of_bool_expr l)
            |> String.join " | "
          )
      | And([]) -> "TRUE"
      | And(l) ->
        sprintf "(%s)"
          (
            (List.map string_of_bool_expr l)
            |> String.join " & "
          )
      | Not(e) ->
        sprintf "!(%s)" (string_of_bool_expr e)

  (** Returns a conjunction of literals which encodes the over-approximation
      of the given guard in the abstraction abs.
      When next is set to true, the predicates are next-state variables.
  *)
  let encode_guard bta abs ?next:(next=false) g =
    let over_approximate = CPAbs.over_approximate abs in
    let under_approximate = CPAbs.under_approximate abs in
    let cube = Queue.create() in
    let open TA in
    let add_lit ?negate:(negate=false) = function
      | (_,_,None) -> ()
      | (x,y,Some(b)) ->
        let lit =
          (* This guard is trivially true
          and there is no corresponding predicate in the model *)
          if y = 0 && (Dbm.Alg.compare b Dbm.Alg.zero < 0) then 
            Value "FALSE"
          else
          if not next then
            (literal_of_constraint (x,y,b))
          else (
            (next_literal_of_constraint (x,y,b))
          )
        in
        let lit = if negate then Not(lit) else lit in
        (*
        printf "%s : (%d,%d,%s)\n" (string_of_bool_expr lit)
          x y (Dbm.Alg.to_string b);
           *)
        Queue.add lit cube
    in
    let rec approximate = function
      (* rectangular guards *)
      | GuardLeq(Clock cl,Constant k) -> add_lit
                           (cl, 0, over_approximate cl 0 (k,DBM_WEAK))
      | GuardLess(Clock cl, Constant k) ->
          add_lit
            (cl, 0, over_approximate cl 0 (k,DBM_STRICT))
      | GuardGreater(Clock cl,Constant k) ->
        let b = under_approximate cl 0 (k, DBM_WEAK) in
        add_lit ~negate:true (cl,0,b)
      | GuardGeq(Clock cl,Constant k) ->
        (* if k <= 0 then this is trivial *)
        if k > 0 then (
          let b = under_approximate cl 0 (k, DBM_STRICT) in
          add_lit ~negate:true (cl,0,b)
        )
      | GuardEqual(Clock cl,Constant k) ->
        approximate (GuardLeq(Clock cl,Constant k));
        approximate (GuardGeq(Clock cl,Constant k))

      (* diagonal guards *)
      | GuardLeq(Subtraction(Clock c1, Clock c2),Constant k) ->
        (*
        if c1 = 1 && c2 = 3 then (
          CPAbs.print bta abs;
          printf "Got X%d - X%d <= %d ---->" c1 c2 k ;
          (match (over_approximate c1 c2 (k,DBM_WEAK)) with
             None -> printf "INF\n"
           | Some(r) -> printf "%s\n" (Dbm.Alg.to_string r)
          );
        );
           *)
        if c1 >= c2 then
          add_lit (c1, c2, over_approximate c1 c2 (k,DBM_WEAK))
        else (
          add_lit ~negate:true (c2, c1, under_approximate c2 c1 (-k,DBM_STRICT))
        )
      | GuardLess(Subtraction(Clock c1, Clock c2),Constant k) ->
        if c1 >= c2 then
          add_lit (c1, c2, over_approximate c1 c2 (k,DBM_STRICT))
        else
          add_lit ~negate:true (c2, c1, under_approximate c2 c1 (-k,DBM_WEAK))

      | GuardGeq(Subtraction(Clock c1, Clock c2),Constant k) ->
        if c1 >= c2 then (
          let b = under_approximate c1 c2 (k, DBM_STRICT) in
          add_lit ~negate:true (c1,c2,b)
        ) else (
          add_lit (c2, c1, over_approximate c2 c1 (-k,DBM_WEAK))
        )
      | GuardGreater(Subtraction(Clock c1, Clock c2),Constant k) ->
        if c1 >= c2 then (
          let b = under_approximate c1 c2 (k, DBM_WEAK) in
          add_lit ~negate:true (c1,c2,b)
        ) else (
          add_lit (c2, c1, over_approximate c2 c1 (-k,DBM_STRICT))
        )

      | GuardEqual(Subtraction(Clock c1, Clock c2),Constant k) ->
        approximate (GuardLeq(Subtraction(Clock c1,Clock c2), Constant k));
        approximate (GuardGeq(Subtraction(Clock c1,Clock c2), Constant k));
      | _ -> failwith "Unexpected guard form"
    in
    List.iter (fun ag -> approximate ag) g;
    And (Queue.fold (fun acc x -> x :: acc) [] cube)

    let rec smv_string_of_exp bta e =
      let open TA in
      match e with
      | Constant c -> sprintf "%d" c
      | Variable(id) -> VarContext.var_of_index bta.TA.vars id
      | Clock(id) ->  VarContext.var_of_index bta.TA.clocks id
      | Product(e1,e2) ->
        sprintf "%s * %s" (smv_string_of_exp bta e1)
          (smv_string_of_exp bta e2)
      | Sum(e1,e2) ->
        sprintf "(%s + %s)" (smv_string_of_exp bta e1)
          (smv_string_of_exp bta e2)
      | Division(e1,e2) ->
        sprintf "%s / %s" (smv_string_of_exp bta e1)
          (smv_string_of_exp bta e2)
      | Subtraction(e1,e2) ->
        sprintf "(%s - %s)" (smv_string_of_exp bta e1)
          (smv_string_of_exp bta e2)
      | BoolEq(e1,e2) ->
        sprintf "(%s = %s)" (smv_string_of_exp bta e1)
          (smv_string_of_exp bta e2)
      | BoolNeq(e1,e2) ->
        sprintf "(%s != %s)" (smv_string_of_exp bta e1)
          (smv_string_of_exp bta e2)
      | BoolAnd(e1,e2) ->
        sprintf "toint(bool(%s) & bool(%s))" (smv_string_of_exp bta e1)
          (smv_string_of_exp bta e2)
      | BoolNot(e1) ->
        sprintf "toint(!bool(%s))" (smv_string_of_exp bta e1)


  let rec smv_string_of_atomic_guard bta =
    let open TA in
    let string_of_exp = smv_string_of_exp bta in
    function
    |  GuardLeq(v,exp) ->
      sprintf "%s <= %s" (string_of_exp v)(string_of_exp exp)
    | GuardLess(v,exp) ->
      sprintf "%s < %s" (string_of_exp v)(string_of_exp exp)
    | GuardGeq(v,exp)->
      sprintf "%s >= %s" (string_of_exp v)(string_of_exp exp)
    | GuardGreater(v,exp)->
      sprintf "%s > %s" (string_of_exp v) (string_of_exp exp)
    | GuardEqual(v,exp)->
      sprintf "%s = %s" (string_of_exp v) (string_of_exp exp)
    | GuardNeq(v,exp)->
      sprintf "%s != %s" (string_of_exp v) (string_of_exp exp)

  let rec smv_string_of_syntactic_guard bta g =
    let rec aux = function
    | [] -> "TRUE"
    | [x] -> smv_string_of_atomic_guard bta x
    | x :: y :: l ->
      sprintf "%s & %s"
        (smv_string_of_atomic_guard bta x) 
        (aux (y::l))
    in
    let s = aux g in
    if s <> "" then sprintf "(%s)" s
    else s

  (* Conjunction of clock guard and the discrete guard as a SMV string *)
  let smv_string_of_full_guard bta abs ?next_clocks:(next_clocks=false) edge =
    sprintf "%s & %s"
      (string_of_bool_expr (encode_guard bta abs ~next:next_clocks edge.TA.edgeGuard))
      (smv_string_of_syntactic_guard bta edge.TA.edgeDiscGuard)

  (** Assign each edge in the model a unique ID from 0 to nb_edges.
      The indexer maps edge references to indices and conversely.
      Returns a triple of indexers: tau edges, sending edges, receiving edges
  *)
  let _encode_edges bta =
    let open TA in
    let triple_array_sum =
      Array.fold_left (fun (a,b,c) (s1,s2,s3) -> (a+s1, b+s2, c+s3)) (0,0,0)
    in
    (* Total number of edges in the model *)
    let nt, ns, nr =
      bta.procs
      |> Array.map
        (fun proc ->
           proc.procLocations
           |>
           Array.map (fun loc ->
               loc.locEdges
               |>
               List.map
                 (fun edge ->
                    match edge.edgeSync with
                      None -> (1,0,0)
                    |Some (SendChan(_)) -> (0,1,0)
                    |Some(RecvChan(_)) -> (0,0,1)
                 )
               |> List.enum
               |> Array.of_enum
               |>
               triple_array_sum
             )
           |> triple_array_sum
        )
      |> triple_array_sum
    in
    (* Register all edges, and assign them unique indices.
       A value of 0 means undefined edge
       so the max value must be #edges+1
    *)
    let tau_indexer = EdgeIndexer.create ~init:1 (nt+1) in
    let send_edgeIndexer = EdgeIndexer.create ~init:1 (ns+1) in
    let recv_edgeIndexer = EdgeIndexer.create ~init:1 (nr+1) in
    Array.iter
      (fun proc ->
         Array.iter
           (fun loc ->
              List.iter (fun edge ->
                  match edge.edgeSync with
                  | None ->
                    EdgeIndexer.add tau_indexer edge
                  | Some(Uta.SendChan(_)) ->
                    EdgeIndexer.add send_edgeIndexer edge
                  | Some(Uta.RecvChan(_)) ->
                    EdgeIndexer.add recv_edgeIndexer edge

                ) loc.locEdges
           )
           proc.procLocations
      ) bta.procs;
    (tau_indexer, send_edgeIndexer, recv_edgeIndexer)

  (** Returns array of (cset, cexp) where for index i:
     cset is the set of committed location identifiers for process i
     cexp is the Boolean expression encoding the disjunction of these as a string
  *)
  let _encode_committed bta  =
    let open TA in
    Array.mapi
      (fun i proc ->
         let comm_list =
           (0--((Array.length proc.procLocations)-1))
           |> Enum.filter (fun i -> proc.procLocations.(i).locCommitted)
           |> List.of_enum
         in
         let expr = (Or (List.map (fun l -> Value(sprintf "loc%d = %d" i l)) comm_list))
         in
         ((IntSet.of_list comm_list),
          string_of_bool_expr expr
         )
      ) bta.procs

  (** Returns a disjunction of urgent locations the entire NTA as a string *)
  let _encode_urgent bta  =
    let open TA in
    Array.mapi
      (fun i proc ->
         let comm_list =
           (0--((Array.length proc.procLocations)-1))
           |> Enum.filter (fun i -> proc.procLocations.(i).locUrgent)
           |> List.of_enum
         in
         (Or (List.map (fun l -> Value(sprintf "loc%d = %d" i l)) comm_list))
      ) bta.procs
    |> fun ar -> Or (Array.to_list  ar)
    |> string_of_bool_expr


  (** Returns a string representing the invariant everywhere. 
      /\_{proc p} /\_{loc l} ((loc_p = l) -> invar_l)
  *)
  let _encode_invariant ?next_clocks:(next_clocks=false) bta abs =
    let nb_procs = Array.length bta.TA.procs in
    let buf = Buffer.create 1024 in
    Buffer.add_string buf "TRUE";
    for i = 0 to nb_procs - 1 do
      Array.iteri
        (fun j loc ->
           Buffer.add_string buf (sprintf " & (loc%d = %d -> %s)"
                             i j
                             (string_of_bool_expr (encode_guard ~next:next_clocks bta abs loc.TA.locInvar)))
        ) bta.TA.procs.(i).TA.procLocations
    done;
    Buffer.contents buf


  (** Returns a string of a formula checking whether the current location is commited *)
  let _encode_global_committed bta comm =
    let comm = Array.map fst comm in
    Array.mapi
      (fun i iset ->
         IntSet.elements iset
         |>
         List.map (fun ind -> sprintf "loc%d = %d" i ind)
      ) comm
    |> Array.to_list
    |> List.flatten
    (* Construct the bool_expr *)
    |> (fun x -> (Or (List.map (fun y -> Value y) x)))
    |> string_of_bool_expr

  (** Returns a string encoding the 2-reduction formula associated to given abstraction preds *)
  let _encode_reduce bta preds =
    let nbclocks = (TA.nb_clocks bta)-1 in
    let conj = Queue.create () in
    for x = 0 to nbclocks do
      for y = 0 to nbclocks do
        if not(x=0 && y=0) then(
          let add_conjunct k =
            let disj = Queue.create () in
            (*
            printf "Conjunct (%d,%d) <= %s\n" x y (Udbml.Basic_types.string_of_raw k);
               *)
            (* first term *)
            List.iter (fun l ->
                if l <= k then (
                  Queue.add (literal_of_constraint (x,y,l)) disj
                )
              ) preds.(x).(y);
            (*
            Queue.iter (fun expr -> printf "\t disj: %s\n" (string_of_bool_expr expr)) disj;
            printf "Now the second disj.\n";
               *)
            (* second term *)
            for z = 0 to nbclocks do
              List.iter
                (fun l ->
                   List.iter
                     (fun l' ->
                        if (Dbm.Alg.add l l' <= k) then(
                          (*
                          printf "\tdisj: %s\n"
                            (string_of_bool_expr(And(
                              [literal_of_constraint (x,z,l);
                               literal_of_constraint (z,y,l')
                              ]
                            )));
                             *)
                          Queue.add
                            (And(
                              [literal_of_constraint (x,z,l);
                               literal_of_constraint (z,y,l')
                              ]
                            )) disj
                        )
                     ) preds.(z).(y)
                ) preds.(x).(z)
            done;
            (* Make the implication *)
            let disj = Queue.fold (fun acc x -> x :: acc) [] disj in
            Queue.add (Or([Not(Or(disj)); literal_of_constraint (x,y,k)])) conj
          in
          List.iter add_conjunct preds.(x).(y)
        )
      done;
    done;
    (* Make the big conjunction *)
    let conj = Queue.fold (fun acc x -> x :: acc) [] conj in
    (string_of_bool_expr (And conj))

  (** Partition edge indices into internal, and synchronizing ones *)
  let _partition_edges bta (tau_indexer,send_indexer,recv_indexer) =
    let open TA in
    let sync2edges = Hashtbl.create 100 in
    let edge2sync = EdgeMap.create 10000 in

    [tau_indexer; send_indexer; recv_indexer]
    |>
    List.iter (fun indexer ->
        EdgeIndexer.get_keys indexer
        |>
        List.iter (fun edge ->
          Hashtbl.add sync2edges edge.edgeSync edge;
          EdgeMap.add edge2sync edge edge.edgeSync
          )
      );
    (sync2edges, edge2sync)


  (* Make a string describing the over-approx of x-y=0, i.e. the initial state *)
  let _init_preds preds =
    let q = Queue.create () in
    let nb_clocks = (Array.length preds) - 1 in
    for x = 0 to nb_clocks do
      for y = 0 to x -1 do
        List.iter
          (fun k ->
             if y = 0 then (
               Queue.add (sprintf "%s" (predicate_of_constraint (x,y,k))) q
             ) else (
               if k < (0,DBM_WEAK) then (
                 Queue.add (sprintf "!%s" (predicate_of_constraint (x,y,k))) q
               ) else (
                 Queue.add (sprintf "%s" (predicate_of_constraint (x,y,k))) q
               )
             )
          ) preds.(x).(y)
      done
    done;
    let l = (Queue.fold (fun acc x -> x :: acc) [] q) in
    (* Just append & at the beginning unless the list is empty *)
    (if l <> [] then "&" else "") ^ (String.join " & " l)

  let rec smv_string_of_query =
    let open TA in
    function
    | TA.EmptyQuery -> "TRUE"
    | AndQuery(q1,q2) ->
      sprintf "(%s & %s)" (smv_string_of_query q1) (smv_string_of_query q2)
    | OrQuery(q1,q2) ->
      sprintf "(%s | %s)" (smv_string_of_query q1) (smv_string_of_query q2)
    | AtomicQuery(i,j) ->
      sprintf "(loc%d = %d)" i j.locId
    | NotQuery(q1) -> sprintf "!(%s)" (smv_string_of_query q1)

  (** Main data type for the smv encoding *)
  type smv_encoding_t =
    { smv_tauIndexer : EdgeIndexer.t;
      smv_sendIndexer : EdgeIndexer.t;
      smv_recvIndexer : EdgeIndexer.t;
      smv_tau_edges : TA.edge list;
      smv_sync_edges : (TA.edge * TA.edge) list;
      smv_tau_clock_resets : (int, clock_t array) Hashtbl.t;
      smv_sync_clock_resets : (int * int, clock_t array) Hashtbl.t
    }

  (** Writes the SMV model for bta given clock pred abstraction abs into file /tmp/a.smv.
      Returns the smv_encoding_t structure which is used to decode the counterexamples
  *)
  let dump_model bta (abs : CPAbs.t) =
    let out = open_out "/tmp/a.smv" in
    let open TA in
    let nb_procs = Array.length bta.procs in
    let nb_locs = Array.map (fun p -> Array.length p.procLocations) bta.procs in
    let nb_clocks = (TA.nb_clocks bta) -1 in
    let preds = get_predicates abs in
    let indexers = _encode_edges bta in
    let tauIndexer, sendIndexer, recvIndexer = indexers in
    let nb_tau_edges = EdgeIndexer.size tauIndexer in
    let nb_send_edges = EdgeIndexer.size sendIndexer in
    let nb_recv_edges = EdgeIndexer.size recvIndexer in
    let (sync2edges, _) = _partition_edges bta indexers in
    (*
    let tau_edges = Hashtbl.find_all sync2edges None in
    *)
    let tau_edges = EdgeIndexer.get_keys tauIndexer in
    let sync_edges =
      Hashtbl.keys sync2edges
      |>
      Enum.map
        (function
          | None -> []
          | Some(SendChan(lab)) ->
            let el1 = Hashtbl.find_all sync2edges (Some(SendChan lab)) in
            let el2 = Hashtbl.find_all sync2edges (Some(RecvChan lab)) in
            List.map
              (fun e1 ->
                 List.map
                   (fun e2 ->
                      (e1,e2)
                   ) el2
              ) el1
            |> List.flatten
          | _ -> []
        )
      |> List.of_enum
      (* unless we want to label sync labels in the model: *)
      |> List.flatten
      (* Eliminate matching sync edges of a same process: *)
      |> List.filter (fun (e1,e2) -> e1.TA.edgeProc <> e2.TA.edgeProc)
    in

    (** Map from edges to an array of reset clocks (which induces a reset order) *)
    let tau_clock_resets = Hashtbl.create 1024 in
    (** The same map from edge indexes *)
    let itau_clock_resets = Hashtbl.create 1024 in
    List.iter (fun e ->
        Common.ClockSet.elements e.edgeReset
        |> Array.of_list
        |> (fun r ->
            Hashtbl.add tau_clock_resets e r; (*(EdgeIndexer.get_index edgeIndexer e);*)
            Hashtbl.add itau_clock_resets (EdgeIndexer.get_index tauIndexer e) r;
          )
      ) tau_edges;
    let sync_clock_resets = Hashtbl.create 1024 in
    let isync_clock_resets = Hashtbl.create 1024 in
    List.iter (fun(e1,e2) ->
        let i1,i2 = (EdgeIndexer.get_index sendIndexer e1), (EdgeIndexer.get_index recvIndexer e2)
        in
        let rset = ClockSet.union e1.edgeReset e2.edgeReset in
        let content = (Array.of_list (ClockSet.elements rset)) in
        Hashtbl.add sync_clock_resets (e1,e2) content;
        Hashtbl.add isync_clock_resets (i1,i2) content
      ) sync_edges;
    let max_clock_resets =
      max
      (* from tau trans *)
      (Hashtbl.fold (fun _ r acc ->
           (max acc (Array.length r)) ) tau_clock_resets 0
      )
        (* from sync trans *)
      (Hashtbl.fold (fun _ r acc ->
           (max acc (Array.length r)) ) sync_clock_resets 0
      )
    in
    let committedAr = _encode_committed bta in
    let invariant = _encode_invariant bta abs in
    let invariant_next = _encode_invariant ~next_clocks:true bta abs in
    let glob_committed = _encode_global_committed bta committedAr in
    let reduce = _encode_reduce bta preds in
    fprintf out "MODULE main\nVAR\n\tmode : {up, reset";
    for i = 1 to max_clock_resets - 1 do
      fprintf out ", reset%d" i;
    done;
    fprintf out "};\n";
    fprintf out "-- Location variables\n";
    Array.iteri (fun i nblocs ->
        fprintf out "\tloc%d : 0..%d;\n" i (nblocs-1);
        for j = 0 to nblocs -1 do
          fprintf out "-- Proc(%d)Loc(%d) = %s\n" i j bta.procs.(i).procLocations.(j).locName;
          (*Log.info (sprintf "Proc(%d)Loc(%d) = %s\n" i j bta.procs.(i).procLocations.(j).locName)*)
        done;
      ) nb_locs;
    for i = 1 to (EdgeIndexer.size tauIndexer)-1 do
      (*Log.info (sprintf "Edge(%d) = %s\n" i (string_of_edge_id bta edgeIndexer i));*)
      fprintf out "-- Tau Edge(%d) = %s\n" i (string_of_edge_id bta tauIndexer i);
    done;
    for i = 1 to (EdgeIndexer.size sendIndexer)-1 do
      (*Log.info (sprintf "Edge(%d) = %s\n" i (string_of_edge_id bta edgeIndexer i));*)
      fprintf out "-- Send Edge(%d) = %s\n" i (string_of_edge_id bta sendIndexer i);
    done;
    for i = 1 to (EdgeIndexer.size recvIndexer)-1 do
      (*Log.info (sprintf "Edge(%d) = %s\n" i (string_of_edge_id bta edgeIndexer i));*)
      fprintf out "-- Recv Edge(%d) = %s\n" i (string_of_edge_id bta recvIndexer i);
    done;
    fprintf out "-- Clock mapping\n";
    VarContext.iter (fun name i ->
        fprintf out "-- Clock %d: %s\n" i name
      ) bta.clocks;
    fprintf out "-- Clock predicates\n";
    for i = 0 to nb_clocks do
      for j = 0 to i-1 do
       List.iter (fun c ->
            fprintf out "\t%s : boolean;\n" (predicate_of_constraint (i,j,c))
          ) preds.(i).(j)
      done
    done;
    fprintf out "-- Discrete variables\n";
    VarContext.iter
      (fun var vi ->
         if var <> "preference" then
           try
             match VarContext.range_of_index bta.vars vi with
               Some (l,r) -> fprintf out "\t%s : %d..%d;\n" var l r
             | None -> failwith (sprintf "No range found for discrete variable %s" var)
           with Not_found -> failwith (sprintf "No range found for var %s of ind %d" var vi)
      ) bta.vars;
    fprintf out "-- Choice of edges for tau (e1) or sync transitions (e1,e2)\n";
    fprintf out "\te : 0..%d;\n" (nb_tau_edges-1);
    fprintf out "\te1 : 0..%d;\n" (nb_send_edges-1);
    fprintf out "\te2 : 0..%d;\n" (nb_recv_edges-1);
    fprintf out "ASSIGN\n";
    (* location init & updates *)
    for i = 0 to nb_procs - 1 do
      if nb_locs.(i) > 1 then (
        fprintf out "\tinit(loc%d) := %d;\n" i
          bta.procs.(i).procInitLoc;
        fprintf out "\tnext(loc%d) := \n" i;
        fprintf out "\tcase\n";
        List.iter
          (fun e ->
             if e.edgeProc = i then (
               fprintf out "\t\tmode = reset & e = %d : %d;\n"
                 (EdgeIndexer.get_index tauIndexer e)
                 e.edgeTarget;
             );
          ) tau_edges;
        List.iter
          (fun (e1,e2) ->
             if (e1.edgeProc = i || e2.edgeProc = i) && e1.edgeProc <> e2.edgeProc  then (
               fprintf out "\t\tmode = reset & e1 = %d & e2 = %d: %d;\n"
                 (EdgeIndexer.get_index sendIndexer e1)
                 (EdgeIndexer.get_index recvIndexer e2)
                 (if e1.edgeProc = i then
                    e1.edgeTarget
                  else e2.edgeTarget)
             )
          ) sync_edges;
        fprintf out "\t\tTRUE : loc%d;\n\tesac;\n" i;
      )
    done;
    fprintf out "-- Discrete variable updates\n";
    (* Discrete vars init & updates *)
    (* Map from updated variable index to list of edges that update that var.
       (Might contain duplicates)
    *)
    let (lvalue2tauedges, lvalue2syncedges) =
      let htau = Hashtbl.create 1024 in
      let hsync = Hashtbl.create 1024 in
      List.iter (fun e ->
          List.iter (fun (lv,_) ->
              Hashtbl.add htau lv e
            ) e.edgeDiscUpdate
        ) tau_edges;
      List.iter (fun (e1,e2) ->
          List.iter (fun (lv,_) ->
              Hashtbl.add hsync lv (e1,e2)
            ) e1.edgeDiscUpdate;
          List.iter (fun (lv,_) ->
              Hashtbl.add hsync lv (e1,e2)
            ) e2.edgeDiscUpdate
        ) sync_edges;
      (htau,hsync)
    in
    VarContext.iter
      (fun v vi ->
         if v <> "preference" then (
             let t_edges = Hashtbl.find_all lvalue2tauedges (vi) in
             let s_edges = Hashtbl.find_all lvalue2syncedges (vi) in
             let Some (l,r) = VarContext.range_of_index bta.vars vi in
             if (List.length t_edges > 0 || List.length s_edges > 0) then(
               fprintf out "\tinit(%s) := %d;\n"
                 v
                 bta.init.stateVars.(vi);
               fprintf out "\tnext(%s) := case\n" v;
               t_edges
               |>
               List.iter (fun e ->
                   let upexpr = List.assoc (vi) e.edgeDiscUpdate in
                   let upstr = smv_string_of_exp bta upexpr in
                   fprintf out "\t\tmode = reset & e = %d & %d <= toint(%s) & toint(%s) <= %d : toint(%s);\n"
                     (EdgeIndexer.get_index tauIndexer e) l upstr upstr r upstr
                 );
               s_edges
               |> List.unique
               |>
               List.iter (fun (e1,e2) ->
                   let upexpr =
                     let (re,se) =
                       match e2.edgeSync with Some(RecvChan _) -> (e2,e1)
                                            | _ -> (e1,e2)
                     in
                     try List.assoc (vi) re.edgeDiscUpdate with
                     | Not_found -> List.assoc (vi) se.edgeDiscUpdate
                   in
                   (** If both edges update the variable, the receiving edge has priority *)
                   let upstr = smv_string_of_exp  bta upexpr in
                   fprintf out "\t\tmode = reset & e1 = %d & e2 = %d & %d <= toint(%s) & toint(%s) <= %d : toint(%s);\n"
                     (EdgeIndexer.get_index sendIndexer e1)
                     (EdgeIndexer.get_index recvIndexer e2)
                     l upstr
                     upstr r
                     upstr
                 );
               fprintf out "\t\tTRUE : %s;\n\tesac;\n" v;
             ) else (
               fprintf out "\tinit(%s) := %d;\n"
                 v
                 bta.init.stateVars.(vi);
               fprintf out "\tnext(%s) := %s;\n"
                 v v;
             )
         )
      ) bta.vars;
    fprintf out "-- Clock predicate updates\n";
    (* clock predicate updates (see below for init)*)
    let clock2tau_updates = Array.init (nb_clocks+1) (fun i -> Queue.create ()) in
    List.iter (fun e ->
        ClockSet.iter (fun x ->
              Queue.add e clock2tau_updates.(x)
          ) e.edgeReset
      ) tau_edges;
    let clock2sync_updates = Array.init (nb_clocks+1) (fun _ -> Queue.create()) in
    List.iter (fun (e1,e2) ->
          let (re,se) =
            match e2.edgeSync with Some(RecvChan _) -> (e2,e1)
                                 | _ -> (e1,e2)
          in
          ClockSet.iter (fun x->
              assert(x < (Array.length clock2tau_updates));
                Queue.add (e1,e2) clock2sync_updates.(x)
            ) re.edgeReset;
          ClockSet.iter (fun x->
                (* Add this update only if the receiving edge does not update x *)
              (try ignore(ClockSet.mem x re.edgeReset)
                 with Not_found ->
                   assert(x < (Array.length clock2tau_updates));
                   Queue.add (e1,e2) clock2sync_updates.(x)
                )
            ) se.edgeReset
      ) sync_edges;
    let reset_mode_of_tau_edge e =
      let m =  Array.length (Hashtbl.find tau_clock_resets e)
      in
      if m <= 1 then "reset"
      else sprintf "reset%d" (m-1)
    in
    let reset_mode_of_sync_edge (e1,e2) =
      let m =  Array.length (Hashtbl.find sync_clock_resets (e1,e2))
      in
      if m <= 1 then "reset"
      else sprintf "reset%d" (m-1)
    in
    fprintf out "TRANS\n";
    fprintf out "\tTRUE -- choice of edges and update of mode \n";
    for i = max_clock_resets - 1 downto 1 do
      let tgt = if i = 1 then "reset" else (sprintf "reset%d" (i-1)) in
      fprintf out "\t& (mode = reset%d -> next(mode) = %s)\n" i tgt
    done;
    fprintf out "\t& (mode = reset -> next(mode) = up)\n";
    fprintf out "-- Choice of the next edges (satisfied by the next-state clock predicates and current-state disc. state)\n";
    fprintf out "\t& (mode != up -> (next(e1) = e1 & next(e2) = e2 & next(e) = e))\n\t& (mode = up ->\n";
    fprintf out "\t\t(next(e) != 0 | (next(e1) != 0 & next(e2) != 0))\n";
    List.iter
      (fun e ->
         let ie = EdgeIndexer.get_index tauIndexer e in
         let g = (smv_string_of_full_guard bta abs ~next_clocks:true e) in
(*
         Log.debug (sprintf "Printing edge %d of guard: %s\n" ie g);
         Log.debug (sprintf "Syntactically: %s\n" (BTA.string_of_guard bta e.BTA.edgeGuard));
  *)
         let cond =
           sprintf "(loc%d = %d & (!committed | comm_%d) & %s & _invariant_next & next(mode) = %s)"
             e.edgeProc
             e.edgeSource
             e.edgeProc
             g
             (reset_mode_of_tau_edge e)
         in
         fprintf out "\t\t& (next(e) = %d -> next(e1) = 0 & next(e2) = 0 & %s)\n"
           ie
           cond
      ) tau_edges;
    List.iter
      (fun (e1,e2) ->
         if e1.edgeProc <> e2.edgeProc then (
           let ie1 = EdgeIndexer.get_index sendIndexer e1 in
           let ie2 = EdgeIndexer.get_index recvIndexer e2 in
           let g1 = (smv_string_of_full_guard bta abs ~next_clocks:true e1) in
           let g2 = (smv_string_of_full_guard bta abs ~next_clocks:true e2) in
(*
         Log.debug (sprintf "Printing sync edge (%d,%d):\n" ie1 ie2);
         Log.debug (sprintf "Syntactically: %s; and %s\n" 
                      (BTA.string_of_guard bta e1.BTA.edgeGuard)
                      (BTA.string_of_guard bta e2.BTA.edgeGuard));
*)
           fprintf out "\t\t& (((next(e1) = %d & next(e2) = %d)) -> next(e) = 0 & ((!committed | comm_%d | comm_%d) & loc%d = %d & loc%d = %d & %s & %s & _invariant_next & next(mode) = %s))\n"
             ie1 ie2
             e1.edgeProc e2.edgeProc
             e1.edgeProc e1.edgeSource
             e2.edgeProc e2.edgeSource
             g1 g2
             (reset_mode_of_sync_edge (e1,e2))
         )
      ) sync_edges;
    fprintf out "\t)\n";
    fprintf out "\t \n";
    fprintf out "-- Transition relation for clock predicates: resets and time up\n";
    let dump_reset_z z =
      let next_of_lit (x,y,k) =
        if x > y then
          sprintf "next(%s)"
            (predicate_of_constraint (x,y,k))
        else
          sprintf "!next(%s)"
            (predicate_of_constraint (y,x,Dbm.Alg.invert_raw k))
      in
      fprintf out "\t\t\tTRUE\n\t\t\t";
      (* Conjunct 1 *)
      List.iter
        (fun k ->
           if (0,DBM_WEAK) <= k then (
             fprintf out "& next(%s) " (predicate_of_constraint (z,0,k))
           )
        ) preds.(z).(0);
      fprintf out "\n";
      for x = 1 to nb_clocks do
        if x <> z then (
          (* Conjunct 2 *)
          preds.(x).(z)
          |>
          List.iter (fun k ->
              let lhs =
                ((List.filter (fun l -> l <= k) preds.(x).(0))
                 |> List.map (fun l -> Value (predicate_of_constraint (x,0,l)))
                 |> (fun l -> Or l)
                 |> string_of_bool_expr
                )
              in
              fprintf out "\t\t\t& ((%s) -> %s)\n"
                lhs (next_of_lit (x,z,k))
            );
          (* Conjunct 3 *)
          let y = x in
          preds.(z).(y)
          |>
          List.iter
            (fun k ->
               let lhs =
                 ((List.filter (fun l -> l <= k) preds.(0).(y))
                  |> List.map (fun l -> (literal_of_constraint (0,y,l)))
                  |> (fun l -> Or l)
                  |> string_of_bool_expr
                 )
               in
               fprintf out "\t\t\t& ((%s) -> %s)\n"
                 lhs (next_of_lit (z,y,k));
               if k >= (0,DBM_WEAK) then (
                 fprintf out "\t\t\t& %s\n"
                   (next_of_lit (z,y,k))
               );
            )
        );
      done;
      (* Conjunct 4 *)
      for x = 0 to nb_clocks do
        for y = 0 to nb_clocks do
          if (x > y && x <> z && y <> z) then (
            preds.(x).(y)
            |> List.iter (fun k ->
                fprintf out "\t\t\t & (%s <-> next(%s))\n"
                  (predicate_of_constraint (x,y,k))
                  (predicate_of_constraint (x,y,k))
              )
          )
        done
      done
    in
    let up_cases = Queue.create () in
    List.iter
      (fun e ->
         let ie = EdgeIndexer.get_index tauIndexer e in
         let resets = Hashtbl.find tau_clock_resets e in
         let nr = Array.length resets in
         Array.iteri
           (fun i z ->
              let reset = if i = nr - 1 then "reset"
                else (sprintf "reset%d" (nr - 1 - i))
              in
              let case = sprintf "(mode = %s & e = %d)"
                  reset ie
              in
              Queue.add case up_cases ;
              fprintf out "\t& (%s ->\n" case;
              dump_reset_z z;
              fprintf out "\t)\n";
           ) resets;
      ) tau_edges;
    List.iter
      (fun (e1,e2) ->
         let ie1 = EdgeIndexer.get_index sendIndexer e1 in
         let ie2 = EdgeIndexer.get_index recvIndexer e2 in
         let resets = Hashtbl.find sync_clock_resets (e1,e2) in
         let nr = Array.length resets in
         Array.iteri
           (fun i z ->
              let reset = if i = nr - 1 then "reset"
                else (sprintf "reset%d" (nr - 1 - i))
              in
              let case = sprintf "(mode = %s & e1 = %d & e2 = %d)"
                  reset ie1 ie2
              in
              Queue.add case up_cases ;
              fprintf out "\t\t& (%s ->\n" case;
              dump_reset_z z;
              fprintf out "\t\t)\n";
           ) resets;
      ) sync_edges;
    (* Time up transitions *)
    fprintf out "-- Time up transitions\n";
    for x = 1 to nb_clocks do
      preds.(x).(0)
      |>
      List.iter
        (fun k ->
         let v = predicate_of_constraint (x,0,k) in
         fprintf out "\t\t& (mode = up & time_can_pass -> (next(%s) -> %s))\n" v v
        )
    done;
    (* Diagonals do not change during up *)
    for x = 1 to nb_clocks do
      for y = 1 to x-1 do
        preds.(x).(y)
        |>
        List.iter
          (fun k ->
             let v = predicate_of_constraint (x,y,k) in
             fprintf out "\t\t& (mode = up & time_can_pass -> (next(%s) <-> %s))\n" v v
          )
      done
    done;
    Queue.add "mode = up & time_can_pass" up_cases;
    fprintf out "-- Clock predicates must be unchanged in all remaining caes\n";
    (* Add that these predicats are unchanged in the complement of the above cases *)
    let complement =
      (Queue.fold (fun acc x -> x::acc) [] up_cases)
      |> String.join " | "
    in
    fprintf out "\t\t& (!(%s) ->\n\t\t\tTRUE " complement;
    for x = 1 to nb_clocks do
      for y = 0 to x-1 do
        preds.(x).(y)
        |>
        List.iter
          (fun k ->
             let v = predicate_of_constraint (x,y,k) in
             fprintf out "\t\t\t& (next(%s) <-> %s)\n" v v
          )
      done
    done;
    fprintf out "\t\t)\n";
    fprintf out ";\n";
    fprintf out "INIT TRUE\n-- Initial abstract zone\n\t%s\n" (_init_preds preds);
    fprintf out "-- Start with up mode so that edges are selected\n";
    fprintf out "\t& mode = up;\n";
    fprintf out "INVAR\n-- Reduce constraint\n\t%s\n" reduce;
    (* Add invariants *)
    fprintf out "-- Location invariants\n";
    fprintf out "\t\t&(mode = up -> (%s))\n"
      invariant;
    fprintf out "\t;\n";
    fprintf out "DEFINE\n";
    fprintf out "\tcommitted := %s;\n" glob_committed;
    for i = 0 to nb_procs -1 do
      fprintf out "\tcomm_%d := %s;\n" i (snd committedAr.(i))
    done;
    fprintf out "urgent := %s;\n" (_encode_urgent bta);
    fprintf out "time_can_pass := !committed & !urgent;\n";
    fprintf out "_invariant := %s;\n" invariant;
    fprintf out "_invariant_next := %s;\n" invariant_next;
    fprintf out "INVARSPEC\n";
    fprintf out "!%s\n" (smv_string_of_query bta.TA.query);
    close_out out;
    { smv_tauIndexer = tauIndexer;
      smv_sendIndexer = sendIndexer;
      smv_recvIndexer = recvIndexer;
      smv_tau_edges = tau_edges;
      smv_sync_edges = sync_edges;
      smv_tau_clock_resets = itau_clock_resets;
      smv_sync_clock_resets = isync_clock_resets
    }

  (** Parse NuSMV cex trace to make symbolic path.
      The returned value is a pair of init state constraints,
      and of the symbolic_path that starts at that initial state.
  *)
  let get_symbolic_path bta smv_enc cex_steps =
    (** Get the list of clock constraints defined by
        a cex state described by its list of assignment strings *)
    let get_zone asgns =
      (* Parse clock pred assignment of the form
         p_x_y_*_k and return the corresponding clock_constraint *)
      let constraint_of_asgn pr =
        (*
        let re = regexp "p_\\([0-9]*\\)_\\([0-9]*\\)_\\(s\\|w\\)_\\([0-9]*\\) = \\(TRUE\\|FALSE\\)" in
           *)
        let re = regexp "p_\\([0-9]*\\)_\\([0-9]*\\)_\\(s\\|w\\)_\\(m\\)?\\([0-9]*\\) = \\(TRUE\\|FALSE\\)" in
        if not (string_match re pr 0) then None
        else
          let x = matched_group 1 pr |> int_of_string in
          let y = matched_group 2 pr |> int_of_string in
          let ineq = match matched_group 3 pr with
              "w" -> DBM_WEAK
            | _ -> DBM_STRICT
          in
          let sign = (try ignore(matched_group 4 pr); -1 with Not_found -> 1) in
          let b = matched_group 5 pr |> int_of_string |> ( *) sign in
          let inv = match matched_group 6 pr with "TRUE" -> true | _ -> false in
          if inv then
            Some (x,y,(b,ineq))
          else Some (Guard.Alg.negate_constraint (x,y,(b,ineq)))
      in
      List.map constraint_of_asgn asgns
      |> List.fold_left (fun acc elt -> match elt with None -> acc | Some x -> x::acc) []
    in
    let get_location_ar state =
      let locs = Array.copy (bta.TA.init.TA.stateLocs) in
      (*
      printf "[DEB] get_location_ar\n";
          List.iter (printf "<%s>\n") state;
         *)
      List.iter (fun asgn ->
          let re = regexp "loc\\([0-9]*\\) = \\([0-9]*\\)" in
          if (string_match re asgn 0) then (
            let i = matched_group 1 asgn |> int_of_string in
            let j = matched_group 2 asgn |> int_of_string in
            locs.(i) <- bta.TA.procs.(i).TA.procLocations.(j)
          )
        ) state;
      locs
    in
    let get_mode state =
      if List.mem "mode = up" state then(
        let locs = get_location_ar state in
        Sym_Up (locs,(List.mem "time_can_pass = TRUE" state))
      )
      else (
        let locs = get_location_ar state in
        let reset_re = regexp  "mode = reset\\([0-9]*\\)" in
        let sync_edge_re = regexp  "e\\([1-2]\\) = \\([0-9]*\\)" in
        let tau_edge_re = regexp  "e = \\([0-9]*\\)" in
        let e1 = ref None in
        let e2 = ref None in
        let e = ref None in
        let ri = ref None in
        List.iter
          (fun line ->
             if Str.string_match reset_re line 0 then
               (
                 let ri_s = Str.matched_group 1 line in
                 ri := Some(if ri_s = "" then 0 else int_of_string ri_s)
               ) else if Str.string_match sync_edge_re line 0 then (
                 let i = Str.matched_group 1 line |> int_of_string in
                 let e = Str.matched_group 2 line |> int_of_string in
                 if i = 1 then (
                   e1 := Some(e);
                   if e = 0 then e1 := None
                 ) else (
                   e2 := Some(e);
                   if e = 0 then e2 := None
                 )
                 (* printf "[DEB] e_%d = %d\n" i e;*)
               ) else if Str.string_match tau_edge_re line 0 then (
                 let ie = Str.matched_group 1 line |> int_of_string in
                 e := Some ie;
                 if ie = 0 then e := None
               )
          ) state;
        (
          match (!e1,!e2,!e,!ri) with
          |Some(e1), Some(e2), None, Some(ri) ->
            let edge1 = EdgeIndexer.get_key smv_enc.smv_sendIndexer e1 in
            let edge2 = EdgeIndexer.get_key smv_enc.smv_recvIndexer e2 in
            let is_tau_edge = List.mem edge1 smv_enc.smv_tau_edges in
            assert(not is_tau_edge);
            let resets =
                assert(List.mem (edge1,edge2) smv_enc.smv_sync_edges);
                Hashtbl.find smv_enc.smv_sync_clock_resets (e1,e2)
            in
            let nr = Array.length resets in
            let x =
              if nr = 0 then (
                None
              ) else (
                let x = resets.(nr - ri - 1 ) in
                Some(x)
              )
            in
            (* Is this the last reset operations? *)
            let last_reset = (x = None) || (ri = 0) in
            (* printf "ri: %d, nr: %d, last: %b\n" ri nr last_reset; *)
            let edges = Pair(edge1,edge2) in
            (* The first step of the reset sequence: *)
            if nr = 0 || nr-ri-1 = 0 then (
                Sym_Edge (locs, edges, x, last_reset)
            ) else (
              (* Subsequent steps of the reset sequence: *)
              match x with
                None -> failwith "Bug"
              | Some(x) ->
                Sym_Reset (locs, edges, x, last_reset)
            )
          | None, None, Some(e), Some(ri) ->
            let edge = EdgeIndexer.get_key smv_enc.smv_tauIndexer e in
            let is_tau_edge = List.mem edge smv_enc.smv_tau_edges in
            assert(is_tau_edge);
            let resets =
                Hashtbl.find smv_enc.smv_tau_clock_resets e
            in
            let nr = Array.length resets in
            let x =
              if nr = 0 then (
                None
              ) else (
                let x = resets.(nr - ri - 1 ) in
                Some(x)
              )
            in
            (* Is this the last reset operations? *)
            let last_reset = (x = None) || (ri = 0) in
            (* printf "ri: %d, nr: %d, last: %b\n" ri nr last_reset; *)
            (* The first step of the reset sequence: *)
            if nr = 0 || nr-ri-1 = 0 then (
                Sym_Edge (locs, Single edge, x, last_reset)
            ) else (
              (* Subsequent steps of the reset sequence: *)
              match x with
                None -> failwith "Bug"
              | Some(x) ->
                Sym_Reset (locs, Single edge, x, last_reset)
            )
          | _ ->
            failwith "Could not parse e1, e2, and reset mode from nusmv trace:"
        )
      )
    in
    (* Call this with the (mode : symbolic_transition) that leads to the current asgns.
       In fact, if the cex is [mode1, Z1], [mode2, Z2], ...
       then the result of mode1 from Z1 is Z2, and the result of mode2 on Z2 is Z3 etc.
       This converts this sequence to [mode1, Z2], [mode2, Z3], etc. where Z1 is the init
       state so can be inferred, and the mode of the last state of the cex has no effect anyway.
    *)
    let rec decode_states mode = function
      | [] -> []
      | state :: l ->
        printf "State:\n";
        List.iter(printf "%s\n") state;
        let mode' = get_mode state in
        let zone = get_zone state in
        (mode, zone) :: (decode_states mode' l)
    in
(*
    printf "-----------------\n";
    List.iter(printf "%s\n") cex_steps;
    printf "-----------------\n";
   *)
    printf "#cex_steps: %d\n" (List.length cex_steps);
    (* Split each state description text into list of assignments *)
    let cex_states_asgns =
      List.map (split (regexp "[\n]+")) cex_steps
      |> List.map (List.map String.trim)
    in
    (* We separate the init state which is not reached by any operation *)
    let cex_init = List.hd cex_states_asgns in
    let init_loc = get_location_ar cex_init in
    let init_time_can_elapse = not(TA.is_urgent_or_committed bta bta.TA.init) in
    let mode_list = (decode_states (Sym_Up (init_loc,init_time_can_elapse)) (List.tl cex_states_asgns)) in
    (get_zone cex_init), mode_list



  (** Return type of the refine function. Since our abstract transition relations
      are approximate, we may not be able to refine to eliminate spurious cex
      in which case CannotRefine is returned.
      TODO Check whether this latter case can occur
  *)
  type refinement_result = Refined | Genuine | CannotRefine

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
  let refine bta abs smv_enc cex_string =
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
    let exception BreakRefined of int in
    let exception BreakGenuine in
    let exception BreakCannotRefine in
    printf "Raw counterexample:\n%s\n\n" cex_string;
    let delimiter_re = regexp "-> State: .* <-\n" in
    let states =
      Str.split delimiter_re cex_string
      |> List.map String.trim
      (* The first element is some garbage text before the cex *)
      |> List.tl
    in
    let cex_init, path = get_symbolic_path bta smv_enc states in
    printf "*** Starting feasability analysis with predicates:\n";
    printf "%s\n"(CPAbs.to_string bta abs);
    printf "Counter-example trace: \n";
    printf "%s\n" (string_of_symbolic_path bta path);
    let path = Array.of_list path in
    let nclocks = (TA.nb_clocks bta) - 1 in
    let npath= Array.length path in
    (* Zone successor through sym-action.
       Invariant is applied after the last reset
       and after time up
    *)
    let post (trans,_) dbm =
      let d = Dbm.copy dbm in
      (match trans with
           Sym_Up (locs, telapse) ->
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
             let invar = BTASemantics.dbm_invariant_of_state bta
                 {TA.stateLocs = locs; TA.stateVars = [||]}
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
           (match edges with
              Pair(e1,e2) ->
              let g1 = BTASemantics.dbm_guard_of_edge bta e1 in
              let g2 = BTASemantics.dbm_guard_of_edge bta e2 in
              Dbm.intersect d g1;
              Dbm.intersect d g2;
            | Single(e1) ->
              let g = BTASemantics.dbm_guard_of_edge bta e1 in
              Dbm.intersect d g;
           );
           (match reset with
              None -> ()
            | Some(x) -> Dbm.reset d (ClockSet.singleton x)
           );
           if flag_last then (
             let tr =  (match edges with
                   Pair(e1,e2) ->
                   (TA.SyncTrans ({TA.stateLocs = locs; TA.stateVars = [||]}, e1, e2))
                 | Single(e1) ->
                   (TA.InternalTrans ({TA.stateLocs = locs; TA.stateVars = [||]}, e1))
               )
             in
             let locs' = TA.next_location_vector bta locs tr in
             let invar = BTASemantics.dbm_invariant_of_state bta
                 {TA.stateLocs = locs'; TA.stateVars = [||]}
             in
             Dbm.intersect d invar;
           )
         | Sym_Reset (locs, edges, x, flag_last) ->
           Dbm.reset d (ClockSet.singleton x);
           if flag_last then (
             let invar = BTASemantics.dbm_invariant_of_state bta
                 {TA.stateLocs = locs; TA.stateVars = [||]}
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
           let invar = BTASemantics.dbm_invariant_of_state bta
               {TA.stateLocs = locs; TA.stateVars = [||]}
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
                let g1 = BTASemantics.dbm_guard_of_edge bta e1 in
                let g2 = BTASemantics.dbm_guard_of_edge bta e2 in
                let g = (Dbm.copy g1) in
                Dbm.intersect g g2;
                g
              | Single(e1) ->
                BTASemantics.dbm_guard_of_edge bta e1
             )
           in
           Dbm.intersect d g;
           let invar = BTASemantics.dbm_invariant_of_state bta
               {TA.stateLocs = locs; TA.stateVars = [||]}
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
      let invar = (BTASemantics.dbm_invariant_of_state bta bta.TA.init) in
      Dbm.intersect dbm invar;
      dbm
    in
    (* Abstract init state *)
    let ainit = BTASemantics.dbm_of_constraints bta cex_init in
    printf "Init:\nAbs:\n%s\n\nConc:\n%s\n\n"
      (Dbm.to_string ainit) (Dbm.to_string init);
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
    try
      for i = 1 to npath do
        let (trans,constr) = path.(i-1) in
        (try
           aposts.(i) <- (BTASemantics.dbm_of_constraints bta constr);
           (*
           printf "Aposts(%d)\n" i;
           printf "%s\n" (Dbm.to_string aposts.(i));
              *)
         with EmptyDBM ->
           (* The intersection of the non-reduced constraints is empty.
              Must add predicates so that abstract reduction can capture this *)
          CPAbs.refine_empty abs constr;
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
          printf "*********** STATE %d *************\n%s\n" i
            (string_of_symbolic_transition bta (fst(path.(i-1))));
          printf "\nAbs:\n%s\nConc:\n%s\n"
            (Dbm.to_string aposts.(i))
            (Dbm.to_string cposts.(i));
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
      Log.debug (sprintf "i0 = %d\n" i0); flush stdout;
      (*
      printf "First trans:\n";
      printf "%s\n" (string_of_symbolic_transition bta (fst path.(i0)));
      *)
      (* Regular refinement check: *)
      (try
         let preAi01 = (pre path.(i0) aposts.(i0+1)) in
         printf "PRE of ai0_1 is:\n%s\n" (Guard.to_string preAi01);
         let preAi01_ai0 = Dbm.copy preAi01 in
         Dbm.intersect preAi01_ai0 aposts.(i0);
         (* If this set is not empty, we can refine regularly *)
         CPAbs.refine_separate abs preAi01_ai0 cposts.(i0);
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
         CPAbs.refine_separate abs ai0 ai0_1
       | Sym_Reset(_,_,x,_),_ ->
         Log.debug "Irregular refinement: Reset\n";
         let ai0 = Dbm.copy aposts.(i0) in
         Dbm.free ai0 (ClockSet.singleton x);
         let ai0_1 = Dbm.copy aposts.(i0+1) in
         Dbm.free ai0_1 (ClockSet.singleton x);
         CPAbs.refine_separate abs ai0 ai0_1

       | Sym_Edge(locs,edges,reset_opt,flag_last),_ ->
         Log.debug "Irregular refinement: Edge Reset\n";
         let ai0 = Dbm.copy aposts.(i0) in
         let ai0_1 = Dbm.copy aposts.(i0+1) in
         let g =
           (match edges with
              Pair(e1,e2) ->
              let g1 = BTASemantics.dbm_guard_of_edge bta e1 in
              let g2 = BTASemantics.dbm_guard_of_edge bta e2 in
              let g = (Dbm.copy g1) in
              Dbm.intersect g g2;
              g
            | Single(e1) ->
              BTASemantics.dbm_guard_of_edge bta e1
           )
         in
         (match reset_opt with
            None ->
            failwith "Irregular refinement: Reset without reset"
          | Some x ->

            Dbm.free ai0 (ClockSet.singleton x);

            (try
               Dbm.constrain (Dbm.copy ai0_1) x 0 (0, DBM_WEAK);
             with EmptyDBM ->
               let d = Dbm.create (TA.nb_clocks bta) in
               Dbm.constrain d x 0 (0, DBM_WEAK);
               CPAbs.refine_separate abs ai0_1 d;
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
         CPAbs.refine_separate abs ai0 ai0_1
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

  let _testprint_committed bta =
    let open TA in
    let comm = _encode_committed bta in
    Array.iteri (fun i proc ->
        printf "Committed locations at process %d:\n\t" i;
        IntSet.iter (fun i-> printf "%s(%d) " proc.procLocations.(i).locName i) (fst comm.(i));
        printf "\n"
      ) bta.procs

end

exception Result_unknown
exception Result_true
exception Result_false
let verify bta ?max_iterations:(max_iterations=max_int) sym_init sym_alg sym_mc =
  let module TA = Uautomaton in
  let module CPAbs = ClockPredicateAbstraction in
  let module SMVInterface = SMVInterfaceMaker in
  let nusmv_cmd = (match sym_mc with
      Options.Sym_nusmv -> "NuSMV"
      | _ -> "nuXmv"
    )
  in
  let script = (match sym_alg with
      Options.Sym_bdd ->
      Log.infof "Using %s with BDD configuration\n" nusmv_cmd;
      bdd_config
      | Options.Sym_ic3 ->
        Log.infof "Using %s with IC3 configuration\n" nusmv_cmd;
        ic3_config
      | Options.Sym_script(file) ->
        Log.infof "Using %s with custom configuration\n" nusmv_cmd;
        (File.with_file_in file IO.read_all)
    )
  in
  let abs =
  (match  sym_init with
   Options.Sym_init_syntax -> CPAbs.init_syntax bta
    | Options.Sym_init_empty -> CPAbs.init_empty bta
    | Options.Sym_init_complete -> failwith "Not implemented"
  ) in
  Log.info "Printing current clock abstraction\n";
  Log.info ("\n"^(CPAbs.to_string bta abs));
  let positive_re = regexp "\\(.\\|\n\\)*is true\\(.\\|\n\\)*$" in
  try
    for it = 0 to max_iterations do
      Stats.cegar_nb_iterations := it;
      Stats.cegar_nb_clock_predicates := CPAbs.size abs;
      Stats.print_cegar_stats();
        (*
      printf "************************\n\t\t\tCEGAR Iteration: %d\n\
\t\t\t#Predicates: %d\n************************\n" it (CPAbs.size abs);
           *)
      let smv_enc = SMVInterface.dump_model bta abs in
      let (pin,pout) = Unix.open_process (sprintf "%s -int" nusmv_cmd) in
      fprintf pout "read_model -i /tmp/a.smv\n";
      fprintf pout "%s" script;
      flush pout;
         (*
      let (pin,pout) = Unix.open_process (sprintf "%s /tmp/a.smv" nusmv_cmd) in
      flush pout;
         *)
      Log.info (sprintf "Waiting for %s for iteration %d...\n" nusmv_cmd !Stats.cegar_nb_iterations); flush stdout;
      let nusmv_output = IO.read_all pin in
      ignore(Unix.close_process (pin,pout));
      if string_match positive_re nusmv_output 0 then (
        raise Result_true
      ) else (
        try
          let trace_re = regexp "<!-- ################### Trace number: 1 ################### -->" in
          let ind = search_forward trace_re nusmv_output 0 in
          let cex_string = string_after nusmv_output (ind) in
          (match SMVInterface.refine bta abs smv_enc cex_string  with 
           | SMVInterface.CannotRefine ->
             Log.info "Don't know how to refine. Aborting \n";
             raise Result_unknown
           | SMVInterface.Refined ->
             Log.info "Refined successfully\n";
           | SMVInterface.Genuine ->
             Log.info "Counter-example confirmed\n";
             raise Result_false
          )
        with Not_found ->
          Log.fatal (sprintf "Cannot parse output\n%s\n"
            (nusmv_output));
          raise Result_unknown
      )
    done;
    "unknown"
  with Result_true ->
    Stats.print_cegar_stats();
    "NOT REACHABLE"
     | Result_false ->
       Stats.print_cegar_stats();
       "REACHABLE"
     | Result_unknown ->
       Stats.print_cegar_stats();
       "UNKNOWN"
