open Printf
(* cegar iterations *)
let cegar_nb_iterations = ref 0
let cegar_nb_clock_predicates = ref 0

let print_cegar_stats () =
  Log.info (sprintf "** CEGAR iterations: %d w/ %d clock predicates\n" !cegar_nb_iterations
    !cegar_nb_clock_predicates)
(*  Log.info (sprintf "** CEGAR clock predicates: %d\n" !cegar_nb_clock_predicates)*)
