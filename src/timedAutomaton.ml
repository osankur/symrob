open Batteries
open Common
open Pdbm
open Printf
open Uta

exception NotRectangular

type 'a single_or_pair =
    Single of 'a
  | Pair of 'a * 'a


module type TIMED_AUTOMATON =
sig
  module Dbm : GENERIC_DBM
  type timed_automaton
  type discrete_state
  type transition
  val nb_clocks : timed_automaton -> int
  val clocks : timed_automaton -> string VarContext.t
  val is_state_equal : timed_automaton -> discrete_state -> discrete_state -> bool
  val initial_discrete_state : timed_automaton -> discrete_state
  val transitions_from : timed_automaton -> discrete_state -> transition list
  val transition_fields : timed_automaton -> transition ->
    (discrete_state * Dbm.t * ClockSet.t * discrete_state)
  val guard_of_transition : timed_automaton -> transition -> Dbm.t
  val invariant_of_discrete_state : timed_automaton -> discrete_state -> Dbm.t
  val print_transition : 'b BatIO.output -> timed_automaton -> transition -> unit
  val is_urgent_or_committed : timed_automaton -> discrete_state -> bool
  val print_discrete_state  : 'b BatIO.output -> timed_automaton -> discrete_state -> unit
  val print_timed_automaton : 'b BatIO.output -> timed_automaton -> unit
  val print_extended_state : 'b BatIO.output -> timed_automaton -> (discrete_state * Dbm.t) -> unit
  val initial_extended_state : timed_automaton -> discrete_state * Dbm.t
  val is_target : timed_automaton -> discrete_state -> bool
  val lu_bounds : timed_automaton -> discrete_state -> int array -> int array -> unit
  val guard_and_invar_constants : timed_automaton -> Dbm.Alg.t array array array
end

module type TIMED_GAME =
sig
  include TIMED_AUTOMATON
  val is_controllable : timed_automaton -> edge -> bool
end

module type ENLARGED_TIMED_AUTOMATON =
sig
  module Dbm : ENLARGED_DBM 
  type timed_automaton
  type discrete_state
  type transition
  val is_state_equal : timed_automaton -> discrete_state -> discrete_state -> bool
  val clocks : timed_automaton -> string VarContext.t
  val transitions_from : timed_automaton -> discrete_state -> transition list
  val transition_fields : timed_automaton -> transition ->
    (discrete_state * Dbm.t * ClockSet.t * discrete_state)
  val invariant_of_discrete_state : timed_automaton -> discrete_state -> Dbm.t
  val print_transition : 'b BatIO.output -> timed_automaton -> transition -> unit
  val print_discrete_state  : 'b BatIO.output -> timed_automaton -> discrete_state -> unit
  val print_timed_automaton : 'b BatIO.output -> timed_automaton -> unit
  val print_extended_state : 'b BatIO.output -> timed_automaton -> (discrete_state * Dbm.t) -> unit 
  val is_urgent_or_committed : timed_automaton -> discrete_state -> bool
  val is_target : timed_automaton -> discrete_state -> bool
  val initial_extended_state : timed_automaton -> discrete_state * Dbm.t
  val lu_bounds : timed_automaton -> discrete_state -> int array -> int array -> unit
end

module GenericUautomaton (Dbm : GENERIC_DBM) =
struct 
  (** Expression type used in the guard and updates
      involving variables. In contrast with Uta.expression 
      used by the parser, the variables in this one are indexed
      by their unique integer identifiers and we distinguish clocks
  *)
  type expression = 
      Constant of int
    | Variable of int
    | Clock of int
    | Sum of expression * expression
    | Product of expression * expression
    | Subtraction of expression * expression
    | Division of expression * expression
    | BoolNot of expression
    | BoolNeq of expression * expression
    | BoolEq of expression * expression
    | BoolAnd of expression * expression

  type atomic_guard =
      GuardLeq of expression * expression
    | GuardLess of expression * expression
    | GuardGeq of expression * expression
    | GuardGreater of expression * expression
    | GuardEqual of expression * expression
    | GuardNeq of expression * expression

  type guard = atomic_guard list

  type update = (int * expression) list

  type edge = {
    edgeSource : int;
    edgeGuard : guard;
    edgeDiscGuard : guard;
    edgeReset : ClockSet.t;
    edgeDiscUpdate : update;
    edgeTarget : int;
    edgeSync : chan option;
    mutable edgeProc : int;
    edgeControllable : bool
  }
  and location = {
    locId : int;
    mutable locName : string;
    locCommitted : bool;
    locUrgent : bool;
    locInvar : guard;
    locEdges : edge list;
    mutable locProc : int;
  }
  and process = {
    procName : string;
    procId : int;
    procLocations : location array;
    procInitLoc : int;
  }
  type discrete_state = {
    stateLocs : location array;
    stateVars : int array;
  }

  type transition = InternalTrans of discrete_state * edge
                  | SyncTrans of discrete_state * edge * edge

  (** A succinct version of the above to be used in hash tables; we just don't need the varible valuations *)
  type _succinct_transition = Suc_InternalTrans of edge
                            | Suc_SyncTrans of edge * edge

  type query = EmptyQuery
             | AndQuery of query * query
             | OrQuery of query * query
             | NotQuery of query
             (* Process of given index is at location *)
             | AtomicQuery of int * location

  type timed_automaton = {
    procs : process array;
    clocks : string VarContext.t;
    vars : string VarContext.t;
    init : discrete_state;
    mutable query : query;
    mutable lowerLU : int array array array;
    mutable upperLU : int array array array;
    guards_tbl : (_succinct_transition,Dbm.t) Hashtbl.t;
    invars_tbl : (location array,Dbm.t) Hashtbl.t;
    mutable rectangular : bool
  }

  (************************* STRING and PRINT *********************)
  let rec string_of_exp ta ?equal_sign:(equal_sign="==") e = 
    let string_of_exp = string_of_exp ta ~equal_sign:equal_sign in
    (function
      | Constant c -> sprintf "%d" c 
      | Variable(id) -> VarContext.var_of_index ta.vars id
      | Clock(id) ->  VarContext.var_of_index ta.clocks id
      | Product(e1,e2) ->
        sprintf "%s * %s" (string_of_exp e1)
          (string_of_exp e2)
      | Sum(e1,e2) ->
        sprintf "(%s + %s)" (string_of_exp e1)
          (string_of_exp e2)
      | Division(e1,e2) ->
        sprintf "%s / %s" (string_of_exp e1)
          (string_of_exp e2)
      | Subtraction(e1,e2) ->
        sprintf "(%s - %s)" (string_of_exp e1)
          (string_of_exp e2)
      | BoolEq(e1,e2) ->
        sprintf "(%s %s %s)" (string_of_exp e1)
          equal_sign
          (string_of_exp e2)
      | BoolNeq(e1,e2) ->
        sprintf "(%s != %s)" (string_of_exp e1)
          (string_of_exp e2)
      | BoolAnd(e1,e2) ->
        sprintf "(%s & %s)" (string_of_exp e1)
          (string_of_exp e2)
      | BoolNot(e1) ->
        sprintf "!(%s)" (string_of_exp e1)
    ) e

  let string_of_atomic_guard ta = 
    let string_of_exp = string_of_exp ta in
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
      sprintf "%s == %s" (string_of_exp v) (string_of_exp exp)
    | GuardNeq(v,exp)->
      sprintf "%s != %s" (string_of_exp v) (string_of_exp exp)

  let xml_string_of_atomic_guard ta =
    let string_of_exp = string_of_exp ta in
    function
    |  GuardLeq(v,exp) ->
      sprintf "%s &lt;= %s" (string_of_exp v)(string_of_exp exp)
    | GuardLess(v,exp) ->
      sprintf "%s &lt; %s" (string_of_exp v)(string_of_exp exp)
    | GuardGeq(v,exp)->
      sprintf "%s &gt;= %s" (string_of_exp v)(string_of_exp exp)
    | GuardGreater(v,exp)->
      sprintf "%s &gt; %s" (string_of_exp v) (string_of_exp exp)
    | GuardEqual(v,exp)->
      sprintf "%s == %s" (string_of_exp v) (string_of_exp exp)
    | _ -> failwith "not implemented"


  let rec string_of_guard ta =
    function
    | [] -> ""
    | [x] -> string_of_atomic_guard ta x
    | x :: y :: l ->
      ((string_of_atomic_guard ta x) ^ " && ")
      ^ (string_of_guard ta (y::l))

  let rec xml_string_of_guard ta =
    function
    | [] -> ""
    | [x] -> xml_string_of_atomic_guard ta x
    | x :: y :: l -> 
      ((xml_string_of_atomic_guard ta x) ^ " &amp;&amp; ")
      ^ (xml_string_of_guard ta (y::l))

  let string_of_updates ta ups = 
    let ups_str = 
      List.map (fun (var,exp) -> sprintf "%s = %s" (VarContext.var_of_index ta.vars var) (string_of_exp ta exp)) ups in
    String.concat ", " ups_str

  (** Pretty Printing Functions *)
  let string_of_state ta state =
    let out = Buffer.create 50 in
    Array.iter (fun loc -> Buffer.add_string out loc.locName;
                 Buffer.add_string out " ") state.stateLocs;
    if (Array.length state.stateVars > 0 ) then (
      Buffer.add_string out "\n";
      Array.iteri (fun i v ->
          let name = VarContext.index2var ta.vars i in
          Buffer.add_string out (sprintf "%s = %d, " name v)) state.stateVars;
    );
    (*    Buffer.add_string out "\n";*)
    Buffer.contents out

  let string_of_edge ta edge =
    let proc = ta.procs.(edge.edgeProc) in
    let resetnames =
      let out = Buffer.create 100 in
      ClockSet.iter
        (fun ind -> 
           let name = VarContext.index2var ta.clocks ind in
           Buffer.add_string out name; 
           Buffer.add_string out " ") 
        edge.edgeReset;
      Buffer.contents out
    in
    let sync = match edge.edgeSync with 
      |None -> ""
      |Some(SendChan(c)) -> c^"!"
      |Some(RecvChan(c)) -> c^"?"
    in
    let discguardstr = string_of_guard ta edge.edgeDiscGuard in
    let guardstr = string_of_guard ta edge.edgeGuard in
    sprintf "%s%s -> %s \tDiscGuard: %s \tDiscUpdate: %s \tGuard: %s \tResets:%s \tSync:%s" 
      (if (edge.edgeControllable) then "" else "[E]")
      (proc.procLocations.(edge.edgeSource).locName)
      (proc.procLocations.(edge.edgeTarget).locName)
      discguardstr
      (string_of_updates ta edge.edgeDiscUpdate)
      guardstr
      resetnames
      sync
  (*
    sprintf "Edge:\n Target: %s.%s\n\tDiscGuard: %s\n\tDiscUpdate: %s\n\tGuard: %s\n\tResets:%s\n\tSync:%s\n" 
            proc.procName
            (proc.procLocations.(edge.edgeTarget).locName)
            discguardstr
            (string_of_updates ta edge.edgeDiscUpdate)
            guardstr
            resetnames
            sync
     *)

  let string_of_location ta loc =
    let out = Buffer.create 128 in
    let utter = Buffer.add_string out in
    utter (sprintf "Location %d: %s "loc.locId loc.locName);
    if (loc.locCommitted) then
      utter "committed ";
    utter (string_of_guard ta loc.locInvar);
    utter "\n";
    utter (sprintf "Has %d edges:\n" (List.length loc.locEdges));
    let edgestrlist = (List.map (string_of_edge ta) loc.locEdges) in
    utter (String.concat "\n" edgestrlist);
    utter "\n";
    Buffer.contents out

  let string_of_process ta proc = 
    let out = Buffer.create 1000 in
    let utter = Buffer.add_string out in
    utter (sprintf "Process(%d): %s\n"  proc.procId proc.procName);
    Array.iter (fun loc -> utter (string_of_location ta loc)) proc.procLocations;
    utter (sprintf "Initial location id: %d\n" proc.procInitLoc);
    Buffer.contents out

  let string_of_transition ta tr =
    let buf = Buffer.create 128 in
    let out = Buffer.add_string buf in
    let proc_name e = ta.procs.(e.edgeProc).procName
    in
    match tr with 
      InternalTrans(state,e) ->
      out (sprintf "From global state: %s\n" (string_of_state ta state));
      out (string_of_edge ta e);
      Buffer.contents buf
    | SyncTrans(state,e1,e2) ->
      out (sprintf "Synchronized Transition btw Processes: %s - %s\n Source: %s\n" (proc_name e1) (proc_name e2)
             (string_of_state ta state));
      out "Sync:\n";
      out (string_of_edge ta e1);
      out "\n";
      out (string_of_edge ta e2);
      Buffer.contents buf

  let print_discrete_state chan ta state =
    fprintf chan "%s\n" (string_of_state ta state)

  let print_timed_automaton chan ta =
    fprintf chan "Timed automaton with %d clocks and %d processes\n"
      (VarContext.size ta.clocks) (Array.length ta.procs);
    Array.iter (fun proc -> fprintf chan "%s\n-----\n" (string_of_process ta proc)) ta.procs

  let print_extended_state chan ta (state,dbm) =
    fprintf chan "%s " (string_of_state ta state);
    Dbm.pretty_print chan ta.clocks dbm

  let print_transition chan ta trans = 
    fprintf chan "%s\n" (string_of_transition ta trans)

  (************************* TIMED_AUTOMATON interface *********************)
  let clocks ta = ta.clocks
  let initial_discrete_state ta = ta.init

  let is_state_equal ta s t =
    not(
      (Array.exists2 (fun l1 l2 -> not (l1.locId = l2.locId)) s.stateLocs t.stateLocs)
      ||
      (Array.exists2 (fun v1 v2 -> not (v1 = v2)) s.stateVars t.stateVars)
    )

  let is_committed state = 
    Array.exists (fun loc -> loc.locCommitted) state.stateLocs

  let is_target ta state =
    let rec eval = function
      | EmptyQuery -> false
      | AtomicQuery(p,l) -> state.stateLocs.(p) = l
      | OrQuery(p1,p2) -> (eval p1) || (eval p2)
      | AndQuery(p1,p2) -> (eval p1) && (eval p2)
      | NotQuery(p) -> not (eval p)
    in
    eval ta.query

  let lu_bounds ta state lbounds ubounds =
    Array.iteri (fun i _ -> 
        lbounds.(i) <- Pdbm.minfty_val;
        ubounds.(i) <- Pdbm.minfty_val
      ) lbounds;
    lbounds.(0) <- 0;
    ubounds.(0) <- 0;
    let nprocs = Array.length state.stateLocs in
    let nclocks = VarContext.size ta.clocks in 
    for iproc = 0 to nprocs - 1 do
      let iloc = state.stateLocs.(iproc).locId in
      for cl = 0 to nclocks - 1 do
        lbounds.(cl) <- max lbounds.(cl) ta.lowerLU.(iproc).(iloc).(cl);
        ubounds.(cl) <- max ubounds.(cl) ta.upperLU.(iproc).(iloc).(cl);
      done;
    done

  let is_urgent_or_committed ta state = 
    Array.exists (fun loc -> loc.locCommitted || loc.locUrgent) state.stateLocs

  let get_location_of_process state procid = 
    state.stateLocs.(procid)

  let source_location_of_edge ta edge =
    ta.procs.(edge.edgeProc).procLocations.(edge.edgeSource)

  let get_process ta procid = 
    ta.procs.(procid)

  let nb_of_processes ta = 
    Array.length ta.procs

  let nb_clocks ta = VarContext.size ta.clocks

  let rec eval_disc_exp ta vars exp =
    try
      let k =
        (match exp with
         | Constant c -> c
         | Variable(id) -> 
           if ( id < 0 || id >= Array.length vars ) then
             failwith (sprintf "Var index %d out of bounds (%d)" id (Array.length vars));
           vars.(id)
         | Clock(id) ->raise Found
         | Product(e1,e2) -> (eval_disc_exp ta vars e1) * (eval_disc_exp ta vars e2)
         | Sum(e1,e2) -> (eval_disc_exp ta vars e1) + (eval_disc_exp ta vars e2)
         | Division(e1,e2) -> (eval_disc_exp ta vars e1) / (eval_disc_exp ta vars e2)
         | Subtraction(e1,e2) -> (eval_disc_exp ta vars e1) - (eval_disc_exp ta vars e2)
         | BoolAnd(e1,e2) -> if (eval_disc_exp ta vars e1) <> 0 && (eval_disc_exp ta vars e2) <> 0 then 1 else 0
         | BoolEq(e1,e2) -> if (eval_disc_exp ta vars e1) = (eval_disc_exp ta vars e2) then 1 else 0
         | BoolNeq(e1,e2) -> if (eval_disc_exp ta vars e1) <> (eval_disc_exp ta vars e2) then 1 else 0
         | BoolNot(e1) ->  if (eval_disc_exp ta vars e1) = 0 then 1 else 0
        ) in
      (*
      eprintf "%s -----> %d\n" (string_of_exp ta exp) k;
       *)
      k
    with Found ->
      failwith ("Discrete expression contains clock: " ^ (string_of_exp ta exp)); 
       | e -> raise e
(*
  let rec eval_bool_exp ta vars = function
    | BoolAnd(e1,e2) -> (eval_bool_exp ta vars e1) &&  (eval_bool_exp ta vars e2)
    | BoolEq(e1,e2) -> (eval_bool_exp ta vars e1) = (eval_bool_exp ta vars e2)
    | BoolNeq(e1,e2) -> (eval_bool_exp ta vars e1) <>  (eval_bool_exp ta vars e2)
    | BoolNot(e1) -> not (eval_bool_exp ta vars e1)
*)
  let eval_disc_guard ta state guard =
    let eval =
      eval_disc_exp ta state.stateVars
    in
    let atomic = function
      | GuardLeq(e1,e2) ->
        (eval e1) <= (eval e2)
      | GuardLess(e1,e2) ->
        (eval e1) < (eval e2)
      | GuardGeq(e1,e2) ->
        (eval e1) >= (eval e2)
      | GuardGreater(e1,e2) ->
        (eval e1) > (eval e2)
      | GuardEqual(e1,e2) ->
        (eval e1) = (eval e2)
      | GuardNeq(e1,e2) ->
        (eval e1) <> (eval e2)
    in
    List.fold_left (fun b ag -> b && (atomic ag)) true guard

  let transitions_from ta state =
    let committed = is_committed state in
    let transq = Queue.create () in
    (* Queue of synchronizing edges *)
    let rchan = Queue.create () in
    let schan = Queue.create () in
    let nproc = Array.length ta.procs in
    for i = 0 to nproc - 1 do
      let loc = state.stateLocs.(i) in
      let add_single =  not committed || loc.locCommitted in
      List.iter
        (fun edge ->
           if (eval_disc_guard ta state edge.edgeDiscGuard ) then
             (match edge.edgeSync with
                Some (SendChan(c)) ->
                Queue.add (c,edge) schan
              | Some (RecvChan(c)) ->
                Queue.add (c,edge) rchan
              | None ->
                if ( add_single ) then
                  Queue.add (InternalTrans (state,edge)) transq
             )
        ) loc.locEdges
    done;
    Queue.iter
      (fun (rname, redge) ->
         Queue.iter
           (fun (sname,sedge) ->
              (* Sync if same channels are used by different processes *)
              if (rname = sname && redge.edgeProc <> sedge.edgeProc) then (
                (* and if state not committed or one of the participating states are *)
                let sloc = source_location_of_edge ta sedge in
                let rloc = source_location_of_edge ta redge in
                if ( not committed || sloc.locCommitted || rloc.locCommitted ) then
                  Queue.add (SyncTrans (state,redge,sedge)) transq
              )
           ) schan
      ) rchan;
    Queue.fold (fun l tr -> tr :: l) [] transq


  let _guard_to_dbm ta state g = 
    let nclocks = VarContext.size ta.clocks in
    let dbm = Dbm.create nclocks in
    let aux = function
      | GuardLeq(Clock(c), e) ->
        let k = eval_disc_exp ta state e in
        Dbm.assign_constraint dbm c 0 (Dbm.Alg.weak_from_int k)
      | GuardLess(Clock(c), e) ->
        let k = eval_disc_exp ta state e in
        Dbm.assign_constraint dbm c 0 (Dbm.Alg.strict_from_int k)
      | GuardGeq(Clock(c), e) ->
        let k = eval_disc_exp ta state e in
        Dbm.assign_constraint dbm 0 c (Dbm.Alg.weak_from_int (-k))
      | GuardGreater(Clock(c), e) ->
        let k = eval_disc_exp ta state e in
        Dbm.assign_constraint dbm 0 c (Dbm.Alg.strict_from_int (-k))
      | GuardEqual(Clock(c), e) ->
        let k = eval_disc_exp ta state e in
        Dbm.assign_constraint dbm 0 c (Dbm.Alg.weak_from_int (-k));
        Dbm.assign_constraint dbm c 0 (Dbm.Alg.weak_from_int k)
      | _ as e -> failwith (sprintf "Bad Guard: %s" (string_of_guard ta [e]))
    in
    List.iter aux g;
    Dbm.reduce dbm;
    dbm

  let _copy_state state = 
    { stateVars = Array.copy state.stateVars;
      stateLocs = Array.copy state.stateLocs}


  (** Apply discrete update of edge to state, result written in state' *)
  let _apply_edge ta state edge state' =
    let aux = fun (id,e) -> 
      state'.stateVars.(id) <- eval_disc_exp ta state.stateVars e
    in
    let tproc = ta.procs.(edge.edgeProc) in
    state'.stateLocs.(tproc.procId) <- tproc.procLocations.(edge.edgeTarget);
    List.iter aux edge.edgeDiscUpdate

  let guard_of_transition ta tr = 
    let to_succinct = function
      |InternalTrans(_,e) -> Suc_InternalTrans(e)
      |SyncTrans(_,e1,e2) -> Suc_SyncTrans(e1,e2)
    in
    let str = to_succinct tr in
    try
      Hashtbl.find ta.guards_tbl str
    with Not_found ->
      (match tr with
       | InternalTrans(state,e) ->
         let g =_guard_to_dbm ta state.stateVars e.edgeGuard in
         Hashtbl.add ta.guards_tbl str g;
         g
       | SyncTrans(state,e1,e2) -> 
         let g1 = _guard_to_dbm ta state.stateVars e1.edgeGuard in
         let g2 = _guard_to_dbm ta state.stateVars e2.edgeGuard in
         Dbm.intersect g1 g2;
         Hashtbl.add ta.guards_tbl str g1;
         g1
      ) 
       |_ as e -> raise e

  let invariant_of_discrete_state ta state = 
    try 
      Hashtbl.find ta.invars_tbl state.stateLocs
    with Not_found ->
      let glob_inv = 
        Array.fold_left (fun acc loc -> loc.locInvar @ acc ) [] state.stateLocs in
      let inv = _guard_to_dbm ta state.stateVars glob_inv in
      Hashtbl.add ta.invars_tbl state.stateLocs inv;
      inv
       | _ as e -> raise e

  let transition_fields ta = function
    | InternalTrans(state,e) ->
      let state' = _copy_state state in
      _apply_edge ta state e state';
      (state, 
       _guard_to_dbm ta state.stateVars e.edgeGuard, 
       e.edgeReset, 
       state')
    | SyncTrans(state,e1,e2) -> 
      let state' = _copy_state state in
      _apply_edge ta state e1 state';       
      _apply_edge ta state e2 state';
      let g1 = _guard_to_dbm ta state.stateVars e1.edgeGuard in
      let g2 = _guard_to_dbm ta state.stateVars e2.edgeGuard in
      Dbm.intersect g1 g2;
      (state, g1, (ClockSet.union e1.edgeReset e2.edgeReset), state')

  let next_location_vector ta locs tr =
    let locs' = Array.copy locs in
    (match tr with
    | InternalTrans(state, e) ->
      locs'.(e.edgeProc) <- ta.procs.(e.edgeProc).procLocations.(e.edgeTarget);
    | SyncTrans(state, e1, e2) ->
      locs'.(e1.edgeProc) <- ta.procs.(e1.edgeProc).procLocations.(e1.edgeTarget);
      locs'.(e2.edgeProc) <- ta.procs.(e2.edgeProc).procLocations.(e2.edgeTarget)
    );
    locs'


  let initial_extended_state ta = 
    let dim = (VarContext.size (clocks ta)) in 
    let z = Dbm.create dim in
    (try
       for i = 0 to dim -1 do
         Dbm.constrain z i 0 Dbm.Alg.zero;
         Dbm.constrain z 0 i Dbm.Alg.zero
       done;
       Dbm.posttime z;
       let inv = (invariant_of_discrete_state ta ta.init) in
       Dbm.intersect z inv
     with EmptyDBM -> Log.fatal "The initial state is empty\n"
        | _ as e-> raise e
    );
    (ta.init, z)



  (** Constructor Functions *)


  (** This is pretty much a direct translation from LocalLUNormalizer class of Verifix.
      @return a pair (lower,upper) corresponding to L and U values, three-dimensional arrays indexed by  process, location, and clock
      *)
  let _make_lu_table ta = 
    let nclocks = VarContext.size ta.clocks in
    let maketable () = 
      Array.map (fun proc -> 
          Array.map (fun loc ->
              Array.init nclocks (fun c -> Pdbm.minfty_val)
            ) proc.procLocations
        ) ta.procs
    in
    let upper = maketable () in
    let lower = maketable () in
    let process iproc iloc g = 
      let aux = function
        | GuardLeq(Clock(l),Constant(r)) ->
          upper.(iproc).(iloc).(l) <- max upper.(iproc).(iloc).(l) r
        | GuardLess(Clock(l),Constant(r)) ->
          upper.(iproc).(iloc).(l) <- max upper.(iproc).(iloc).(l) r
        | GuardEqual(Clock(l),Constant(r)) ->
          upper.(iproc).(iloc).(l) <- max upper.(iproc).(iloc).(l) r;
          lower.(iproc).(iloc).(l) <- max lower.(iproc).(iloc).(l) r
        | GuardGreater(Clock(l),Constant(r)) ->
          lower.(iproc).(iloc).(l) <- max lower.(iproc).(iloc).(l) r
        | GuardGeq(Clock(l),Constant(r)) ->
          lower.(iproc).(iloc).(l) <- max lower.(iproc).(iloc).(l) r
        | _ ->
          Log.info "Non-rectangular guard detected. Will not apply extrapolation";
          raise NotRectangular
          (*failwith "Cannot compute lu bounds: Guards not in normal form."*)
      in
      List.iter aux g
    in
    let close bounds iproc proc = 
      let stable = ref false in
      while (not !stable) do
        stable := true;
        Array.iter (fun loc -> 
            List.iter (fun edge ->
                let source = edge.edgeSource in
                let target = edge.edgeTarget in
                let sourceBnd = bounds.(iproc).(source) in
                let targetBnd = bounds.(iproc).(target) in
                for j = 1 to (VarContext.size ta.clocks)-1 do
                  if (not (ClockSet.mem j edge.edgeReset)) then (
                    if (targetBnd.(j) > sourceBnd.(j) ) then(
                      sourceBnd.(j) <- targetBnd.(j);
                      stable := false
                    )
                  )
                done
              ) loc.locEdges
          ) proc.procLocations
      done;
    in
    Array.iteri (fun iproc proc -> 
        (* Initialize *)
        Array.iteri (fun iloc loc ->
            List.iter (fun edge ->
                process iproc iloc edge.edgeGuard) 
              loc.locEdges;
            process iproc iloc loc.locInvar
          ) proc.procLocations;
        (* Close *)
        close lower iproc proc;
        close upper iproc proc;
      ) ta.procs;
    (lower,upper)


  (** Constructs a timed_automaton. The constructor function is parameterized
   *  by guard_of_transition and invariant_of_discrete_state so that we can 
   *  instantiate it for other kinds of automata (enlarged automata below)
   *  in modules extending the current one.
       @param sys parsed system (Uta.system)
       @param scale scales all constants by scale
       @param enlarge enlarges all constants by enlarge (after having scaled)
       @param (guard_of_transition,invariant_of_discrete_state)
      *)
  let make_ta (guard_of_transition, invariant_of_discrete_state) sys ?scale ?enlarge () = 
    let templates = sys.sysTemplates in 
    (** Variable and clock contexts have initially keys of type (p,name)
     * where p is process option (None for global variables),
     * and name the name of the variable. *)
    let varcont = VarContext.create () in
    let var_init_values = Hashtbl.create 10 in
    let const_values = Hashtbl.create 10 in
    let clockcont = VarContext.create () in
    VarContext.add clockcont (None,"0");
    let constcont = VarContext.create () in
    (* Function to register global clocks and variables *)
    let register_vars tmp (clocks,vars) = 
      List.iter (fun cl -> 
          try VarContext.add clockcont (tmp,cl) 
          with Var_already_defined -> 
            eprintf "Variable %s is already defined\n" cl;
            failwith "Error"
             | _ as e ->
               raise e
        ) clocks;
      List.iter (fun var -> 
          try 
            match var with
              Var(id,v,(l,r)) ->
              (*
              printf "Registering %s (initially %d) with (%d,%d)\n" id v l r;
                 *)
              VarContext.add varcont ~range:(l,r) (tmp,id);
              let index = VarContext.index_of_var varcont (tmp,id) in
              Hashtbl.add var_init_values index v
                (*
              let (l',r') = VarContext.range_of_index varcont index in
                   *)
            | ConstVar(id,v) ->
              VarContext.add constcont (tmp,id);
              let index = VarContext.index_of_var constcont (tmp,id) in
              Hashtbl.add const_values index v
          with Var_already_defined ->
            eprintf "Variable %s is already defined\n" (name_of_var var);
            failwith "Error"
             | _ as e ->
               raise e
        ) vars
    in
    (* Register variables: first global ones then local ones *)
    register_vars None (sys.sysClocks, sys.sysVars);
    List.iter (fun tmp -> register_vars (Some tmp) (tmp.tempClocks, tmp.tempVars) ) templates;
    let nvars = (VarContext.size varcont) in
    let is_clock tmp var = 
      if (VarContext.mem clockcont (Some tmp,var)) then
        true
      else if (VarContext.mem clockcont (None,var)) then
        true
      else 
        false
    in
    let get_clock_id tmp var = 
      if (VarContext.mem clockcont (Some tmp,var) ) then
        VarContext.index_of_var clockcont (Some tmp,var)
      else
        VarContext.index_of_var clockcont (None,var)
    in
    (* Convert the given Uta.expression inside the template tmp to the local exp type
       by replacing variable names by their integer identifiers. 
       Also instantiates constants
       and partially evaluates the arithmetic operations  *)
    let convert_exp tmp exp = 
      let rec eval = function
        | Uta.Constant(c) -> Constant(c)
        | Uta.Variable(name) -> 
          (* We first check if the variable is a constant *)
          if (VarContext.mem constcont (Some tmp,name) ) then
            (* Is it a local constant? *)
            let varid = VarContext.index_of_var constcont (Some tmp,name) in
            Constant(Hashtbl.find const_values varid)
          else if (VarContext.mem constcont (None,name)) then
            (* Is it a global constant ? *)
            let varid = VarContext.index_of_var constcont (None,name) in
            Constant(Hashtbl.find const_values varid)
          else if (VarContext.mem varcont (Some tmp,name)) then
            (* Is it a local variable? *)
            let varid = VarContext.index_of_var varcont (Some tmp,name) in
            Variable(varid)
          else if (VarContext.mem varcont (None,name)) then
            (* Is it a global variable? *)
            let varid = VarContext.index_of_var varcont (None,name) in
            Variable(varid)
          else if (VarContext.mem clockcont (Some tmp, name) ) then
            (* Local clock *)
            let varid = VarContext.index_of_var clockcont (Some tmp,name) in
            Clock(varid)
          else if (VarContext.mem clockcont (None, name) ) then
            (* Global clock *)
            let varid = VarContext.index_of_var clockcont (None,name) in
            Clock(varid)
          else (
            eprintf "Printing final VarContext\n";
            VarContext.iter
              (fun (t,name) ind ->
                 let scope = match t with None -> "None" | Some tmp -> tmp.tempName
                 in
                 eprintf "\t%d <%s> : %s\n" ind  name scope
              ) varcont;
            printf "%b\n" (VarContext.mem varcont (Some tmp, name));
            failwith (sprintf "Undefined variable <%s>" name)
          )
        | Uta.Sum(e1,e2)  ->
          let ne1 = eval e1 in
          let ne2 = eval e2 in
          (match (ne1,ne2) with
             Constant(v1), Constant(v2) -> Constant(v1 + v2)
           | _ -> Sum(ne1,ne2)
          )
        | Uta.Subtraction(e1,e2)  ->
          let ne1 = eval e1 in
          let ne2 = eval e2 in
          (match (ne1,ne2) with
             Constant(v1), Constant(v2) -> Constant(v1 - v2)
           | _ -> Subtraction(ne1,ne2)
          )
        | Uta.Product(e1,e2)  ->
          let ne1 = eval e1 in
          let ne2 = eval e2 in
          (match (ne1,ne2) with
             Constant(v1), Constant(v2) -> Constant(v1 * v2)
           | _ -> Product(ne1,ne2)
          )
        | Uta.Division(e1,e2)  ->
          let ne1 = eval e1 in
          let ne2 = eval e2 in
          (match (ne1,ne2) with
             Constant(v1), Constant(v2) -> Constant(v1 / v2)
           | _ -> Division(ne1,ne2)
          )
        | Uta.BoolNot(e) -> BoolNot(eval e)
        | Uta.BoolAnd(e1,e2) -> BoolAnd(eval e1, eval e2)
        | Uta.BoolEq(e1,e2) -> BoolEq(eval e1, eval e2)
        | Uta.BoolNeq(e1,e2) -> BoolNeq(eval e1, eval e2)
      in
      eval exp
    in
    (*
    let rec convert_bool_exp tmp = function
      | Uta.BoolNot e -> BoolNot(convert_bool_exp tmp e)
      | Uta.BoolEq (e1,e2) -> BoolEq(convert_bool_exp tmp e1, convert_bool_exp tmp e2)
      | Uta.BoolNeq (e1,e2) -> BoolNeq(convert_bool_exp tmp e1, convert_bool_exp tmp e2)
      | Uta.BoolAnd (e1,e2) -> BoolAnd(convert_bool_exp tmp e1, convert_bool_exp tmp e2)
    in
       *)
    let convert_guard tmp g  =
      let convert_atomic_guard = function
        | Uta.GuardLeq(e1,e2) -> GuardLeq(convert_exp tmp e1, convert_exp tmp e2)
        | Uta.GuardLess(e1,e2) -> GuardLess(convert_exp tmp e1, convert_exp tmp e2)
        | Uta.GuardGeq(e1,e2) -> GuardGeq(convert_exp tmp e1, convert_exp tmp e2)
        | Uta.GuardGreater(e1,e2) -> GuardGreater(convert_exp tmp e1, convert_exp tmp e2)
        | Uta.GuardEqual(e1,e2) -> GuardEqual(convert_exp tmp e1, convert_exp tmp e2)
        | Uta.GuardNeq(e1,e2) -> GuardNeq(convert_exp tmp e1, convert_exp tmp e2)
      in
      (* Make sure clock guards have the form Guard*(Clock(cl),Constant(r)) *)
      let normalize_atomic_guard = function
        | GuardLeq(_ as k,Clock(cl)) ->
          GuardGeq(Clock(cl),k)
        | GuardLess(_ as k,Clock(cl)) ->
          GuardGreater(Clock(cl),k)
        | GuardGeq(_ as k,Clock(cl)) ->
          GuardLeq(Clock(cl),k)
        | GuardGreater(_ as k,Clock(cl)) ->
          GuardLess(Clock(cl),k)
        | GuardEqual(_ as k,Clock(cl)) ->
          GuardEqual(Clock(cl),k)
        | e -> e
      in
      let aux ag = 
        normalize_atomic_guard (convert_atomic_guard ag)
      in
      let g = List.map aux g in
      g
    in
    (** Instantiate constants inside updates *)
    let convert_update tmp up =
      List.map (fun (var,exp) ->
          let varid =
            if (VarContext.mem varcont (Some tmp,var)) then
              VarContext.index_of_var varcont (Some tmp,var)
            else
              VarContext.index_of_var varcont (None,var)
          in
          (varid,convert_exp tmp exp)
        ) up
    in
    (** Get discrete guard from mixed guard *)
    let filter_disc_guard tmp g = 
      let filt_ag ag =
        List.for_all (fun name -> not (is_clock tmp name)) (vars_of_atomic_guard ag)
      in
      List.filter filt_ag g
    in
    (** Get clock guard from mixed guard *)
    (* TODO Also check here that there is no disc variable involved in the clock guards *)
    let filter_clock_guard tmp g =
      let filt_ag ag =
        List.exists (fun name -> (is_clock tmp name)) (vars_of_atomic_guard ag)
      in
      List.filter filt_ag g
    in
    (** Make clock reset set *)
    let clock_update tmp up =
      let reset = 
        (List.map (fun (name,_) -> get_clock_id tmp name)
           (List.filter (fun (var,_) -> is_clock tmp var) up))
        |>
        (List.fold_left (fun set cl -> ClockSet.add cl set) ClockSet.empty)
      in
      reset
    in
    (** scale all constants by scale and enlarge by enlarge*)
    let scale_and_enlarge_cguard g =
      let rec eval = function
        | Sum(e1,e2)  ->
          let ne1 = eval e1 in
          let ne2 = eval e2 in
          (match (ne1,ne2) with
             Constant(v1), Constant(v2) -> Constant(v1 + v2)
           | _ -> Sum(ne1,ne2)
          )
        | Subtraction(e1,e2)  ->
          let ne1 = eval e1 in
          let ne2 = eval e2 in
          (match (ne1,ne2) with
             Constant(v1), Constant(v2) -> Constant(v1 - v2)
           | _ -> Subtraction(ne1,ne2)
          )
        | Product(e1,e2)  ->
          let ne1 = eval e1 in
          let ne2 = eval e2 in
          (match (ne1,ne2) with
             Constant(v1), Constant(v2) -> Constant(v1 * v2)
           | _ -> Product(ne1,ne2)
          )
        | Division(e1,e2)  ->
          let ne1 = eval e1 in
          let ne2 = eval e2 in
          (match (ne1,ne2) with
             Constant(v1), Constant(v2) -> Constant(v1 / v2)
           | _ -> Division(ne1,ne2)
          )
        | e -> e
      in
      let scale_and_enlarge g = 
        match (scale, enlarge) with
        | Some(s), Some(d) ->
          let s = Constant(s) in
          let d = Constant(d) in
          (match g with
           | GuardLeq(Clock(_) as e1,e2) -> [GuardLeq(e1,eval (Sum(Product(e2,s),d)))]
           | GuardLess(Clock(_) as e1,e2) -> [GuardLess(e1,eval (Sum(Product(e2,s),d)))]
           | GuardGreater(Clock(_) as e1,e2) -> [GuardGreater(e1,eval (Subtraction(Product(e2,s),d)))]
           | GuardGeq(Clock(_) as e1,e2) -> [GuardGeq(e1,eval (Subtraction(Product(e2,s),d)))]
           | GuardEqual(Clock(_) as e1,e2) ->
             let se2 = Product(e2,s) in
             [GuardGeq(e1,eval (Subtraction(se2,d)));
              GuardLeq(e1,eval (Sum(se2,d)))
             ]
           | other ->
             failwith "Cannot enlarge non-normalized clock guard"
          )
        | _ -> [g]
      in
      List.fold_left (fun acc ag -> (scale_and_enlarge ag)@acc) [] g
    in
    (* Convert the (template,string) VarContext.t  to string VarContext.t
       by prepending the process names to variables and clocks. 
       We will just extract these elements from the hash tables, along with their indices,
       so as to reinsert them in the same order in the new VarContext.
       These contexts are only for pretty printing and have no role in simulation
    *)
    (*
    Hashtbl.iter (fun (_,name) ind ->
        printf "%d: %s\n" ind name;
      ) (VarContext.get_var2index varcont);
    Hashtbl.iter (fun ind (l,r) ->
        printf "RANGE(%d): %d %d\n" ind l r
      ) varcont.Uta.VarContext.index2range;
       *)
    let get_vc_elements vc = 
      Hashtbl.fold 
        (fun (tmp,name) index acc ->
           let prefix = match tmp with
               None -> ""
             | Some tmp -> tmp.tempName ^"."
           in
           let name = sprintf "%s%s" prefix name in
           let range = VarContext.range_of_index vc index in
           (index,range, name) :: acc
        ) (VarContext.get_var2index vc) [] 
    in
    let clist = List.sort compare (get_vc_elements clockcont) in
    let vlist = List.sort compare (get_vc_elements varcont) in
    let clocks = VarContext.create () in
    let vars = VarContext.create () in
    List.iter (fun (__,_,name) -> VarContext.add clocks name) clist;
    List.iter (fun (_,range,name) -> match range with
          None ->
          VarContext.add vars name
        | Some range ->
          VarContext.add vars ~range:range name
      ) vlist;
    let disc_update tmp up =
      List.filter (fun (var,_) -> not (is_clock tmp var)) up
    in
    (** Now we start making the timed automaton *)
    let make_proc id tmp =
      (* Assign integer identifiers to locations by their locId's.
         We assign id i to the i-th location in the list (see below)
      *)
      let locids = Hashtbl.create 50 in
      List.iteri (fun i loc -> Hashtbl.add locids loc.Uta.locId i) tmp.tempLocations;
      let make_edge edge =
        {
          edgeSource = Hashtbl.find locids edge.Uta.edgeSource;
          edgeTarget = Hashtbl.find locids edge.Uta.edgeTarget;
          edgeDiscGuard = convert_guard tmp (filter_disc_guard tmp edge.Uta.edgeGuard);
          edgeGuard = scale_and_enlarge_cguard
              (convert_guard tmp (filter_clock_guard tmp edge.Uta.edgeGuard));
          edgeReset = clock_update tmp edge.edgeUpdates;
          edgeDiscUpdate = convert_update tmp (disc_update tmp edge.edgeUpdates);
          edgeSync = edge.Uta.edgeSync;
          edgeProc = -1;
          edgeControllable = true;
        }
      in
      let make_loc loc = 
        let edges = 
          let e = List.filter
              (fun edge -> edge.Uta.edgeSource = loc.Uta.locId) tmp.tempEdges in
          List.map make_edge e
        in
        {
          locId = Hashtbl.find locids loc.Uta.locId;
          locName = if (loc.Uta.locName <> "") then loc.Uta.locName else loc.Uta.locId;
          locCommitted = loc.Uta.locCommitted;
          locUrgent = loc.Uta.locUrgent;
          locInvar = scale_and_enlarge_cguard (convert_guard tmp loc.Uta.locInvar);
          locEdges = List.rev edges;
          locProc = -1;
        }
      in
      let locslist = List.map make_loc tmp.tempLocations in
      let locs = Array.of_list locslist in
      {
        procName = tmp.Uta.tempName;
        procId = id;
        procLocations = locs;
        procInitLoc = Hashtbl.find locids tmp.tempInitialLocation.locId;
      } 
    in
    let procs = Array.of_list (List.mapi make_proc templates) in
    (* Fill in the edgeProc and locProc fields in all locations and edges *)
    Array.iter (fun proc -> 
        Array.iter (fun loc -> 
            loc.locName <- proc.procName ^ "." ^ loc.locName;
            loc.locProc <- proc.procId;
            loc.locEdges |>
            List.iter (fun edge -> edge.edgeProc <- proc.procId)
          ) proc.procLocations
      )
      procs;
    let initLocs = Array.map (fun proc -> proc.procLocations.(proc.procInitLoc)) procs in
    let initVars = Array.create nvars 0 in
    for i = 0 to nvars-1 do
      initVars.(i) <- Hashtbl.find var_init_values i;
    done;
    let ta = {
      procs = procs;
      clocks = clocks;
      vars = vars;
      init = {stateLocs = initLocs; stateVars = initVars};
      query = EmptyQuery;
      lowerLU = [||];
      upperLU = [||];
      guards_tbl = Hashtbl.create 1024;
      invars_tbl = Hashtbl.create 1024;
      rectangular = false
    }
    in
    (try
      let (lower,upper) = _make_lu_table ta in
      ta.lowerLU <- lower;
      ta.upperLU <- upper;
      ta.rectangular <- true
    with NotRectangular -> ());
    (** Check restrictions:
     * 1) No discrete variables in clock guards
     *    ( This restriction could actually be lifted
     *      by redefining the hash tables as a function
     *      from state = stateLocs * stateVars)
     *)
    let check_ta ta =
      let check_guard_no_discrete g = 
        let aux = function 
          |Variable(_) -> raise Found
          | _ -> ()
        in
        let atomic = function
          | GuardLess(e1,e2) -> aux e1; aux e2
          | GuardLeq(e1,e2) -> aux e1; aux e2
          | GuardGeq(e1,e2) -> aux e1; aux e2
          | GuardGreater(e1,e2) -> aux e1; aux e2
          | GuardEqual(e1,e2) -> aux e1; aux e2
          | _ -> ()
        in
        List.iter atomic g
      in
      (try
         ta.procs |> Array.iter (fun proc ->
             proc.procLocations |> 
             Array.iter (fun loc ->
                 check_guard_no_discrete loc.locInvar;
                 loc.locEdges |> List.iter (fun edge -> check_guard_no_discrete edge.edgeGuard)
               )
           ) 
       with Found -> failwith "We do not support discrete variables in clock guards"
          | _ as e -> raise e
      )
    in
    check_ta ta;
    ta

  let guard_and_invar_constants ta =
    let module IntSet = Batteries.Set.Make(struct type t = Dbm.Alg.t let compare = compare end) in
    let dim = (nb_clocks ta) + 1 in
    let abs = Array.init dim 
                (fun i -> Array.init dim 
                   (fun j -> ref (IntSet.empty) )
                ) in
    let add_to_abs =
      List.iter (function
          (* rectangular guards *)
          GuardLess(Clock c, Constant k) ->
          abs.(c).(0) := IntSet.add (Dbm.Alg.strict_from_int k) !(abs.(c).(0))
          | GuardLeq(Clock c,Constant k) -> 
          abs.(c).(0) := IntSet.add (Dbm.Alg.weak_from_int k) !(abs.(c).(0))
          | GuardGreater(Clock c,Constant k) -> 
          abs.(0).(c) := IntSet.add (Dbm.Alg.strict_from_int (-k)) !(abs.(0).(c))
          | GuardGeq(Clock c,Constant k) ->
            (* The c >= 0 predicate is useless *)
            if k <> 0 then
              abs.(0).(c) := IntSet.add (Dbm.Alg.weak_from_int (-k)) !(abs.(0).(c))
          | GuardEqual(Clock c,Constant k) ->
            (* The c >= 0 predicate is useless *)
            if k<> 0 then(
              abs.(0).(c) := IntSet.add (Dbm.Alg.weak_from_int (-k)) !(abs.(0).(c))
            );
            abs.(c).(0) := IntSet.add (Dbm.Alg.weak_from_int k) !(abs.(c).(0))

         (* diagonal guards *)
          | GuardLess(Subtraction(Clock c,Clock d),Constant k) ->
            abs.(c).(d) := IntSet.add (Dbm.Alg.strict_from_int k) !(abs.(c).(d))
          | GuardLeq(Subtraction(Clock c,Clock d),Constant k) ->
            abs.(c).(d) := IntSet.add (Dbm.Alg.weak_from_int k) !(abs.(c).(d))
          | GuardGreater(Subtraction(Clock c,Clock d),Constant k) ->
            abs.(d).(c) := IntSet.add (Dbm.Alg.strict_from_int (-k)) !(abs.(d).(c))
          | GuardGeq(Subtraction(Clock c,Clock d),Constant k) ->
            abs.(d).(c) := IntSet.add (Dbm.Alg.weak_from_int (-k)) !(abs.(d).(c))
          | GuardEqual(Subtraction(Clock c,Clock d),Constant k) ->
            abs.(d).(c) := IntSet.add (Dbm.Alg.weak_from_int (-k)) !(abs.(d).(c));
            abs.(c).(d) := IntSet.add (Dbm.Alg.weak_from_int k) !(abs.(c).(d))
          | _ as ag -> failwith (sprintf "Guard not in normal form: %s" (string_of_atomic_guard ta ag))
        )
    in
    Array.iter (fun proc ->
        (Array.iter (fun loc ->
             List.iter (fun edge -> 
                 add_to_abs edge.edgeGuard
               ) loc.locEdges;
             add_to_abs loc.locInvar
           )
        ) proc.procLocations
      ) ta.procs;
    let abs' =
      Array.map (Array.map (fun s -> IntSet.to_array !s)) abs in
    Array.iter (Array.iter (Array.sort compare)) abs';
    abs'

  let _convert_query ta (query : Uta.query) =
    let exception Found of int in
    let exception FoundLoc of location in
    let grab_proc_index_by_name name =
      try
(*        Array.iter (fun proc -> printf "Process: %s\n" proc.procName ) ta.procs;*)
        Array.iteri (fun i proc -> if proc.procName = name then raise (Found i)) ta.procs;
        failwith (sprintf "Querry Error: No process named %s" name)
      with Found i -> i
    in
    let grab_loc_by_name proc name =
      let name = proc.procName ^ "." ^ name in
      try
        Array.iteri (fun i loc -> if loc.locName = name then raise (FoundLoc loc)) proc.procLocations;
        failwith (sprintf "Querry Error: No location named %s in process %s" name proc.procName)
      with FoundLoc loc -> loc
    in
    let rec convert = function
    | Uta.AndQuery(a,b) -> AndQuery(convert a, convert b)
    | Uta.OrQuery(a,b) -> OrQuery(convert a, convert b)
    | Uta.NotQuery(a) -> NotQuery(convert a)
    | Uta.AtomicQuery(p,l) ->
      let proc_ind = grab_proc_index_by_name p in
      AtomicQuery(proc_ind, grab_loc_by_name ta.procs.(proc_ind) l)
    in
    match query with
    | Uta.EmptyQuery -> EmptyQuery
    | Uta.ReachQuery(pq) -> convert pq

  let from_file tafile qfile ?scale ?enlarge () =
    let pta  = UtaReader.nta_from_file (tafile) in
    let pquery = UtaReader.query_from_file qfile in
    let ta = 
    (match scale,enlarge with
      | Some s, Some e ->
        make_ta (guard_of_transition, invariant_of_discrete_state) pta ~scale:s ~enlarge:e ()
      | _ ->
        make_ta (guard_of_transition, invariant_of_discrete_state) pta ()
    ) in
    ta.query <- _convert_query ta pquery;
    ta


end


(*module Uautomaton : (TIMED_AUTOMATON with type Dbm.t = Guard.t 
                                      and type Dbm.Alg.t = Guard.Alg.t) = struct
*)
module Uautomaton  = struct
  module Dbm = Guard
  include GenericUautomaton(Guard)
end



module Ugame = struct
  include Uautomaton

  let is_controllable ta edge =
    true
end

module EnlargedUautomaton = 
struct
  include GenericUautomaton(InfEnlargedDBM)
  module Dbm = InfEnlargedDBM

  let guard_of_transition ta tr = 
    let to_succinct = function
      |InternalTrans(_,e) -> Suc_InternalTrans(e)
      |SyncTrans(_,e1,e2) -> Suc_SyncTrans(e1,e2)
    in
    let str = to_succinct tr in
    try 
      Hashtbl.find ta.guards_tbl str
    with Not_found ->
      (match tr with
       | InternalTrans(state,e) ->
         let g = Dbm.enlarge_guard(_guard_to_dbm ta state.stateVars e.edgeGuard) in
         Hashtbl.add ta.guards_tbl str g;
         g
       | SyncTrans(state,e1,e2) -> 
         let g1 = Dbm.enlarge_guard(_guard_to_dbm ta state.stateVars e1.edgeGuard) in
         let g2 = Dbm.enlarge_guard(_guard_to_dbm ta state.stateVars e2.edgeGuard) in
         Dbm.intersect g1 g2;
         Hashtbl.add ta.guards_tbl str g1;
         g1
      ) 
       |_ as e -> raise e

  let invariant_of_discrete_state ta state = 
    try 
      Hashtbl.find ta.invars_tbl state.stateLocs
    with Not_found ->
      let glob_inv = 
        Array.fold_left (fun acc loc -> loc.locInvar @ acc ) [] state.stateLocs in
      let inv = Dbm.enlarge_guard(_guard_to_dbm ta state.stateVars glob_inv) in
      Hashtbl.add ta.invars_tbl state.stateLocs inv;
      inv
       | _ as e -> raise e

  let transition_fields ta = 
    (function
      | InternalTrans(state,e) as tr ->
        let state' = _copy_state state in
        _apply_edge ta state e state';
        (state, 
         guard_of_transition ta tr,
         e.edgeReset, 
         state')
      | SyncTrans(state,e1,e2) as tr -> 
        let state' = _copy_state state in
        _apply_edge ta state e1 state';       
        _apply_edge ta state e2 state';
        let g1 = guard_of_transition ta tr in
        let g2 = guard_of_transition ta tr in
        Dbm.intersect g1 g2;
        (state, g1, (ClockSet.union e1.edgeReset e2.edgeReset), state')
    )

  let initial_extended_state ta = 
    let dim = (VarContext.size (clocks ta)) in 
    let z = Dbm.create dim in
    (try
       for i = 0 to dim -1 do
         Dbm.constrain z i 0 Dbm.Alg.zero;
         Dbm.constrain z 0 i Dbm.Alg.zero
       done;
       Dbm.posttime z;
       let inv = (invariant_of_discrete_state ta ta.init) in
       Dbm.intersect z inv
     with EmptyDBM -> Log.fatal "The initial state is empty\n"
        | _ as e-> raise e
    );
    (ta.init, z)

  let from_file tafile qfile =
    eprintf "Opening enlarged timed automaton\n";
    let pta  = UtaReader.nta_from_file tafile in
    let query = UtaReader.query_from_file qfile in
    let ta = make_ta (guard_of_transition, invariant_of_discrete_state) pta () in
    ta.query <- (_convert_query ta query);
    ta

end
