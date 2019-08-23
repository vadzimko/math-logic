type token =
  | VAR of (string)
  | IMPL
  | AND
  | OR
  | NOT
  | LPAREN
  | RPAREN
  | EOL

open Parsing;;
let _ = parse_error;;
# 2 "src/parser.mly"
open Tree;;
# 16 "src/parser.ml"
let yytransl_const = [|
  258 (* IMPL *);
  259 (* AND *);
  260 (* OR *);
  261 (* NOT *);
  262 (* LPAREN *);
  263 (* RPAREN *);
  264 (* EOL *);
    0|]

let yytransl_block = [|
  257 (* VAR *);
    0|]

let yylhs = "\255\255\
\001\000\002\000\002\000\002\000\002\000\002\000\002\000\000\000"

let yylen = "\002\000\
\002\000\001\000\003\000\002\000\003\000\003\000\003\000\002\000"

let yydefred = "\000\000\
\000\000\000\000\002\000\000\000\000\000\008\000\000\000\004\000\
\000\000\000\000\000\000\000\000\001\000\003\000\000\000\005\000\
\000\000"

let yydgoto = "\002\000\
\006\000\007\000"

let yysindex = "\001\000\
\019\255\000\000\000\000\019\255\019\255\000\000\001\255\000\000\
\015\255\019\255\019\255\019\255\000\000\000\000\024\255\000\000\
\018\255"

let yyrindex = "\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\006\255\000\000\
\008\255"

let yygindex = "\000\000\
\000\000\252\255"

let yytablesize = 28
let yytable = "\008\000\
\009\000\001\000\010\000\011\000\012\000\015\000\016\000\017\000\
\013\000\006\000\000\000\006\000\007\000\007\000\006\000\006\000\
\010\000\011\000\012\000\003\000\011\000\014\000\000\000\004\000\
\005\000\010\000\011\000\012\000"

let yycheck = "\004\000\
\005\000\001\000\002\001\003\001\004\001\010\000\011\000\012\000\
\008\001\002\001\255\255\004\001\007\001\008\001\007\001\008\001\
\002\001\003\001\004\001\001\001\003\001\007\001\255\255\005\001\
\006\001\002\001\003\001\004\001"

let yynames_const = "\
  IMPL\000\
  AND\000\
  OR\000\
  NOT\000\
  LPAREN\000\
  RPAREN\000\
  EOL\000\
  "

let yynames_block = "\
  VAR\000\
  "

let yyact = [|
  (fun _ -> failwith "parser")
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'expr) in
    Obj.repr(
# 16 "src/parser.mly"
                             ( _1 )
# 92 "src/parser.ml"
               : Tree.tree))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : string) in
    Obj.repr(
# 18 "src/parser.mly"
                             ( Var (_1) )
# 99 "src/parser.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'expr) in
    Obj.repr(
# 19 "src/parser.mly"
                             ( _2 )
# 106 "src/parser.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 20 "src/parser.mly"
                             ( Unop  (Neg, _2) )
# 113 "src/parser.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 21 "src/parser.mly"
                             ( Binop (And, _1, _3) )
# 121 "src/parser.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 22 "src/parser.mly"
                             ( Binop (Or, _1, _3) )
# 129 "src/parser.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 23 "src/parser.mly"
                             ( Binop (Impl, _1, _3) )
# 137 "src/parser.ml"
               : 'expr))
(* Entry main *)
; (fun __caml_parser_env -> raise (Parsing.YYexit (Parsing.peek_val __caml_parser_env 0)))
|]
let yytables =
  { Parsing.actions=yyact;
    Parsing.transl_const=yytransl_const;
    Parsing.transl_block=yytransl_block;
    Parsing.lhs=yylhs;
    Parsing.len=yylen;
    Parsing.defred=yydefred;
    Parsing.dgoto=yydgoto;
    Parsing.sindex=yysindex;
    Parsing.rindex=yyrindex;
    Parsing.gindex=yygindex;
    Parsing.tablesize=yytablesize;
    Parsing.table=yytable;
    Parsing.check=yycheck;
    Parsing.error_function=parse_error;
    Parsing.names_const=yynames_const;
    Parsing.names_block=yynames_block }
let main (lexfun : Lexing.lexbuf -> token) (lexbuf : Lexing.lexbuf) =
   (Parsing.yyparse yytables 1 lexfun lexbuf : Tree.tree)
