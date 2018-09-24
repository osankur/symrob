type token =
  | NUM of (int)
  | ID of (string)
  | LB
  | STLB
  | UB
  | STUB
  | EQ
  | AND
  | EOF

val guard :
  (Lexing.lexbuf  -> token) -> Lexing.lexbuf -> string
