(* Simplify with this:
 http://plus.kaist.ac.kr/~shoh/ocaml/ocamllex-ocamlyacc/ocamllex-tutorial/sec-toy-language.html
 *)
{
  open UtaParser
  open Printf

  let incr_linenum lexbuf =
    let pos = lexbuf.Lexing.lex_curr_p in
      lexbuf.Lexing.lex_curr_p <- { pos with
        Lexing.pos_lnum = pos.Lexing.pos_lnum + 1;
        Lexing.pos_bol = pos.Lexing.pos_cnum;
      }
  ;;
}

let digit = ['0'-'9']+
let id = ['a'-'z' '_' 'A'-'Z'] ['a'-'z' 'A'-'Z' '_' '0'-'9']*

rule token = parse
  | digit as inum
    {NUM(int_of_string inum)}
  | [' ' '\t']	{ token lexbuf }
  | "\n" { incr_linenum lexbuf; token lexbuf}
  | "/*" {longcomment_lang lexbuf}
  | "//" {onelinecomment_lang lexbuf}
  | "<=" | "&lt;=" {LEQ}
  | "<" | "&lt;" {LE}
  | ">=" | "&gt;=" {GEQ}
  | ">" | "&gt;" {GE}
  | "==" {EQ}
  | "!=" {NEQ}
  | "!" {BNOT}
	| "=" {ASSIGN}
	| "[" {LSBRACK}
	| "]" {RSBRACK}
	| ":=" {ASSIGN}
	| "&amp;" | "&&" | "and" {AND}
	| "or" {OR}
	| "||" {OR}
	| "not" {NOT}
  | "\n" | "\t" {token lexbuf}
	| "E<>" {RQUERY}
  | "+" {PLUS}
  | "-" {MINUS}
  | "*" {MULT}
  | "/" {DIV}
	| "(" {LPAR}
	| ")" {RPAR}
	| "true" {NUM(1)}
	| "false" {NUM(0)}
	| "bool" {BOOL}
	| "clock" {CLOCK}
	| "chan" {CHAN}
	| "int" {INT}
	| "const" {CONST}
	| "urgent" {URGENT}
	| ";" {SCOLON}
	| "," {COMMA}
	| "system" {SYSTEM}
	| "." {DOT}
  | id as text {ID(text)}
  | _ as t {fprintf stderr "Line %d : Unknown token : %c\n"
				   (lexbuf.Lexing.lex_curr_p.Lexing.pos_lnum)t; raise (Failure "Unknown token")}
  | eof		{EOF}
and longcomment_lang = parse 
  | "*/" {token lexbuf}
  | "\n" { incr_linenum lexbuf; longcomment_lang lexbuf}
  | _ {longcomment_lang lexbuf}
and onelinecomment_lang = parse
  | "\n" { incr_linenum lexbuf; token lexbuf}
	| eof {EOF}
  | _ {onelinecomment_lang lexbuf}
