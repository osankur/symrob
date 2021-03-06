open Pdbm
open Common
open TimedAutomaton
open RobustReach
open ExactReach
open Batteries
open Printf
open Uta
open Cudd

let test () =
  let tafile = "examples/nonrobust.xml" in
  let qfile = "examples/nonrobust.q" in
  Log.info "Running Uautomaton-based reachability\n";
  let ta = Uautomaton.from_file tafile qfile () in
  Log.infof "Read TA with %d clocks\n" (VarContext.size (Uautomaton.clocks ta ));
  let module Search = ExactReach.Bfs in
  (match Search.reach ta with
   | SearchTree.Unreachable ->
     Log.info "\nVERDICT: SAFE\n";
     Log.SearchStatistics.print_statistics stdout !Options.mode;
   | SearchTree.Reachable(path) ->
     Search.print_path stdout ta path;
     Log.info "\nVERDICT: REACHABLE\n";
     Log.SearchStatistics.print_statistics stdout !Options.mode
  );
  let _ = Cudd.Bdd.nor in
  exit 0

let usage () =
  printf
    "Symbolic CEGAR Algorithm for checking safety of timed automata
Usage: abs-symbolic -c model.xml query.q
"

let execute tafile qfile =
  Log.info (sprintf "Reading timed automaton %s and query %s\n" tafile qfile); flush stdout;
  match !Options.mode with
  | Options.RobustReachability ->
    let eta = EnlargedUautomaton.from_file tafile qfile in
    Log.infof "Running robust reachability (Greedy level: %d)\n" !Options.gammaGreedyLevel;
    Log.infof "Read TA with %d clocks\n" (VarContext.size (EnlargedUautomaton.clocks eta));
    let reach = match !Options.search with
      | Options.Dfs -> RobustReach.Dfs.reach
      | Options.Bfs -> RobustReach.Bfs.reach
    in
    (match reach eta with
     | SearchTree.Unreachable ->
       Log.infof "\nVERDICT: SAFE for delta < %s\n" (Num.string_of_num !InfEnlargedDBMAlgebra.largest_delta0);
       Log.SearchStatistics.print_statistics stdout !Options.mode;
     | SearchTree.Reachable(path) ->
       RobustReach.Bfs.print_path stdout eta path;
       Log.info "\nVERDICT: REACHABLE\n";
       Log.SearchStatistics.print_statistics stdout !Options.mode
    )
  | Options.ExactReachability ->
    Log.info "Running Uautomaton-based reachability\n";
    let ta = Uautomaton.from_file tafile qfile () in
    Log.infof "Read TA with %d clocks\n" (VarContext.size (Uautomaton.clocks ta));
    let reach = (match !Options.search with
        | Options.Dfs -> ExactReach.Dfs.reach
        | Options.Bfs -> ExactReach.Bfs.reach
      )
    in
    (match reach ta with
     | SearchTree.Unreachable ->
       Log.info "VERDICT: SAFE\n";
       Log.SearchStatistics.print_statistics stdout !Options.mode;
     | SearchTree.Reachable(path) ->
       ExactReach.Dfs.print_path stdout ta path;
       Log.info "VERDICT: REACHABLE\n";
       Log.SearchStatistics.print_statistics stdout !Options.mode
    )
  | Options.CuddSymbolicCegar ->
    Log.info "Running Cudd Cegar algorithm...\n";
    let ta = Uautomaton.from_file tafile qfile () in
    Log.infof "Read TA with %d clocks\n" (VarContext.size (Uautomaton.clocks ta));
    (*Log.info (sprintf "Result: %s\n" (CuddCegar.reach ta))*)
    (printf "Result: %s\n" (CuddCegar.reach ta))

let main () =
  let isfile name =
    (String.exists name ".xml") ||  (String.exists name ".q" )
  in
  let args = Array.sub Sys.argv 1 ((Array.length Sys.argv)-1) in
  let options_args = Array.filter (fun s -> not (isfile s)) args in
  let file_args = Array.filter isfile args in
  let prev = ref "" in
  for i = 0 to (Array.length options_args) - 1 do
    match options_args.(i) with
    | "--silent" -> Log.set_level Log.Silent
    | "--test" -> test()
    | "--dfs" -> Options.search := Options.Dfs
    | "--bfs" -> Options.search := Options.Bfs
    | "--enlarged" ->
      Options.mode := Options.ExactReachability;
      Options.rescaling := true
    | "--debug" -> Log.set_level Log.Debug
    | "--greedy1" -> Options.gammaGreedyLevel := 1
    | "--greedy2" -> Options.gammaGreedyLevel := 2
    | "--greedy3" -> Options.gammaGreedyLevel := 3
    | "--scale" | "--enlarge" ->
      Options.mode := Options.ExactReachability;
      Options.rescaling := true;
      prev := options_args.(i)
    | "--initial-width"
    | "--enlarge-precision" -> prev := options_args.(i)
    | "--sym-init-empty" ->
      Options.sym_init := Options.Sym_init_empty;
      Log.warning "CEGAR refinement procedure is not complete under empty init refinement"
    | "--bdd-reordering-sift" ->
      Options.bdd_reordering := Cudd.Man.REORDER_SIFT
    | "--bdd-reordering-random" ->
      Options.bdd_reordering := Cudd.Man.REORDER_RANDOM
    | other ->
      if ( other.[0] = '-' ) then
        (String.iter (function
             | '-' -> ()
             | 'q' -> Options.quantified := true
             | 'e' -> Options.mode := Options.ExactReachability
             | 'r' -> Options.mode := Options.RobustReachability
             | 'c' -> Options.mode := Options.CuddSymbolicCegar
             | c ->
               Log.warningf "Unrecognized option: %c\n" c
           ) other
        )
      else(
        try
          (match !prev with
             "--scale" -> Options.scale := int_of_string other
           | "--enlarge" -> Options.enlarge := int_of_string other
           | "--initial-width" -> Options.initial_width := int_of_string other
           | "--enlarge-precision" -> Options.enlarge_precision := Num.num_of_string other
           | _ as s -> usage(); Log.fatalf "Command line parsing problem: %s\n" s
          );
          prev := ""
        with _ -> Log.fatalf "Number expected instead of \"%s\"" other
      )
  done;
  (** Detect file type *)
  let tafile = ref "" in
  let qfile = ref "" in
  Array.iter (fun filename ->
      if ( String.ends_with filename ".xml" ) then
        (
          tafile := filename;
        )
      else if (String.ends_with filename ".q") then
        (
          qfile := filename;
        )
      else
        (
          Log.fatalf "File extension not recognized: %s\n" filename
        )
    ) file_args ;
  if ( !tafile = "" ) then
    (
      usage();
      Log.fatal "No input files\n"
    );
  if ( !qfile = "" ) then
    (
      qfile := (Filename.chop_suffix !tafile ".xml") ^ ".q";
      Log.warningf "Guessing query file: %s\n" !qfile
    );
  execute !tafile !qfile

let _ = main ()

