func fib int int {
  0 -> 1;
  1 -> 1;
  n -> add (fib (sub n 1)) (fib (sub n 2));
}

func main [string] int {
  args ->
    | print (fib 5);
    | 0;
}