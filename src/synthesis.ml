open Common
open TimedAutomaton
open Printf
open Pdbm

(** Returns timed automaton where all edges have new distinct synchronized
 * labels {EDGEi}_i*)
let add_distinct_edge_ids ta = 
  let count = ref 0 in
  let nextid () =
    incr(count); (sprintf "EDGE%d" !count)
  in
  let do_transition t = 
    {ta_trans_source = t.ta_trans_source; 
    ta_trans_target =t.ta_trans_target;
    ta_trans_guard = t.ta_trans_guard;
    ta_trans_reset = t.ta_trans_reset;
    ta_trans_labels = (nextid())::t.ta_trans_labels}
  in
  let do_location l = 
    {ta_location_index = l.ta_location_index;
    ta_location_invar = l.ta_location_invar;
    ta_location_proplist = l.ta_location_proplist;
    ta_location_transitions = List.map do_transition l.ta_location_transitions}
  in
  let rec getsynclabels = function
    | i when i > !count -> []
    | i -> (sprintf "EDGE%d" i)::(getsynclabels (i+1))
  in
  let locations = Array.map do_location ta.ta_locations in
  {ta_locations = locations; ta_clocks = ta.ta_clocks; ta_synclabels =
    (getsynclabels 1)}

(** Returns shrink(invar \cap guard \cap unreset_R(zone)) *)
let action_controllable_predecessor ta zone edge = 
  let source = edge.ta_trans_source in
  let target = edge.ta_trans_target in
  let guard = edge.ta_trans_guard in
  let reset = StringSet.fold 
    (fun name is -> IntSet.add (Hashtbl.find ta.ta_clocks.ClockContext.clock2index name) is) 
    edge.ta_trans_reset IntSet.empty in
  let sourceinvar =
    ta.ta_locations.(source).ta_location_invar
  in
  let (l,z) = zone in
  if (l <> target) then
    raise (Failure "Incompatible edge and zone");
  let z1 = ShrunkDBM.copy z in 
  ShrunkDBM.unreset z1 reset;
  ShrunkDBM.intersect_wguard z1 guard;
  ShrunkDBM.intersect_wguard  z1 sourceinvar;
  ShrunkDBM.shrink_updown z1;
  (source,z1)

(** Returns invar \cap guard \cap unreset_R(zone) *)
let action_predecessor ta zone edge = 
  let source = edge.ta_trans_source in
  let target = edge.ta_trans_target in
  let guard = edge.ta_trans_guard in
  let reset = StringSet.fold 
    (fun name is -> IntSet.add (Hashtbl.find ta.ta_clocks.ClockContext.clock2index name) is) 
    edge.ta_trans_reset IntSet.empty in
  let sourceinvar =
    ta.ta_locations.(source).ta_location_invar
  in
  let (l,z) = zone in
  if (l <> target) then
    raise (Failure "Incompatible edge and zone");
  let z1 = Guard.copy z in 
  Guard.unreset z1 reset;
  Guard.intersect z1 guard;
  Guard.intersect z1 sourceinvar;
  (source,z1)

(** Controllable predecessors: the predecessor via given edge but we shrink by
 * before taking the edge. Returns invar \cap pretime(shrink(invar \cap guard \cap unreset(zone)) *)
let controllable_predecessor ta zone edge = 
  let source = edge.ta_trans_source in
  let target = edge.ta_trans_target in
  let guard = edge.ta_trans_guard in
  let reset = StringSet.fold 
    (fun name is -> IntSet.add (Hashtbl.find ta.ta_clocks.ClockContext.clock2index name) is) 
    edge.ta_trans_reset IntSet.empty in
  let sourceinvar =
    ta.ta_locations.(source).ta_location_invar
  in
  let (l,z) = zone in
  if (l <> target) then
    raise (Failure "BackwardReachability.predecessor: incompatible edge and zone");
  let z1 = ShrunkDBM.copy z in 
  ShrunkDBM.unreset z1 reset;
  ShrunkDBM.intersect_wguard z1 guard;
  ShrunkDBM.intersect_wguard z1 sourceinvar;
  ShrunkDBM.shrink_updown z1;
  ShrunkDBM.pretime z1;
  ShrunkDBM.intersect_wguard z1 sourceinvar;
  (source,z1)

(* Construct a straight-line timed automaton describing the given backward path in a timed automaon ta*)
let backward_path_to_ta ta seq = 
  let context = ta.ta_clocks in 
  let current_index = ref 0 in
  let rec path_to_locationlist acc = function
    | (_,None) :: _ :: rest -> failwith "Bad backward path"
    | ((l,z),Some t) :: (((l',z'),t') as next) :: rest ->
      (* In Uppaal, only upper bound invariants are allowed *)
      let dim = Guard.dimension z in
      let invar = Guard.create dim in
      for i = 1 to dim - 1 do
          Guard.constrain invar i 0 z.(i).(0)
      done;
      let (l2,z2) = action_predecessor ta (l',z') t in
      let guard = z2 in
      let trans =
        {ta_trans_source = !current_index; ta_trans_target = !current_index+1;
         ta_trans_guard = guard; ta_trans_labels = t.ta_trans_labels;
         ta_trans_reset = t.ta_trans_reset}
      in 
      let loc = 
       {ta_location_index = !current_index;
        ta_location_invar = invar;
        ta_location_transitions = [trans];
        ta_location_proplist = []};
      in
      incr(current_index);
      path_to_locationlist (loc::acc) (next::rest)
    | [((l,z),_)] -> 
       {ta_location_index = !current_index;
        ta_location_invar = ta.ta_locations.(l).ta_location_invar;
        ta_location_transitions = [];
        ta_location_proplist = []}::acc
    | [] -> acc
   in 
   let nblocs = List.length seq in
   let locations = path_to_locationlist [] seq in
   let locarray = Array.create nblocs (List.hd locations) in
   let _ = List.fold_right (fun loc i -> locarray.(i) <- loc; i+1) locations 0
   in
   {ta_locations = locarray; ta_clocks = context; ta_synclabels = ta.ta_synclabels}

let rec print_backward_path ta = function
  | (_,None) :: _ :: rest -> ()
  | ((l,z),Some t) :: ((l',z'),t') :: rest ->
    printf "When ";
    TimedAutomaton.print_extended_zone stdout ta (l,z);
    printf "\n\tDelay to ";
    let (l2,z2) = action_predecessor ta (l',z') t in
    TimedAutomaton.print_extended_zone stdout ta (l2,z2);
    if (Guard.punctual z2) then
      printf "(punctual)";
    printf "\n\tTake ";
    TimedAutomaton.print_transition stdout ta.TimedAutomaton.ta_clocks t;
    print_backward_path ta (((l',z'),t')::rest)
  | [((l,z),_)] -> ()
  | [] -> ()

let rec print_backward_shrunk_path ta = function
  | (_,None) :: _ :: rest -> ()
  | ((l,z),Some t) :: ((l',z'),t') :: rest ->
    printf "When ";
    TimedAutomaton.print_extended_shrunk_zone stdout ta (l,z);
    printf "\n\tDelay to ";
    let (l2,z2) = action_controllable_predecessor ta (l',z') t in
    TimedAutomaton.print_extended_shrunk_zone stdout ta (l2,z2);
    printf "\n\tTake ";
    TimedAutomaton.print_transition stdout ta.TimedAutomaton.ta_clocks t;
    print_backward_shrunk_path ta (((l',z'),t')::rest)
  | [((l,z),_)] ->()
  | [] -> ()

(** Given an exact backward path, returns a backward path made of controllable
 * predecessors *)
let rec cpre_of_backward_path ta seq = match seq with
  [] -> []
  | [(l,z),None] ->
    [(l,ShrunkDBM.from_guard z),None]
  |[_] -> failwith "Backward path ends with a transition"
  |((l,z),None)::rest -> failwith "Backward path contains None as internal transition"
  |((l,z),Some t):: rest -> 
      let rest = cpre_of_backward_path ta rest in
      let (lnext,znext),_ = List.hd rest in
      let (l,z) = controllable_predecessor ta (lnext,znext) t in
      ((l,z),Some t)::rest

(** Returns a new guard where all constants are multiplied by given constant *)
let rescale_guard factor g = 
  let dim = Guard.dimension g in
  let g' = Guard.create dim in
  for i = 0 to dim - 1 do
    for j = 0 to dim - 1 do
      let (k,ineq) = g.(i).(j) in match k with
      | Infty -> g'.(i).(j) <- (Infty,ineq)
      | Int(k) -> g'.(i).(j) <- (Int(k * factor), ineq)
      (*
      | Infty -> Guard.set_constraint g' i j (Infty,ineq)
      | Int(k) -> Guard.set_constraint g' i j (Int(k * factor), ineq)
      *)
    done
  done;
  Guard.reduce g';
  g'

let rescale_transition factor tra = 
  {ta_trans_source = tra.ta_trans_source; 
   ta_trans_target = tra.ta_trans_target;
   ta_trans_guard = rescale_guard factor tra.ta_trans_guard;
   ta_trans_labels = tra.ta_trans_labels;
   ta_trans_reset = tra.ta_trans_reset}

(** returns a timed autmoaton by multiplying all constants by factor *)
let rescale_timed_automaton ta factor =
  let rescale_location loc = 
       {ta_location_index = loc.ta_location_index;
        ta_location_invar = rescale_guard factor loc.ta_location_invar;
        ta_location_transitions = List.map (rescale_transition factor) loc.ta_location_transitions;
        ta_location_proplist = loc.ta_location_proplist}
  in
  let nblocs = Array.length ta.ta_locations in 
  if (nblocs = 0 ) then failwith "Empty timed automaton";
  let nulocations = Array.create nblocs (ta.ta_locations.(0)) in
  for i = 0 to nblocs - 1 do
    nulocations.(i) <- rescale_location ta.ta_locations.(i)
  done;
  {ta_locations = nulocations; ta_clocks = ta.ta_clocks; ta_synclabels = ta.ta_synclabels}

(** Given a shrunk backward path seq defined on ta (for instance, given by cpre_of_backward_path) 
 * returns an exact backward path by instantiating delta=1, and rescaling by
 * delta0*)
let rescale_backward_shrunk_path ta seq factor =
  let instantiate g factor =
    let dim = ShrunkDBM.dimension g in
    let g' = Guard.create dim in
    for i = 0 to dim - 1 do
      for j = 0 to dim - 1 do
        g'.(i).(j) <- 
          match g.(i).(j) with
          (Infty,_,ineq,_) -> (Infty,ineq)
          |(Int(k),p,ineq,d0) -> (Int(k*factor - p),ineq)
      done
    done; g'
  in
  List.map 
  (function
    | ((l,z),None) -> ((l,instantiate z factor), None)
    | ((l,z),Some t) -> ((l,instantiate z factor), Some (rescale_transition factor t))
  ) seq

(** Classical backwards reachability analysis *)
let solve ta target ~robust:robust ~searchtype:stype = 
  if (robust) then
  (
    printf "[INF] Running robust reachability algorithm\n"; flush stdout
  )
  else
    printf "[INF] Running classical reachability algorithm\n";
  let ta = add_distinct_edge_ids ta in
  match Reachability.backward_search ta "target" robust stype with
  | report, None -> 
      printf "[INF] NOT REACHABLE\n";
      printf "[INF] %d states were visited\n" report;
  | report, Some(seq) -> 
      printf "[INF] REACHABLE in %d steps:\n" (List.length seq);
      printf "[INF] %d states were visited\n" report;
     if (not robust ) then (
       let strategy = backward_path_to_ta ta seq in
       let systemfile = open_out "system.xml" in
       Uppaal.print_uppaal_controlled_system systemfile ta strategy;
       print_backward_path ta seq
     ) else (
       (*** DEBUGGING NEEDED ****)
       let robseq = cpre_of_backward_path ta seq in
       let delta0 = 1 + 
         if (List.length robseq >0) then
          let (_,z),_ = List.hd robseq in
          Num.int_of_num (Num.ceiling_num (Num.div_num (Num.num_of_int 1) (ShrunkDBM.delta_bound z)))
         else 0
       in
       if (List.length robseq > 0 ) then (
         let (_,z),_ = List.hd robseq in 
           printf "[INF] Provided that delta < %s\n" (Num.string_of_num
           (ShrunkDBM.delta_bound z));
           printf "[INF] Provided that delta <= 1/%d\n" delta0 
       );
       let ta = rescale_timed_automaton ta delta0 in
       print_timed_automaton stdout ta;
       let strategy = backward_path_to_ta ta (rescale_backward_shrunk_path ta robseq delta0) in
       let systemfile = open_out "system.xml" in
       Uppaal.print_uppaal_controlled_system systemfile ta strategy;
       print_backward_shrunk_path ta robseq
     )
  
