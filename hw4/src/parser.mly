%{
open Tree;;
%}
%token <string> VAR
%token IMPL AND OR NOT
%token LPAREN RPAREN
%token EOL
%right IMPL
%left OR
%left AND
%nonassoc NOT
%start main
%type <Tree.tree> main
%%
main:
        expr EOL             { $1 }
expr:
        VAR                  { Var ($1) }
        | LPAREN expr RPAREN { $2 }
        | NOT expr           { Unop  (Neg, $2) }
        | expr AND expr      { Binop (And, $1, $3) }
        | expr OR expr       { Binop (Or, $1, $3) }
        | expr IMPL expr     { Binop (Impl, $1, $3) }
