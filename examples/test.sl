func parse_int string int? {
  []     -> ?;
  [x:xs] -> 
    match (x >= '0' && x <= '9') {
      true -> x - '0';
    }
}

func main [string] int {
  []  -> 0;
  [x] -> 
    match (parse_int x) {
      ? -> -1;
      n -> n;
    }
}