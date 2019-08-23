type un_op = Neg;;
type bin_op = And | Or | Impl;;

type tree =
      Unop  of un_op * tree
	| Binop of bin_op * tree * tree
    | Var   of string;;
