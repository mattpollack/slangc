option_pipe(a [(a a?)] a?)
| v []     = v
| v [x:xs] =
  match (x v)
  | ? = ?
  | d = option_map d xs
  
  