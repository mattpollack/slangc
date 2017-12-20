type Parser A = [A] string | Error string;

type AST
= Function
| Type;

func parse string [AST] {
  ""  -> [];
  src -> []; # TODO
}

func main [string] int {
  args -> 0;
}