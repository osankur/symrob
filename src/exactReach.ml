open Batteries
open RobustReach
open TimedAutomaton
open Pdbm
open Common
open SearchTree
open Printf
open Uta

module ExactReachability (WaitList : ZONECONTAINER) (Model : TIMED_AUTOMATON) =
struct
  module Dbm = Model.Dbm
  module Model = Model
  exception ExactTarget of ((Model.discrete_state * Dbm.t), Model.transition) search_node

  module DSSet = Set.Make(struct type t = Model.discrete_state let compare = compare end)

  let print_path chan ta = 
    let print_transition chan ta edge =
      let (s,g,r,t) = Model.transition_fields ta edge in 
      Model.print_transition chan ta edge;
      fprintf chan "\nGuard: ";
      Dbm.pretty_print chan (Model.clocks ta) g
    in
    SearchTree.print_path (Model.print_extended_state chan ta)
      (print_transition chan ta)
      print_string

  let post ta state edge normalize =
    let (s,g,r,t) = Model.transition_fields ta edge in
    let (l,z) = state in
    let z' = Dbm.copy z in
    if (not (Model.is_state_equal ta l s) ) then
      Log.fatal "Post: Transition source does not match the state's location";
    Dbm.intersect z' g;
    Dbm.reset z' r;
    if (not (Model.is_urgent_or_committed ta t)) then
      Dbm.posttime z';
    Dbm.intersect z' (Model.invariant_of_discrete_state ta t);
    normalize t z';	
    (t,z')


  let reach ta  =
    let open Log.SearchStatistics in
    let passed_list = Hashtbl.create 10000 in
    let passed_ds = ref DSSet.empty in
    let dim = (VarContext.size (Model.clocks ta)) + 1 in
    (** Normalization function: Local LU normalization *)
    let get_lua_bounds = 
      let int_lbounds = Array.make dim 0 in
      let int_ubounds = Array.make dim 0 in
      let int_alphabounds = 
	Array.make dim 0 in
      fun dstate -> 
	Model.lu_bounds ta dstate int_lbounds int_ubounds;
	for i = 0 to dim - 1 do
	  int_alphabounds.(i) <- max int_lbounds.(i) int_ubounds.(i)
        done;
        (int_lbounds,int_ubounds,int_alphabounds)
    in
    let normalize dstate z =
      let (lbounds,ubounds,_) = get_lua_bounds dstate in
      Dbm.extrapolate_lu z lbounds ubounds
    in
    let leq dstate z z' = 
      let (_,_,alphabounds) = get_lua_bounds dstate in
      Dbm.closure_leq alphabounds z z'
    in
    let passed (l,z) = 
      passed_ds := DSSet.add l !passed_ds;
      (try 
	 let q = Hashtbl.find passed_list l in
	 let alreadyPut = ref false in
	 let dummy = BatDllist.prepend q (BatDllist.get q) in
	 let cur = ref q in
	 (* Here we prepend a dummy node before q (head),
	    and loop on the list until we hit dummy *)
	 while ( not (!cur == dummy) ) do
	   let z' = BatDllist.get !cur in 
	   if (leq l z z') then (
	     ignore(BatDllist.drop dummy);
	     raise Found
	   )
	   else if (leq l z' z) then
	     (
	       if (not !alreadyPut) then (
		 alreadyPut := true;
		 let newnode = BatDllist.append !cur z in
		 (* update the list head known by the hash table *)
		 if ( q == !cur ) then(
		   Hashtbl.add passed_list l newnode
		 );
		 ignore(BatDllist.drop !cur);
		 cur := BatDllist.next newnode;
	       ) else (
		 if ( q == !cur ) then(
		   let nextcur = BatDllist.next !cur in
		   Hashtbl.add passed_list l nextcur
		 );
		 cur := BatDllist.drop !cur;
	       );
	     )
	   else 
	     cur := BatDllist.next !cur
	 done;
	 ignore(BatDllist.drop dummy);
	 if (!alreadyPut) then(
	 ) else (
	   ignore(BatDllist.append q z)
	 );
	 false
       with Not_found -> 
	 let q = BatDllist.create z in 
	 Hashtbl.add passed_list l q;
	 false
	  | Found ->
	    true
      )
    in
    let is_passed (l,z) = 
      try
	let q = Hashtbl.find passed_list l in
	BatDllist.iter (fun z' -> 
	    if (leq l z z') then raise Found)	q;
	false
      with Not_found -> false | Found -> true | _ as e -> raise e
    in
    let wait = WaitList.create() in
    let (linit,zinit) = Model.initial_extended_state ta in
    normalize linit zinit;
    let search_root = 
      {
	parent = None; 
	children = Queue.create(); 
	label = (linit,zinit);
	width_bound = 0;
	flag_processed = false;
      }
    in
    let expand node =
      let (l,z) = node.label in
      let edges = Model.transitions_from ta l in
      List.iter (fun edge ->
	  (try
	     let (ln,zn) = post ta (l,z) edge normalize in
	     if ( not (is_passed (ln,zn))) then
	       (
		 let nnode = 
		   {parent = Some(node,RegularEdge(edge)); 
		    children = Queue.create(); 
		    label=(ln,zn);
		    width_bound = 0;
		    flag_processed = false
		   } in
		 WaitList.add (Some node,Some(RegularEdge(edge)),nnode) wait
	       )
	   with EmptyDBM -> () (* no successor from this edge *)

	      | _ as e -> raise e)
	) edges
    in
    (** MAIN LOOP OF THE ALGORITHM *)
    try
      WaitList.add (None,None,search_root) wait;
      while not (WaitList.is_empty wait) do
	let parent,edge,node = WaitList.pop wait in
	let (l,z) = node.label in
	if ( !counter_visited mod 1000 = 0 ) then
	  (
	    Log.debugf "Visited %d states\r" !counter_visited;
	    flush stdout
	  );
	(match parent,edge with
	   None,_ -> () (* This is the root of the search *)
	 |Some(parent), Some(edge) -> 
	   Queue.add node parent.children
	 | _ -> Log.fatal "Bad search tree: Non-root node has no parent\n"
	);
	if (Model.is_target ta l) then (
	  printf "\n";
	  raise (ExactTarget node);
	);
	if (not (passed node.label)) then (
	  expand node
	);
	increment_visited();
      done;
      printf "\nVisited %d locations\n" (DSSet.cardinal !passed_ds);
      Unreachable
    with ExactTarget(targetnode) ->
      let rec to_list node = match node.parent with
	| Some(pnode,edge) ->
	  (pnode.label,edge) :: to_list pnode
	| None -> []
      in
      Reachable (List.rev (to_list targetnode))
end

module Dfs = ExactReachability(ZoneStack)(Uautomaton)
module Bfs = ExactReachability(ZoneQueue)(Uautomaton)
