{
	open UppaalGuard
}
let digit = ['0'-'9']
let id = ['a'-'z' '_' 'A'-'Z'] ['a'-'z' 'A'-'Z' '_' '0'-'9']*

rule token = parse
  | digit+ as inum
    {NUM(int_of_string inum)}
	| "<=" {UB}
	| "<" {STUB}
	| ">=" {LB}
	| ">" {STLB}
	| "=" {EQ}
	| "&&" {AND}
	| id as text {ID(text)}
  | _ as t {printf "Line %d : Unknown token : %c\n"
  (lexbuf.Lexing.lex_curr_p.Lexing.pos_lnum)t; raise (Failure "Unknown token")}
  | eof		{EOF}

