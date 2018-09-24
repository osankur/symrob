open Batteries
open Printf

type 't search_edge = RegularEdge of 't | GammaEdge of 't list
type ('a,'t) search_node = 
{
  parent : ((('a,'t) search_node) * 't search_edge) option; 
  children : (('a,'t) search_node) Queue.t; 
  label : 'a;
  mutable width_bound : int;
  mutable flag_processed : bool
}
type ('a,'t) path = ('a * 't search_edge) list
type ('a,'t) reachability_result = Unreachable | Reachable of ('a,'t) path

let print_search_tree print_label node =
  let rec aux level node =
	(0--level) |> Enum.iter (fun i -> printf " ");
	print_label node.label;
	Queue.iter (aux (succ level)) node.children
  in
  aux 0 node

  let rec print_path print_label print_edge print_string path =
		match path with 
		|[]->()
		| ((l,z),RegularEdge(edge)) :: rest ->
			 print_label (l,z);
			 print_string "\n";
			 print_edge edge;
			 print_string "\n";

			 print_path print_label print_edge print_string rest
		| ((l,z),GammaEdge(edges)) :: rest -> 
			 print_label (l,z);
			 print_string "\n";
			 print_string "Gamma-Cycle:\n";
			 List.iter 
				 (fun edge -> print_string "\t"; 
											print_edge edge) edges;
			 print_string "\n";
			 print_path print_label print_edge print_string rest

