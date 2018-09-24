
(** The seach tree stores the tree of exploration, and allows one bidirectional access 
to search paths. Regular edges correspond to actual edges of the timed automaton.
GammaEdges correspond to transitions taken by repeating a cycle; these lead to the fixpoint of
these edges.
The types are generic to allow instantiating the forward algorithm module both for enlarged and exact cases.
In general 'a stands for the zone type (Guard.t or InfEnlargedDBM.t), whereas 't stands for the transition_t
from the GenericTimedAutomaton functor.
*)
type 't search_edge = RegularEdge of 't | GammaEdge of 't list
type ('a,'t) search_node = 
{
  parent : ((('a,'t) search_node) * 't search_edge) option; 
  children : (('a,'t) search_node) Queue.t; 
  label : 'a;
  mutable width_bound : int;
  mutable flag_processed : bool
}

(** A path is a sequence of extended_states and transition_t search_edge *)
type ('a,'t) path = ('a * 't search_edge) list

(** Reachability result is either Unreachable, or Reachable given with the witnessing path *)
type ('a,'t) reachability_result = Unreachable | Reachable of ('a,'t) path

(** Given a printing function for the labels (of type 'a , which stands for extended_states),
and the root of the tree, prints the search tree *)
val print_search_tree : ('a -> unit) -> ('a, 't) search_node -> unit

(** Given functions print_label, print_edge and print_string, and a list of (extended_state * search_edge), prints the path *)
val print_path :
  ('a * 'b -> 'c) ->
  ('d -> unit) -> (string -> 'e) -> (('a * 'b) * 'd search_edge) list -> unit
