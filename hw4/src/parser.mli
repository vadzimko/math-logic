type token =
  | VAR of (string)
  | IMPL
  | AND
  | OR
  | NOT
  | LPAREN
  | RPAREN
  | EOL

val main :
  (Lexing.lexbuf  -> token) -> Lexing.lexbuf -> Tree.tree
