%{
  open Printf
  open Uta
%}
%token <int> NUM
%token <string> ID
%token SYSTEM CONST URGENT
%token LE LEQ GE GEQ EQ NEQ AND OR EOF
%token PLUS MINUS MULT DIV
%token BNOT
%token CLOCK CHAN INT
%token SCOLON COMMA ASSIGN
%token LPAR RPAR LSBRACK RSBRACK
%token RQUERY NOT DOT
%token TRUE FALSE BOOL
%left PLUS MINUS
%left MULT DIV
%left OR
%left AND
%left EQ NEQ
%nonassoc UMINUS
%nonassoc UBNOT
%type <Uta.temp_declaration> declaration
%type <Uta.guard> guard
%type <Uta.update> updates
%type <(string * string) list> system
%type <Uta.query> query
%start guard
%start query
%start declaration
%start updates
%start system
%%

id_list :  ID SCOLON {[$1]}
		| ID COMMA id_list {$1 :: $3 }

id_assign_list : ID ASSIGN NUM SCOLON {[($1,$3)]}
		| ID ASSIGN NUM COMMA id_assign_list 
				 {($1,$3) :: $5}

clock_declaration: 
		CLOCK id_list {$2}

expression: 
    NUM {Constant($1)}
    | ID {Variable($1)}
    | expression PLUS expression {Sum($1,$3)}
    | expression MINUS expression {Subtraction($1,$3)}
    | expression MULT expression {Product($1,$3)}
    | expression DIV expression {Division($1,$3)}
		| MINUS expression %prec UMINUS {Subtraction(Constant(0),$2)}
    | BNOT expression %prec UBNOT {BoolNot($2)}
    | LPAR expression AND expression RPAR {BoolAnd($2,$4)}
    | expression EQ expression {BoolEq($1,$3)}
    | expression NEQ expression {BoolNeq($1,$3)}
		| LPAR expression RPAR {$2}

rel_int:
        NUM {$1}
| MINUS NUM %prec UMINUS {(-($2))}


int_range:
		LSBRACK rel_int COMMA rel_int RSBRACK {($2,$4)}

int_declaration:
INT id_assign_list {List.map (fun (x,y) -> Var(x,y,(-max_int,max_int))) $2}
| INT int_range id_assign_list {List.map (fun (x,y) -> Var(x,y,$2)) $3}
		| INT int_range id_list
			  {
				List.map (fun x -> Var(x,0,$2)) $3
			  }
		| INT int_range ID ASSIGN rel_int SCOLON
			  {
				[Var($3,$5,$2)]
			  }
		| INT id_list
			  {
				List.map (fun x -> Var(x,0,(-max_int,max_int))) $2
			  }
		| BOOL id_list
			  {
				List.map (fun x -> Var(x,0,(0,1))) $2
			  }
		| BOOL ID ASSIGN NUM SCOLON
			  {
				[Var($2,$4,(0,1))]
			  }

const_int_declaration:
		CONST INT id_assign_list 
		{List.map (fun x -> ConstVar(x)) $3}

chan_declaration:
		CHAN id_list {$2}|
		URGENT CHAN id_list {
						 eprintf "Parse warning: urgent channels are not supported, assuming regular channel\n";
						 $3
					 }
 


atomic_guard:
 expression LE expression {GuardLess($1,$3)}
	| expression LEQ expression {GuardLeq($1,$3)}
	| expression GE expression {GuardGreater($1,$3)}
	| expression GEQ expression {GuardGeq($1,$3)}
	| expression EQ expression {GuardEqual($1,$3)}
	| expression NEQ expression {GuardNeq($1,$3)}

guard:
atomic_guard {[$1]} | atomic_guard AND guard {$1 :: $3}

atomic_update: ID ASSIGN expression {($1,$3)}

updates:
atomic_update {[$1]} | atomic_update COMMA updates {$1 :: $3}

declaration: 
	{[],[],[]}
	 | clock_declaration declaration 
						 {
						   let clocks, ints, chans = $2 in
						   ($1 @ clocks), ints, chans
						 }
	 | int_declaration declaration 
					   {
						 let clocks, ints, chans = $2 in
						 clocks, ($1 @ ints), chans
					   }
	 | chan_declaration declaration
						{
						  let clocks, ints, chans = $2 in
						  clocks, ints, ($1 @ chans)
						}
	 | const_int_declaration declaration
					   {
							 let clocks, ints, chans = $2 in
							 clocks, ($1 @ ints), chans
					   }

process_decl:
	 {[]}| ID ASSIGN ID LPAR RPAR SCOLON process_decl {($1,$3) :: $7}

system: process_decl SYSTEM id_list  
{
	let proctypes = $1 in
	let get_type proc = 
		let rec aux = function
			| [] -> proc
			| (p,t) :: _ when p = proc -> t
			| _ :: l -> aux l
		in
		aux proctypes
	in
	List.map (fun p -> (p, get_type p)) $3
}

boolean_query: 
ID DOT ID {AtomicQuery($1,$3)}
	 | NOT ID DOT ID {NotQuery(AtomicQuery($2,$4))}
	 | boolean_query AND boolean_query 
									 {AndQuery($1,$3)}
	 | boolean_query OR boolean_query 
									 {OrQuery($1,$3)}
	 | NOT LPAR boolean_query RPAR
									 {NotQuery($3)}
	 | LPAR boolean_query RPAR 
					{$2}

query: RQUERY boolean_query {ReachQuery($2)}
%%
