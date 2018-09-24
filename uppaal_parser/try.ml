(* http://www.ffconsultancy.com/ocaml/benefits/parsing.html 
 On Genlex
 *)
open Printf;;
open Uta;;

let lexbuf = 
	Lexing.from_string (read_line()) in
		let g = GuardParser.declaration GuardLexer.token lexbuf in
		let clocks, ints, chans = g in
		printf "Global clocks: ";
		List.iter (fun name -> printf "%s " name) clocks;
		printf "\nGlobal discrete variables: ";
		List.iter (fun (name,v) -> printf "(%s,%d) " name v) ints;
		printf "\nChannels: ";
		List.iter (fun name -> printf "%s " name) chans;
		printf "\n"
