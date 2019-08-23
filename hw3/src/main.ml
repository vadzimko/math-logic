open Tree;;
open Buffer;;
open Pervasives;;
open Printf;;

(*let cin = open_in "input.txt";;*)
let cout = open_out "output.txt";;

let unary un_op = match un_op with Neg -> "!";;
let binary bin_op = match bin_op with
      And  -> "&"
    | Or   -> "|"
    | Impl -> "->";;

let rec parse_tree tree str = match tree with
      Var var                   -> add_string str var

    | Unop (un_op,arg)          -> add_char str '(';
                                   add_string str (unary un_op);
                                   parse_tree arg str;
                                   add_char str ')'

    | Binop (bin_op,left,right) -> add_char str '(';
                                   add_string str (binary bin_op);
                                   add_char str ',';
                                   parse_tree left str;
                                   add_char str ',';
                                   parse_tree right str;
                                   add_char str ')';;

let tree_to_string tree =
    let str = Buffer.create 10000 in
    parse_tree tree str;
    contents str;;

(*let first_line = (input_line cin);;*)
let first_line = (read_line ());;
fprintf cout "%s\n" first_line;;

let y = Str.split (Str.regexp "|-") first_line in
    let rec split line =
        match line with
            [] -> ()
         |  h::[] -> let lexbuf = Lexing.from_string (h ^ "\n") in
                     fprintf cout "%s\n" (tree_to_string (Parser.main Lexer.main lexbuf));
         |  h::t -> split t in split y;;

let x = Str.split (Str.regexp "|-") first_line in
    let prin line = fprintf cout "%s\n" (tree_to_string (Parser.main Lexer.main (Lexing.from_string (line ^ "\n")))) in
    let rec prin_all lines = match lines with
                                     [] -> ()
                                  |  h::[] -> prin h
                                  |  h::t -> prin h; prin_all t in
    let rec split line =
        match line with
            [] -> ()
         |  h::[] -> prin h
         |  h::t -> let hypothesis = Str.split (Str.regexp ",") h in
                        match hypothesis with
                            [] ->  ()
                         |  h::[] -> prin h
                         |  h::t -> prin h; prin_all t;
                               split t in split x;;

fprintf cout "---\n";;
try
    while true do
        fprintf cout "%s\n" (tree_to_string (Parser.main Lexer.main (Lexing.from_string ((read_line ()) ^ "\n"))))
        (*fprintf cout "%s\n" (tree_to_string (Parser.main Lexer.main (Lexing.from_string (((input_line cin) ^ "\n")))));*)
    done
with _ -> exit 0

(*close_in cin;*)
(*close_out cout;*)

(*printf "%s\n" result;;*)
(*print_endline result;;*)
(*flush stdout;*)

