open Printf
open Str
open Unix
open Num
open Pervasives

let usage () = 
  printf 
"symrob 0.1 r2167 
binary search script

Usage: binarySearch [options] <system> [query]

Options:
  --initial-enlarge N\t\tInitial enlargement value with N rational (i.e. in the form p/q).
  --enlarge-precision N\t\tStopping precision for the binary search

"


let symrob = "symrob --enlarged"
let infinitesimal = ref false

let total_visits = ref 0
let counter_bsiterations = ref 0
let enlarge_precision = ref (num_of_string "1/20")
let initial_enlarge = ref (num_of_string "8")


let search basecommand = 
  (** Returns pair (if reachable,nb visited states) *)
  let reachable nu =
	let r = Num.ratio_of_num nu in
	let num,denom = (Big_int.int_of_big_int (Ratio.numerator_ratio r)),
					(Big_int.int_of_big_int (Ratio.denominator_ratio r))
	in
	let command = sprintf "%s --scale %d --enlarge %d" basecommand denom num in
	let reachable = ref None in
	let visited = ref 0 in
	let pat_visited = "[INF] Visited states: " in
	(*
	let pat_visited = Str.regexp "[INF] Visited states: \\([0-9]*\\)[^0-9]*" in
	 *)
	let check_output line = 
	  if ( Batteries.String.exists line "[INF] VERDICT: SAFE" ) then(
		reachable := Some(false)
	  ) else if ( Batteries.String.exists line "[INF] VERDICT: REACHABLE" ) then (
		reachable := Some(true)
	  )
	  else if (Batteries.String.exists line pat_visited) then (
		visited := int_of_string (Batteries.String.tail line (String.length pat_visited))
	  )
	in
	printf "Running program <%s>\n" command;
	flush stdout;
	(*
	let in_channel, out_channel, err_channel  = Unix.open_process_full command [||] in
	 *)
	let in_channel  = Unix.open_process_in command in
	begin
      try
		while true do
		  let line = input_line in_channel in
		  (*printf "Read: <%s>\n" line;*)
          check_output line;
		done;
      with End_of_file ->
		ignore(Unix.close_process_in in_channel)
		(*
		ignore (Unix.close_process_full (in_channel, out_channel, err_channel))
		 *)
	end;
	let b = (match !reachable with
			 |None -> fprintf stderr "Symrob quit unexpectedly\n"; exit(-1)
			 |Some(b) -> b
			)
	in
	(b, !visited)
  in
  (** Lower bound for the binary search: !nu is in [!lowerbound, !initial_enlarge] *)
  let lowerbound = ref (num_of_string "0") in
  let upperbound = ref !initial_enlarge in
  let nu = ref (!initial_enlarge) in 
  let final_verdict = ref None in
  let prev = ref (!nu) in
  let total_visits = ref 0 in
  let stop  =  ref false in
  let open Num in 
  let open Pervasives in 
  while ( not !stop ) do
	let (verdict,visit) = reachable !nu in
	prev := !nu;
	(** If system is safe, then set the search lowerbound to current nu *)
	if ( not verdict ) then(
	  lowerbound := !nu;
	  final_verdict := Some(false, !nu);
	) else (
	  upperbound := !nu;
	);
	nu := (!lowerbound +/ !upperbound) // (Num.num_of_int 2);
	total_visits := !total_visits + visit; 	
	stop := (!infinitesimal && (not verdict)) ||
			  (!upperbound -/ !lowerbound) <=/ !enlarge_precision;
	incr(counter_bsiterations);
	printf "Target reachable: %b (%d states visited)\n" verdict visit;
	flush stdout;
  done;
  (match !final_verdict with
  |None ->
	Log.info "Verdict: INCONCLUSIVE\n";
	Log.infof "REACHABLE for all delta >= %s\n" (string_of_num !prev);
	Log.info (sprintf "After %d refinements\n" !counter_bsiterations)
  |Some(_,delta) ->
	Log.infof "Verdict: SAFE for delta = %s\n" (string_of_num delta);	
	Log.infof "Safety reached after %d refinements\n" !counter_bsiterations;
  );
  printf "Total Visited States: %d\n" !total_visits

let main =
  let input = Queue.create () in
  let i = ref 1 in
  let args = Sys.argv in
  let nargs = Array.length args in
  while (!i < nargs) do	
	if ( args.(!i) = "--initial-enlarge" ) then (
	  if ( !i+1 < nargs ) then(
		incr(i);
		initial_enlarge := num_of_string args.(!i)
	  ) else (
		usage();
		fprintf stderr "[ERR] Argument missing after %s\n" args.(!i);
		exit(-1);
	  )
	) else if ( args.(!i) = "--enlarge-precision" ) then (
	  if ( !i+1 < nargs ) then(
		incr(i);
		enlarge_precision := num_of_string args.(!i)
	  ) else (
		usage();
		fprintf stderr "[ERR] Argument missing after %s\n" args.(!i);
		exit(-1);
	  )
	) else if ( args.(!i) = "--infinitesimal" ) then(
	  infinitesimal := true
	) else (
	  Queue.add args.(!i) input
	);
	incr(i);
  done;
  if ( Queue.length input <= 0 ) then(
	usage();
	exit(-1);
  );
  let command_buf = Buffer.create 128 in
  Buffer.add_string command_buf symrob;
  Queue.iter (fun arg -> Buffer.add_string command_buf (" "^arg)) input;
  search (Buffer.contents command_buf)

