option_map<a>(a [(a a?)] a?)
| v []     = v
| v [x:xs] =
  match (x v)
  | ? = ?
  | d = option_map d xs

func main([string] IO)
| _ =
  
  