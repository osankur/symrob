open Batteries
open Printf


let cegar_verbose = ref false
let cegar_print_bdd_stats = ref false
let cegar_verbose_fwd_reach = ref true


type log_t = Info | Debug | Warning | Error | Fatal

let log_level = ref Info
let set_level level =
  (match level with
     Debug ->
     cegar_verbose := true;
     cegar_print_bdd_stats := true;
     cegar_verbose_fwd_reach := true
   | _ -> ()
  );
  log_level := level


let log_err_channel = stderr
let log_regular_channel = stdout 

let logf level s f = 
  (match level with
	| Error ->
		 Printf.fprintf log_err_channel "[ERR] ";
		 Printf.fprintf log_err_channel s f
	| Fatal ->
		 Printf.fprintf log_err_channel "[FAT] ";
		 Printf.fprintf log_err_channel s f;
		 exit(-1)
	| Warning -> 
		 if ( !log_level = Debug || !log_level = Warning ) then
		   (
			 Printf.fprintf log_err_channel "[WAR] ";
			 Printf.fprintf log_err_channel s f
		   )
	| Info ->
		 if ( !log_level = Info || !log_level = Debug || !log_level = Warning ) then
		   (
			 Printf.fprintf log_regular_channel "[INF] ";
			 Printf.fprintf log_regular_channel s f
		   )
	| Debug ->
		 if ( !log_level = Debug ) then
		   (
			 Printf.fprintf log_regular_channel "[DEB] ";
			 Printf.fprintf log_regular_channel s f;
		   )
  );
  flush log_err_channel;
  flush log_regular_channel


let fatal s =
	logf Fatal "%s" s

let info s =
	logf Info "%s" s
let warning s =
	logf Warning "%s" s
let infof f s =
	logf Info f s
let warningf f s =
	logf Warning f s
let fatalf f s =
	logf Fatal f s

let debug s =
	logf Debug "%s" s

let debugf f s =
	logf Debug f s

let log level s =
	logf level "%s" s


module SearchStatistics =
struct
  let counter_visited = ref 0 
  let counter_gamma = ref 0 
  let counter_acceleration = ref 0
  (** Number of iterations of the binary search *)
  let counter_bsiterations = ref 0
  let increment_visited () = incr(counter_visited)
  let increment_gamma () = incr(counter_gamma)
	let increment_acceleration () = incr(counter_acceleration)
  let reset_counters () =
		counter_visited := 0;
		counter_gamma := 0;
		counter_acceleration := 0;
  counter_bsiterations := 0

  let print_statistics chan mode = 
    match mode with 
      Options.ExactReachability
    |Options.RobustReachability ->
      fprintf chan "[INF] Search Statistics:\n";
      fprintf chan "[INF] Visited states: %d\n[INF] Expanded gamma cycles: %d (%d new states)\n" !counter_visited !counter_acceleration !counter_gamma
    | _ ->
      fatal "Cannot print stats: Present algorithm is not search-based"
end
