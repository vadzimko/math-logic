{
open Parser
exception EOF
}

let var_reg = ['A' - 'Z'] + ['A'-'Z' '0' - '9' '\'']*
let empty = [' ' '\t' '\r']

rule main = parse
        var_reg as var { VAR(var) }
        | empty        { main lexbuf}
        | "->"         { IMPL }
        | "&"          { AND }
        | "|"          { OR }
        | "!"          { NOT }
        | "("          { LPAREN }
        | ")"          { RPAREN }
        | "\n"         { EOL }
        | eof          { raise EOF }


