open Batteries;;
open Xml;;
open Sys;; 
open Printf;;
open Str;;
open Uta;;
(** TODO 
    1) In XML-light, given an XML tag, one cannot have access to line number.
    So if an error occurs inside a declaration or a guard, I don't know
    how to return the line number in the input file.

    WHAT IS HOT
    1) Check if local declarations are parsed correctly

*)

exception No_declaration
(**
 * Error message, line number, and character range
*)
exception Parse_error of string 

let xml_children_by_tag xml tag = 
  List.filter (function | Element(t,_,_) when t = tag -> true
			| _ -> false) (Xml.children xml)

let parse_declaration str =
  let lexbuf = Lexing.from_string str in
  (try 
     UtaParser.declaration UtaLexer.token lexbuf
   with e ->
     let curr = lexbuf.Lexing.lex_curr_p in
     let line = curr.Lexing.pos_lnum in 
     let cnum = curr.Lexing.pos_cnum - curr.Lexing.pos_bol in
     let tok = Lexing.lexeme lexbuf in
     raise (Parse_error (sprintf 
			   "Parsing error in declaration tag. At line %d:%d, token %s" line cnum tok))
  )

let parse_guard str =
  let lexbuf = Lexing.from_string str in
  (try 
     let g = UtaParser.guard UtaLexer.token lexbuf in
     g
   with e ->
     let curr = lexbuf.Lexing.lex_curr_p in
     let line = curr.Lexing.pos_lnum in
     let cnum = curr.Lexing.pos_cnum - curr.Lexing.pos_bol in
     let tok = Lexing.lexeme lexbuf in
     raise (Parse_error (sprintf "Cannot parse guard. Error at line%d:%d, token %s\n Guard: %s" line cnum tok str))
  )

let parse_updates str =
  let lexbuf = Lexing.from_string str in
  (try 
     UtaParser.updates UtaLexer.token lexbuf
   with e ->
     raise (Parse_error "Cannot parse updates")
  )


let print_declaration decl = 
  let clocks, ints, chans = decl in
  printf "Global clocks: ";
  List.iter (fun name -> printf "%s " name) clocks;
  printf "\nGlobal discrete variables: ";
  List.iter (fun (name,v) -> printf "(%s,%d) " name v) ints;
  printf "\nChannels: ";
  List.iter (fun name -> printf "%s " name) chans;
  printf "\n"


let parse_template xml =
 (*
eprintf "NEW TEMPLATE\n";
Xml.iter (function 
| Element(_) as node ->
eprintf "NODE: %s\n" (Xml.tag node)
| PCData(s) as node ->
eprintf "PCDATA: %s\n" s
) xml;
*)
  let parse_name = function
    |Element(tag,_,children) ->
      (match (List.hd children) with
	 PCData name -> name
       | _ -> failwith "PCData for name was expected"
      )
    |_ -> failwith "Name node ame was expected"
  in
  let parse_location node =
    let loc =	
      {
	locId = "";
	locPos = (0,0);
	locName = "";
	locNamePos = (0,0);
	locInvar = [];
	locInvarPos = (0,0);
	locCommitted = false;
	locUrgent = false;
      }
    in
    Xml.iter
      (fun node ->
	 match node with
	   Element(tag,attr,children) ->
	   (match tag with
	      "name" -> loc.locName <- (parse_name node);
	      (try
		 let x = int_of_string (Xml.attrib node "x") in 
		 let y = int_of_string (Xml.attrib node "y") in
		 loc.locNamePos <- (x,y)
	       with e ->
		 loc.locNamePos <- (0,0)
	     (*
eprintf "Couldn't parse location name position";
raise e
*)
	      )
	    | "committed" -> loc.locCommitted <- true
	    | "urgent" -> loc.locUrgent <- true
	    | "label" ->
	      (try
		 if (Xml.attrib node "kind" = "invariant") then (
		   let inv = parse_guard (Xml.pcdata (List.hd children) ) in
		   loc.locInvar <- inv;
		   (try 
		      let x = int_of_string (Xml.attrib node "x") in 
		      let y = int_of_string (Xml.attrib node "y") in
		      loc.locInvarPos <- (x,y);
		    with _ ->
		      loc.locInvarPos <- (0,0)
		   )
		 )
	       with e ->
		 eprintf "Couldn't parse location label";
		 raise e
	      )
	    | _ -> ()
	   )
	 | _ -> failwith "location cannot have PCData children"
      ) node;
    let (x,y) = 
      (try
	 (int_of_string (Xml.attrib node "x")),
	 (int_of_string (Xml.attrib node "y"))
       with _ -> (0,0)
      ) in 
    loc.locPos <- (x,y);
    (try
       let id = Xml.attrib node "id" in
       loc.locId <- id;
     with e -> 
       eprintf "Missing location id";
       raise e
    );
    loc
  in
  let parse_transition node = 
    let trans = 
      {
	edgeSource = "";
	edgeGuard = [];
	edgeGuardPos = (0,0);
	edgeSync = None;
	edgeSyncPos = (0,0);
	edgeUpdates = [];
	edgeUpdatesPos = (0,0);
	edgeTarget = "";
	edgeNails = [];
      } in
    Xml.iter 
      (fun node ->
	 match node with
	   Element(tag,_,children) ->
	   (match tag with
	      "source" -> trans.edgeSource <- Xml.attrib node "ref"
	    |"target" -> trans.edgeTarget <- Xml.attrib node "ref"
	    |"label" ->
	      let (x,y) = 
		(try
		   (int_of_string (Xml.attrib node "x")),
		   (int_of_string (Xml.attrib node "y"))
		 with _ ->
		   (0,0)
		)
	      in
	      (match (Xml.attrib node "kind") with
		 "guard" -> 
		 trans.edgeGuardPos <- (x,y);
		 let g = parse_guard (Xml.pcdata (List.hd children)) in						 
		 trans.edgeGuard <- g
	       | "assignment" ->
		 trans.edgeUpdatesPos <- (x,y);
		 let g = parse_updates (Xml.pcdata (List.hd children)) in
		 trans.edgeUpdates <- g
	       | "synchronisation" ->
		 let rc = Xml.pcdata (List.hd (Xml.children node)) in
		 trans.edgeSync <- Some(
		     if (String.contains rc '?') then (
		       RecvChan(String.sub rc 0 ((String.length rc)-1))
		     ) else if (String.contains rc '!') then (
		       SendChan(String.sub rc 0 ((String.length rc)-1))
		     ) else (
		       failwith (sprintf "Synchronisation string does not contain ? or !: %s" rc)
		     )
		   );
		 trans.edgeSyncPos <- (x,y)
	       | "comments" -> ()
	       | other -> failwith (sprintf "Unexpected label kind in transition: %s" other)
	      )
	    | "nail" ->
	      let (x,y) = 
		(try 
		   (int_of_string (Xml.attrib node "x")),
		   (int_of_string (Xml.attrib node "y"))
		 with _ ->
		   (0,0)
		) in
	      trans.edgeNails <- (x,y) :: trans.edgeNails
	    | _ as n -> failwith (sprintf "Unexpected tag: %s" n)
	   )
	 | _ -> failwith "Unexpected PCData"
      ) node;
    trans.edgeNails <- List.rev trans.edgeNails;
    trans
  in
  let loc_nodes = xml_children_by_tag xml "location" in
  let trans_nodes = xml_children_by_tag xml "transition" in
  let init_node = xml_children_by_tag xml "init" in
  let name_node = xml_children_by_tag xml "name" in
  let decl_node = xml_children_by_tag xml "declaration" in
  let locs = List.rev (List.map parse_location loc_nodes) in
  let trans = List.rev (List.map parse_transition trans_nodes) in
  let initLoc = 		
    let initId = Xml.attrib (List.hd init_node) "ref" in
    let initlocs = List.filter (fun loc -> loc.locId = initId) locs in
    if (List.length initlocs = 0 ) then
      failwith "Initial location missing"
    else (List.hd initlocs)
  in
  let (clocks,vars,_) = 		
    (match decl_node with
     (* The declaration tag may be absent, in which case decl_node = [] *)
       [] -> 
    (*
eprintf "Template: Empty declaration\n"; flush stderr;
*)
       ([],[],[])
     (* Otherwise we look at the first node. Its only child should be a pcdata *)
     | declnode :: _ ->
       (try
	  let pcdnode = 
	    List.hd (Xml.children declnode) in
      (*
eprintf "Template: Some declaration\n";
eprintf "Decl: %s\n" (Xml.pcdata pcdnode);
*)
	  parse_declaration (Xml.pcdata pcdnode)
	with Failure(s) when s = "hd" -> ([],[],[])
	   | _ as e -> raise e
       )
    (*
let declstr = 
(match declnode with
PCData(s) -> 
(*eprintf "PCDATA: %s\n" s; flush stderr;*) s
| Element(_) as e -> 
(*
eprintf "ELEMENT: %s\n" (Xml.tag e); flush stderr;
*)
""
) in
eprintf "Decl string: %s\n" declstr;
let pcdatanode = match Xml.children declnode with
[] -> failwith "declaration node has no child"
| c :: _ -> c
in
let decl = Xml.pcdata pcdatanode in
parse_declaration decl												
*)
    )
  in
  let name = Xml.pcdata (List.hd (Xml.children (List.hd name_node))) in
  {
    tempName = name;
    tempLocations = List.rev locs;
    tempInitialLocation = initLoc;
    tempEdges = List.rev trans;
    tempClocks = clocks;
    tempVars = vars;		
  }

let parse_templates xml =
  List.rev(Xml.fold (fun init node -> match node with
      | (Element(tag, attr,children) as tmp) when tag = "template" ->
	(parse_template tmp) :: init
      | _ -> init
    ) [] xml)

let parse_system xml = 
  let sysnodes = xml_children_by_tag xml "system" in
  match sysnodes with
    [] -> failwith "Missing system tag"
  | sysnode :: _ -> 
    let sysstr = Xml.pcdata (List.hd (Xml.children sysnode)) in
    let lexbuf = Lexing.from_string sysstr in
    (try 
       UtaParser.system UtaLexer.token lexbuf
     with e ->
       let curr = lexbuf.Lexing.lex_curr_p in
       let line = curr.Lexing.pos_lnum in
       let cnum = curr.Lexing.pos_cnum - curr.Lexing.pos_bol in
       let tok = Lexing.lexeme lexbuf in
       raise (Parse_error (sprintf "Cannot parse system definition. Error at line %d, char %d, token %s" line cnum tok))
    )



let parse_nta xml = 
  (try 
     let global_decl = 
       Xml.fold (fun init node -> match node with
	   | Element(tag, attr,children) when tag = "declaration" ->
	     (match (List.hd children) with
		PCData s -> parse_declaration s
	      | _ -> init
	     )
	   | _ -> init
	 ) ([],[],[]) xml
     in
     let templates = parse_templates xml in
     let get_template_by_name name = 
       let rec aux = function
	 | [] -> failwith (sprintf "No template with name %s" name)
	 | tmp :: _ when tmp.tempName = name -> tmp
	 | _ :: l -> aux l
       in
       aux templates
     in
     let procInstances = parse_system xml in 
     let procs = 
       procInstances |>
       List.map (fun (proc,temp) ->
	   let temp = get_template_by_name temp in										
	   {temp with tempName = proc}
	 )
     in
     {
       sysTemplates = procs;
       sysProcessInstances =  procInstances;
       sysClocks = (fun (a,_,_) -> a) global_decl;
       sysVars = (fun (_,a,_) -> a) global_decl;
       sysChans = (fun (_,_,a) -> a) global_decl;
       sysQuery = EmptyQuery
     }
   with (Xml.Error e) ->
     eprintf "%s\n" (Xml.error e);
     failwith ""
      |Not_pcdata xml ->
	failwith ("Not a pcdata\n" ^ (Xml.to_string_fmt xml))
      | _ as e -> raise e
  )

let nta_from_file file =
  try
    let xml_parser = XmlParser.make() in
    XmlParser.prove xml_parser false;
    let xml = XmlParser.parse xml_parser (XmlParser.SFile file) in
    parse_nta xml
  with Xml.Error(e) ->
    raise (Parse_error (Xml.error e))

let nta_from_string str =
  try
    let xml_parser = XmlParser.make() in
    XmlParser.prove xml_parser false;
    let xml = XmlParser.parse xml_parser (XmlParser.SString str) in
    (*let xml = Xml.parse_string str in *)
    parse_nta xml
  with Xml.Error(e) ->
    raise (Parse_error (Xml.error e))

let query_from_file file = 
  if (file = "" ) then EmptyQuery
  else(
    let infile = open_in file in
    let lexbuf = Lexing.from_channel infile in
    (try
       let q = UtaParser.query UtaLexer.token lexbuf in
       close_in infile;
       q
     with 
       Sys_error(_) as e-> eprintf "Cannot open query file\n"; raise e
     | _  -> 
       let curr = lexbuf.Lexing.lex_curr_p in
       let line = curr.Lexing.pos_lnum in
       let cnum = curr.Lexing.pos_cnum - curr.Lexing.pos_bol in
       let tok = Lexing.lexeme lexbuf in
       raise (Parse_error (sprintf 
			     "Cannot parse query. Error at line %d:%d, token %s" line cnum tok))
    )
  )


let _ =
  if (Filename.basename Sys.argv.(0) = "utaReader.native" ) then(
    try
      (* Create a custom parser by disabling auto DTD checking *)
      let xml_parser = XmlParser.make() in
      XmlParser.prove xml_parser false;
      let xml = XmlParser.parse xml_parser (XmlParser.SFile Sys.argv.(1)) in
      let nta = parse_nta xml in
      print_nta stdout nta
    with Xml.Error(e) ->
      Printf.printf "%s\n" (Xml.error e)
  )

