open Batteries
open Common
open TimedAutomaton
open Pdbm
open Printf
open SearchTree
open Uta

module type ZONECONTAINER =
sig
  type ('a,'t) elt = ('a ,'t) search_node option * 't search_edge option * ('a,'t) search_node
  type ('a,'t) t
  val create : unit -> ('a,'t) t
  val pop : ('a,'t) t -> ('a,'t) elt
  val add : ('a,'t) elt -> ('a,'t) t -> unit
  val is_empty : ('a,'t) t -> bool
  val length : ('a,'t) t -> int
end

module ZoneQueue =
struct
  type ('a,'t) elt = ('a,'t) search_node option * 't search_edge option * ('a,'t) search_node
  type ('a,'t) t =  ('a,'t) elt Queue.t
  let create = Queue.create
  let pop = Queue.take
  let add = Queue.add
  let is_empty = Queue.is_empty
  let length = Queue.length
end
module ZoneStack =
struct
  type ('a,'t) elt = ('a,'t) search_node option * 't search_edge option * ('a,'t) search_node
  type ('a,'t) t =  ('a,'t) elt Stack.t
  let create = Stack.create
  let pop = Stack.pop
  let add = Stack.push
  let is_empty = Stack.is_empty
  let length = Stack.length
end

module Reachability (WaitList : ZONECONTAINER) (Model : ENLARGED_TIMED_AUTOMATON) =
struct
  module Dbm = Model.Dbm
  exception RobustTarget of ((Model.discrete_state* Dbm.t), 
                             Model.transition) search_node

  let print_path chan ta = 
    let print_transition chan ta edge =
      let (s,g,r,t) = Model.transition_fields ta edge in 
      fprintf chan "Edge: ";
      Model.print_transition chan ta edge;
      fprintf chan "\n\tWhose guard is: ";
      Dbm.pretty_print chan (Model.clocks ta) g;
      fprintf chan "\n"
    in
    let print_extended_state chan ta state =
      fprintf chan "State: ";
      Model.print_extended_state chan ta state
    in
    SearchTree.print_path (print_extended_state chan ta)
      (print_transition chan ta)
      print_string


  (** A hash table for gamma cycles with a simple interface*)
  module GammaPassedList =
  struct
    type edge_t = Model.transition
    type gamma_node = 
      { 
        mutable gamma_final : bool; 
        gamma_children : (edge_t, gamma_node) Hashtbl.t
      }

    let head =  {gamma_final = false; gamma_children = Hashtbl.create 5};;

    (** Checks if the cycle is in the passed list (returns true), and add its if not (returns false)*)
    let gamma_passed cycle = 
      let rec aux cycle node = match cycle with
        | [] -> if ( node.gamma_final ) then true
          else (
            node.gamma_final <- true; 
            false
          )
        | edge :: lcycle -> 
          (try
             let nnode = Hashtbl.find node.gamma_children edge in
             aux lcycle nnode
           with Not_found ->
             let nnode = {gamma_final=false; gamma_children = Hashtbl.create 5} in
             Hashtbl.add node.gamma_children edge nnode;
             aux lcycle nnode
              |_ as e -> raise e
          )
      in
      aux cycle head
  end 

  (** Successors of state through the given edge. The function returns the result of applying the transition, letting time elapse, and normalizing. *)
  let post ta state edge normalize =
    let (source,guard,reset,target) = Model.transition_fields ta edge in
    let (l,z) = state in
    let z' = Dbm.copy z in
    if (not (Model.is_state_equal ta l source )) then
      Log.fatal "Post: Transition source does not match the state's location";
    Dbm.intersect z' guard;
    Dbm.reset z' reset;
    if (not (Model.is_urgent_or_committed ta target)) then
      Dbm.posttime z';
    Dbm.intersect z' (Model.invariant_of_discrete_state ta target);
    normalize target z';
    (target,z')

  (** The predecessors of state through edge. The function rolls back time (down/pretime operation), and then applies the edge backwards.
      Note that when we intersect pre^*(gamma) with a given state, because the forward exploration always ends with the posttime operation,
      the intersection is non-empty exactly when there is an infinite path through gamma from some valuation of state. *)
  let pre ta state edge =
    let (source,guard,reset,target) = Model.transition_fields ta edge in
    let (l,z) = state in
    let z' = Dbm.copy z in
    if (not (Model.is_state_equal ta l target )) then
      Log.fatal "Pre: Transition target does not match the state's location";
    Dbm.pretime z';
    Dbm.unreset z' reset;
    Dbm.intersect z' guard;
    (source,z')

  (** Computes the post^*(Top) of a given cycle in the enlarged semantics.
      It was shown in Jaubert, Reynier 2011 that this fixpoint computation either terminates
      in N steps, or the fixpoint is empty, where N = number of clocks squared.
      Here, the cycle is given as a list of edges *)
  let post_star ta cycle normalize = 
    let (source,guard,_,_) = Model.transition_fields ta (List.hd cycle) in
    let post state edge = post ta state edge normalize in
    let iterate state = List.fold_left post state cycle in
    let dim = Dbm.dimension guard in
    let maxstep = (dim-1)*(dim-1) in
    let rec fp state step = 
      if (step > maxstep ) then (
      (*
      Log.debug "post_star: maxstep exceeded\n";
       *)
        raise EmptyDBM
      )else(
        let nextstate = iterate state in
        if ( Dbm.quantified_leq (snd state) (snd nextstate) ) then
          state
        else fp nextstate (succ step)
      )
    in
    fp (source,Dbm.create dim) 0


  let pre_star ta cycle = 
    let (source,guard,_,_) = Model.transition_fields ta (List.hd cycle) in
    let rev_cycle = List.rev cycle in
    let dim = Dbm.dimension guard in
    let maxstep = (dim-1)*(dim-1) in
    let rec fp state step = 
      let iterate state = List.fold_left (pre ta) state rev_cycle in
      if (step > maxstep ) then raise EmptyDBM
      else(
        let nextstate = iterate state in
        if ( Dbm.quantified_leq (snd state) (snd nextstate) ) then
          state
        else fp nextstate (succ step)
      )
    in
    (* We apply the fixpoint computation fp on Top *)
    fp (source,Dbm.create dim) 0


  (** Given timed automaton ta, an array of lu bounds indexed by clocks (of type int option * int option, where None means -Inf),
      and array of alpha bounds indexed by clocks (maximal constant appearing in ta for each clock), and a target recognizing function, check for robust reachability *)
  let reach ta  =
    let open Log.SearchStatistics in
    let dim = (VarContext.size (Model.clocks ta)) in
    (** Normalization function: Local LU normalization.
        We prepare the bound arrays that will be reused. *)
    let get_lua_bounds =
      let int_lbounds = Array.make dim 0 in
      let int_ubounds = Array.make dim 0 in
      let lbounds = Array.make dim Model.Dbm.Alg.zero in
      let ubounds = Array.make dim Model.Dbm.Alg.zero in
      let alphabounds = Array.make dim Model.Dbm.Alg.zero in
      fun dstate ->
        Model.lu_bounds ta dstate int_lbounds int_ubounds;
        for i = 0 to dim -1 do
          lbounds.(i) <- Model.Dbm.from_ints int_lbounds.(i) (-1);
          ubounds.(i) <- Model.Dbm.from_ints int_ubounds.(i) 1;
          alphabounds.(i) <- Model.Dbm.Alg.max lbounds.(i) ubounds.(i)
        done;
        (lbounds,ubounds,alphabounds)
    in
    let normalize dstate z =
      let (lbounds,ubounds,_) = get_lua_bounds dstate in
      Dbm.extrapolate_deltalu z lbounds ubounds
    in
    let leq dstate z z' = (*Dbm.leq z z'*)
      let (_,_,alphabounds) = get_lua_bounds dstate in
      Dbm.closure_deltaleq alphabounds z z'
    in
    let passed_list = Hashtbl.create 10000 in
    let passed (l,z) = 
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
        BatDllist.iter 
          (fun z' -> 
             if (leq l z z') then (
               raise Found
             )
          ) q;
        false
      with Not_found -> false | Found -> true | _ as e -> raise e
    in
    (** The wait list *)
    let wait = WaitList.create() in
    (** Process the regular successors of a node *)
    let expand node =
      let (l,z) = node.label in
      let edges = Model.transitions_from ta l in
      (*
      Log.debugf "Expanding state with %d transitions\n" (List.length edges);
      Log.debug "Expanding state: ";
      Model.print_extended_state stdout ta (l,z);
       *)
      List.iter (fun edge ->             
          (try
             let (ln,zn) = post ta (l,z) edge normalize (*(fun a b -> b)*) in
             if (not (Dbm.is_empty zn) && not (is_passed (ln,zn))) then
               (
                 let nnode = 
                   {
                     parent = Some(node,RegularEdge(edge)); 
                     children = Queue.create(); 
                     label=(ln,zn);
                     width_bound = node.width_bound;
                     flag_processed = false
                   } in
                 WaitList.add (Some node,Some(RegularEdge(edge)),nnode) wait;              
               ) else ()
           with EmptyDBM -> (); (* no successor from this edge *)
              | _ as e -> raise e)
        ) edges
    in
    (** Process gamma cycles between two nodes of the search tree *)
    let expand_gamma_cycle first last =
      increment_acceleration ();
      let rec to_list node acc =
        if ( node == (BatDllist.get first) ) then
          acc
        else
          match node.parent with
            None -> Log.fatal "Non-root node of the search tree has no parent"; []
          | Some(parent,RegularEdge(edge)) -> 
            to_list parent (edge::acc)
          | _ -> Log.fatal "The gamma cycle contains a gamma edge"; []
      in
      let cycle = to_list (BatDllist.get last) [] in
      (try 
        (*
                   The gamma passed list can be used if we also take into account
                   the non-emptiness of prestar /\ posttar
          if (GammaPassedList.gamma_passed cycle) then (
            Log.debug "Cycle already accelerated\n";
            raise Found;
          );
         *)
         let (loc,pregamma) = pre_star ta cycle in
         let (l,z) = (BatDllist.get first).label in
         Dbm.intersect pregamma z;
         (* The intersection is not empty, we go on *)
         let (loc,postgamma) = post_star ta  cycle normalize in
         if ( (is_passed (loc,postgamma))) then (
           raise Found;
         );
         increment_gamma();
         (** Add this new node to the search tree *)
         let parent_node = (Dllist.get first) in
         let newnode = {
           parent = Some(parent_node,GammaEdge(cycle));
           children = Queue.create(); 
           label = (loc,postgamma);
           width_bound = parent_node.width_bound;
           flag_processed = true
         }
         in
         Queue.add newnode (Dllist.get first).children;
         if (not (passed newnode.label)) then (
           expand newnode
         );
         true
       with EmptyDBM -> 
         false
          | Found -> 
            false
          | _ as e-> raise e
      )
    in
    (** Find all gamma cycles from the root to given node that have not been processed yet,
        and process them. *)
    let process_prefix_for_cycles node =    
      let accelerate_all_factors first last =
        (* we will enumerate all factors of length len, and increment len *)
        let len = ref 1 in
        let gamma_added = ref false in
        (try
           while true do
             let p = ref first in
             let q = ref first in
             for i = 0 to (!len - 1)  do
               q := BatDllist.next !q;
               if (!q == first ) then
                 raise Not_found
             done;
             while (not (!q == first) ) do
               let success = expand_gamma_cycle !p !q in
               gamma_added := !gamma_added || success;
               p := BatDllist.next !p;
               q := BatDllist.next !q
             done;
             incr(len)
           done
         with Not_found -> () (* No factor of length len *)
        );
        !gamma_added
      in
      let same_exact_state = match !Options.gammaGreedyLevel with
          1 | 2 -> fun s t -> Model.is_state_equal ta (fst s) (fst t)
        | _ -> fun s t -> 
	  (Model.is_state_equal ta (fst s) (fst t))
	  &&
	  (Dbm.equal_non_enlarged_zones (snd s) (snd t))
      in
      (** Returns a BatDllist of all states in the prefix with the same_exact_state as the given node *)
      let get_list_of_occurrences node = 
        let listhd = ref (BatDllist.create node) in
        let rec add_endpoints curnode = 
          match curnode with
          |Some(pnode,RegularEdge(_)) -> 
            if (same_exact_state pnode.label node.label) then
              listhd := BatDllist.prepend !listhd pnode;
            add_endpoints pnode.parent
          |_-> ()
        in 
        add_endpoints node.parent;
        listhd
      in
      let processedDiscStates = Hashtbl.create 100 in
      let success = ref false in
      let rec chooseDiscStates node = 
        if ( not (Hashtbl.mem processedDiscStates (fst node.label)) ) then (
          let listhd = get_list_of_occurrences node in
          success := !success || (accelerate_all_factors !listhd (BatDllist.prev !listhd));
          Hashtbl.add processedDiscStates (fst node.label) true;
        );
        if (!Options.gammaGreedyLevel >= 3 ) then (
          !success
        ) else 
          match node.parent with
          |Some(pnode,RegularEdge(_)) -> chooseDiscStates pnode
          |_ -> !success
      in
      chooseDiscStates node
    in
    (** Algorithm's parameters *)
    let (linit,zinit) = Model.initial_extended_state ta in
    normalize linit zinit;
    let search_root = 
      {
        parent = None; 
        children = Queue.create(); 
        label = (linit,zinit);
        width_bound = !Options.initial_width;
        flag_processed = false
      }
    in
    (** Main loop of the algorithm *)
    try        
      WaitList.add (None,None,search_root) wait;
      while not (WaitList.is_empty wait) do
        let parent,edge,node = WaitList.pop wait in
        let (l,z) = node.label in
        if (Model.is_target ta l) then (
          printf "\n";
          raise (RobustTarget node);
        );
        if ( !counter_visited  mod 1000 = 0 ) then
          (
            Log.debug (sprintf "Visited %d states, Passed Gamma-Fixpoints: %d/%d\r" !counter_visited !counter_gamma !counter_acceleration);

            flush stdout
          );
        (* Adding to the search tree - passed list *)
        (match parent,edge with
           None,_ -> () (* This is the root of the search *)
         |Some(parent), Some(edge) -> 
           Queue.add node parent.children
         | _ -> Log.fatal "Bad search tree: Non-root node has no parent\n"
        );

        if (not (passed node.label)) then (
          if ( Dbm.width z > node.width_bound ) then
            (
              Log.debugf "Width exceeded %d                                    \r" node.width_bound;
              if not (process_prefix_for_cycles node) then 
                node.width_bound <- node.width_bound + !Options.width_increment;
            );
          expand node
        );
        increment_visited()
      done;
      Unreachable
    with RobustTarget(targetnode) ->
      let rec to_list node = match node.parent with
        | Some(pnode,edge) ->
          (pnode.label,edge) :: to_list pnode
        | None -> []
      in
      Reachable (List.rev (to_list targetnode))
end

module Dfs = Reachability(ZoneStack)(EnlargedUautomaton)
module Bfs = Reachability(ZoneQueue)(EnlargedUautomaton)
