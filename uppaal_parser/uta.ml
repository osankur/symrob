open Batteries
open Printf
exception Var_already_defined
exception Var_undefined of string

module VarContext =
struct
  type 'a t = {
    index2var : (int,'a) Hashtbl.t;
    var2index : ('a,int) Hashtbl.t;
    index2range : (int,(int*int)) Hashtbl.t;
    mutable nextVarIndex : int;
  }
  let create () =
    {
      var2index = Hashtbl.create 100;
      index2var = Hashtbl.create 100;
      index2range = Hashtbl.create 100;
      nextVarIndex = 0;
    }
  let get_var2index vc = 
    vc.var2index

  let index_of_var vc var =
    Hashtbl.find vc.var2index var

  let range_of_index vc index = 
    if Hashtbl.mem vc.index2range index then 
      Some(Hashtbl.find vc.index2range index)
    else None

  (*
  let print_ranges vc =
    Hashtbl.iter (fun vi (l,r) ->
        printf "%d : (%d,%d)\n" vi l r
      ) vc.index2range
     *)

  let var_of_index vc index = 
    try
      Hashtbl.find vc.index2var index
    with
    | Not_found ->
      eprintf "No var with index %d\n Size: %d\n" index (Hashtbl.length vc.index2var);
      Hashtbl.iter (fun index var ->
	  eprintf "CLOCK: %d %s\n" index var) vc.index2var;
      flush stderr;
      raise Not_found
    | _ as e -> raise e

  let index2var = var_of_index
  let var2index = index_of_var
  let mem vc var = 
    Hashtbl.mem vc.var2index var

  let add vc ?id ?range var  =
    let register_range i = function
      | None -> ()
      | Some(range) ->
        Hashtbl.add vc.index2range i range
    in
    if ( mem vc var ) then 
      raise (Var_already_defined );
    match id with
      None ->
      let index = vc.nextVarIndex in
      vc.nextVarIndex <- vc.nextVarIndex + 1;
      Hashtbl.add vc.index2var index var;
      Hashtbl.add vc.var2index var index;
      register_range index range
    | Some id ->
      Hashtbl.add vc.index2var id var;
      Hashtbl.add vc.var2index var id;
      register_range id range


  let size vc = 
    Hashtbl.length vc.index2var
  let iter f vc = 
    Hashtbl.iter f vc.var2index 
end

type expression = 
    Constant of int
  | Variable of string
  | Sum of expression * expression
  | Product of expression * expression
  | Subtraction of expression * expression
  | Division of expression * expression
  | BoolNot of expression
  | BoolNeq of expression * expression
  | BoolEq of expression * expression
  | BoolAnd of expression * expression

(*
type bool_expression =
  | BoolAtomic of expression
  | BoolNot of bool_expression
  | BoolNeq of bool_expression * bool_expression
  | BoolEq of bool_expression * bool_expression
  | BoolAnd of bool_expression * bool_expression
*)
type atomic_guard =
    GuardLeq of expression * expression
  | GuardLess of expression * expression
  | GuardGeq of expression * expression
  | GuardGreater of expression * expression
  | GuardEqual of expression * expression
  | GuardNeq of expression * expression

type range = int *int 
(** Variable name and initial value *)
type variable = Var of (string * int * range) | ConstVar of (string*int)

let name_of_var = function
  |Var(name,init,range) -> name
  |ConstVar(name,init) -> name

(** a declaration is: Clock list, variable list, channel list *)
type temp_declaration = (string list) * (variable list) * (string list)
type guard = atomic_guard list
type update = (string * expression) list
type position = int * int

type location = {
  mutable locId : string;
  mutable locPos : position;
  mutable locName : string;
  mutable locNamePos : position;
  mutable locInvar : guard;
  mutable locInvarPos : position;
  mutable locCommitted : bool;
  mutable locUrgent : bool;
}

type chan = 
    SendChan of string 
  | RecvChan of string

type edge = 
  {
    mutable edgeSource : string;
    mutable edgeGuard : guard;
    mutable edgeGuardPos : position;
    mutable edgeSync : chan option;
    mutable edgeSyncPos : position;
    mutable edgeUpdates : update;
    mutable edgeUpdatesPos : position;
    mutable edgeTarget : string;
    mutable edgeNails : position list;
  }

type template = {
  tempName : string; 
  tempLocations : location list;
  tempInitialLocation : location;
  tempEdges : edge list;
  tempClocks : string list;
  tempVars : variable list;
}

type prop_query = AndQuery of prop_query * prop_query
		| OrQuery of prop_query * prop_query
		| NotQuery of prop_query
		| AtomicQuery of string * string

type query = ReachQuery of prop_query
	   | EmptyQuery

type system = {
  sysTemplates : template list;
  (** list of process names and their template types *)
  sysProcessInstances : (string * string) list;
  sysVars : variable list;
  sysClocks : string list;
  sysChans : string list;
  sysQuery : query
}

let nb_clocks sys =
  List.length sys.sysClocks


let string_of_query q = 
  let rec string_of_prop_query = function
    | AtomicQuery(p,l) -> p^"."^l
    | NotQuery(pq) -> sprintf "(not %s)" (string_of_prop_query pq)
    | OrQuery(p1,p2) -> sprintf "(%s or %s)"
			  (string_of_prop_query p1)
     (string_of_prop_query p2)
    | AndQuery(p1,p2) -> sprintf "(%s and %s)"
			   (string_of_prop_query p1)
      (string_of_prop_query p2)
  in
  match q with
  | ReachQuery(pq) -> "E<> " ^ (string_of_prop_query pq)
  | EmptyQuery -> "No query"

let rec string_of_exp = function
  | Constant c -> sprintf "%d" c
  (*	| VariableID(id) -> sprintf "Var(%d)" id*)
  | Variable id -> id
  | Product(e1,e2) ->
    sprintf "%s * %s" (string_of_exp e1)
      (string_of_exp e2)
  | Sum(e1,e2) ->
    sprintf "(%s + %s)" (string_of_exp e1)
      (string_of_exp e2)
  | Division(e1,e2) ->
    sprintf "%s / %s" (string_of_exp e1)
      (string_of_exp e2)
  | Subtraction(e1,e2) ->
    sprintf "(%s - %s)" (string_of_exp e1)
      (string_of_exp e2)
  | _ -> failwith "not implemented"
(*
let rec string_of_bool_exp = function
  | BoolAtomic(e) -> string_of_exp e
  | BoolNeq(e1,e2) ->
    sprintf "(%s != %s)" (string_of_bool_exp e1) (string_of_bool_exp e2)
  | BoolEq(e1,e2) ->
    sprintf "(%s == %s)" (string_of_bool_exp e1) (string_of_bool_exp e2)
  | BoolNot(e) ->
    sprintf "!%s" (string_of_bool_exp e)
  | BoolAnd(e1,e2) ->
    sprintf "(%s && %s)" (string_of_bool_exp e1) (string_of_bool_exp e2)
*)

let rec string_of_atomic_guard = function
  |  GuardLeq(v,exp) ->
    sprintf "%s <= %s" (string_of_exp v)(string_of_exp exp)
  | GuardLess(v,exp) ->
    sprintf "%s < %s" (string_of_exp v)(string_of_exp exp)
  | GuardGeq(v,exp)->
    sprintf "%s >= %s" (string_of_exp v)(string_of_exp exp)
  | GuardGreater(v,exp)->
    sprintf "%s > %s" (string_of_exp v) (string_of_exp exp)
  | GuardEqual(v,exp)->
    sprintf "(%s == %s)" (string_of_exp v) (string_of_exp exp)
  | GuardNeq(v,exp)->
    sprintf "(%s != %s)" (string_of_exp v) (string_of_exp exp)


let xml_string_of_atomic_guard = function
  |  GuardLeq(v,exp) ->
    sprintf "%s &lt;= %s" (string_of_exp v)(string_of_exp exp)
  | GuardLess(v,exp) ->
    sprintf "%s &lt; %s" (string_of_exp v)(string_of_exp exp)
  | GuardGeq(v,exp)->
    sprintf "%s &gt;= %s" (string_of_exp v)(string_of_exp exp)
  | GuardGreater(v,exp)->
    sprintf "%s &gt; %s" (string_of_exp v) (string_of_exp exp)
  | GuardEqual(v,exp)->
    sprintf "%s == %s" (string_of_exp v) (string_of_exp exp)
  | _ -> failwith "not implemented"


let rec string_of_guard  = function
  | [] -> ""
  | [x] -> string_of_atomic_guard x
  | x :: y :: l -> 
    ((string_of_atomic_guard x) ^ " && ")
    ^ (string_of_guard  (y::l))

let rec xml_string_of_guard  = function
  | [] -> ""
  | [x] -> xml_string_of_atomic_guard x
  | x :: y :: l ->
    ((xml_string_of_atomic_guard x) ^ " &amp;&amp; ")
    ^ (xml_string_of_guard  (y::l))

(** TODO Modeles de circuits avec longues expressions : explosion de complexite possibles.
    Reecrire avec des ensembles ou hashtbl
 *)
let rec vars_of_exp = function
  | Constant c -> []
  | Variable id -> [id]
  | Product(e1,e2) -> (vars_of_exp e1) @ (vars_of_exp e2)
  | Sum(e1,e2) -> (vars_of_exp e1) @ (vars_of_exp e2)
  | Division(e1,e2) -> (vars_of_exp e1) @ (vars_of_exp e2)
  | Subtraction(e1,e2) -> (vars_of_exp e1) @ (vars_of_exp e2)
  | BoolNot(e) -> vars_of_exp e
  | BoolAnd(e1,e2) -> (vars_of_exp e1) @ (vars_of_exp e2)
  | BoolEq(e1,e2) -> (vars_of_exp e1) @ (vars_of_exp e2)
  | BoolNeq(e1,e2) -> (vars_of_exp e1) @ (vars_of_exp e2)
(*
let rec vars_of_bool_exp = function
  | BoolNot(e) -> vars_of_bool_exp e
  | BoolAnd(e1,e2) -> (vars_of_bool_exp e1) @ (vars_of_bool_exp e2)
  | BoolEq(e1,e2) -> (vars_of_bool_exp e1) @ (vars_of_bool_exp e2)
  | BoolNeq(e1,e2) -> (vars_of_bool_exp e1) @ (vars_of_bool_exp e2)
*)
let vars_of_atomic_guard = function
  | GuardLeq(e1,e2) -> (vars_of_exp e1) @ (vars_of_exp e2)
  | GuardLess(e1,e2) -> (vars_of_exp e1) @ (vars_of_exp e2)
  | GuardGeq(e1,e2) -> (vars_of_exp e1) @ (vars_of_exp e2)
  | GuardGreater(e1,e2) -> (vars_of_exp e1) @ (vars_of_exp e2)
  | GuardEqual(e1,e2) -> (vars_of_exp e1) @ (vars_of_exp e2)
  | GuardNeq(e1,e2) -> (vars_of_exp e1) @ (vars_of_exp e2)

let print_location chan loc = 
  let (x,y) = loc.locPos in 
  fprintf chan "<location id=\"%s\" x=\"%d\" y=\"%d\">\n" loc.locId x y;
  let (x,y) = loc.locNamePos in
  fprintf chan "\t<name x=\"%d\" y=\"%d\">%s</name>\n" x y loc.locName;	
  let (x,y) = loc.locInvarPos in
  fprintf chan "\t<label kind=\"invariant\" x=\"%d\" y=\"%d\">%s</label>\n" x y (xml_string_of_guard loc.locInvar);
  if (loc.locCommitted) then
    fprintf chan "\t<committed/>\n";
  if (loc.locUrgent) then
    fprintf chan "\t<urgent/>\n";
  fprintf chan "</location>\n"

let print_declaration chan (decl : temp_declaration) = 
  fprintf chan "<declaration>\n";
  let (clocks, vars, chans) = decl in
  if (List.length clocks > 0 ) then (
    fprintf chan "clock %s" (List.hd clocks);
    List.iter (fun c -> fprintf chan ", %s" c) (List.tl clocks);
    fprintf chan ";\n";
  );
  List.iter (function
|Var(name,init,(l,r)) -> fprintf chan "int[%d,%d] %s = %d;\n" l r name init
      |ConstVar(name,init) -> fprintf chan "const int %s = %d;\n" name init
    ) vars;
  if (List.length chans > 0 ) then (
    fprintf chan "chan %s" (List.hd chans);
    List.iter (fun c -> fprintf chan ", %s" c) (List.tl chans);
    fprintf chan ";\n";
  );
  fprintf chan "</declaration>\n"


let string_of_sync = function
  | None -> ""
  | Some (RecvChan s) -> s ^ "?"
  | Some (SendChan s) -> s ^ "!"

let string_of_updates ups = 
  let ups_str = List.map (fun (var,exp) -> sprintf "%s = %s" var (string_of_exp exp)) ups in
  String.concat ", " ups_str

(** FIXME Replace the print functions by the construction of an xml tree, which can then be converted to string with formatting *)

let print_edge chan edge =
  fprintf chan "<transition>\n\t<source ref=\"%s\"/>\n\t<target ref=\"%s\"/>\n\t" edge.edgeSource edge.edgeTarget;
  let (x,y) = edge.edgeGuardPos in
  fprintf chan "<label kind=\"guard\" x=\"%d\" y=\"%d\">%s</label>\n\t" x y (xml_string_of_guard edge.edgeGuard);
  let (x,y) = edge.edgeUpdatesPos in
  fprintf chan "<label kind=\"assignment\" x=\"%d\" y=\"%d\">%s</label>\n\t" x y (string_of_updates edge.edgeUpdates);
  let (x,y) = edge.edgeSyncPos in
  fprintf chan "<label kind=\"synchronisation\" x=\"%d\" y=\"%d\">%s</label>" x y (string_of_sync edge.edgeSync);
  List.iter (fun (x,y) -> fprintf chan "\n\t<nail x=\"%d\" y=\"%d\"/>" x y ) edge.edgeNails;
  fprintf chan "\n</transition>\n"


let print_template chan temp =
  fprintf chan "<template>\n<name>%s</name>\n" temp.tempName;
  print_declaration chan (temp.tempClocks,temp.tempVars, []);
  List.iter (print_location stdout) temp.tempLocations;
  fprintf chan "<init ref=\"%s\"/>\n" temp.tempInitialLocation.locId;
  List.iter (print_edge stdout) temp.tempEdges;
  fprintf chan "</template>\n"

let print_templates chan templates =
  List.iter (print_template chan) templates

let print_nta chan system = 
  fprintf chan "<?xml version=\"1.0\" encoding=\"utf-8\"?><nta>\n";
  print_declaration chan (system.sysClocks, system.sysVars, system.sysChans);
  print_templates chan system.sysTemplates;
  fprintf chan "<system>\n";
  system.sysProcessInstances |> 
  List.iter (fun (proc,temp) ->
      fprintf chan "%s = %s();\n" proc temp
    );
  fprintf chan "<system>system %s;</system>\n</nta>" (String.concat ", " (List.map fst system.sysProcessInstances))

