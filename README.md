# Slang Programming Language
Slang enforces discrete representation of data in a functional context. 
```
func fib int int
  0 -> 1;
  1 -> 1;
  n -> fib (n - 1) + fib (n - 2);
}

func main [string] int {
  _ ->
    | print "Fib: " (fib 5)
    | 0;
}

# Fib 5
```