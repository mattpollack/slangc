type Parser A 
{ string [A]
| ERROR string
}

type Token
{ PAREN_OPEN
| PAREN_CLOSE
| IDENTIFIER string
| INTEGER int
}

func skip_whitespace Parser<A> Parser<A> {
  ([h:ts] tokens) -> 
    match h {
      " "  -> skip_whitespace (ts tokens);
      "\n" -> skip_whitespace (ts tokens);
      "\t" -> skip_whitespace (ts tokens);
      "\0" -> skip_whitespace (ts tokens);
      _    -> ([h:ts] tokens);
    }
}

func parse string [Token]? {
  src -> [];
}

func main [string] int {
  [src] -> 
    | parse "(a 10 c d (e f g) h i j)";
    | 0;
  flags -> 1;
}