type mode_t = RobustReachability | ExactReachability | CuddSymbolicCegar

type search_t = Dfs | Bfs

(** The initial abstraction *)
type sym_init =  Sym_init_syntax | Sym_init_complete | Sym_init_empty


let rescaling = ref false
let mode = ref RobustReachability
let search = ref Bfs
let initial_width = ref 10
let width_increment = ref 10
let quantified = ref false
let scale = ref 1
let enlarge = ref 0
let enlarge_precision = ref (Num.num_of_string "1/10")
let gammaGreedyLevel = ref 3 (* 1-3 *)
let sym_init = ref Sym_init_syntax

let bdd_reduce_threshold = 1000
let bdd_reordering = ref Cudd.Man.REORDER_NONE
let bdd_use_restrict = false
