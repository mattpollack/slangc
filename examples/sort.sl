func merge [A] [A] [A] {
  a      []     -> a;
  []     b      -> b;
  [a:as] [b:bs] -> 
    match (a > b) {
      true -> [a] ++ (merge as [b:bs]);
      _    -> [b] ++ (merge [a:as] bs);
    }
}

func map [A] (A B) [B] {
  []     _ -> [];
  [x:xs] f -> [(f x)] ++ (map f xs);
}

# NOTE: Possibly allow non-exhaustive match statements when returning optional values?
func parse_int string int? {
  []     -> ?;
  [x:xs] -> 
    match (x >= '0' && x <= '9') {
      true -> # ...
    }
}
  
func main [string] int {
  args -> 
    print "hello world";
    0;
}
