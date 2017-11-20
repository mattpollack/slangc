# Slang
Slang is foremost a functional language. Slang employs a strong and static type system. Strong typing complements the pattern matching facilities Slang provides. Static type checking allows for smaller bytecode executables as well as a quick, and memory efficient interpretation. 

```

def fib (int int)
| 0 = 1
| 1 = 1
| n = + (fib (- n 1)) (fib (- n 2))

```