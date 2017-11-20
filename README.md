# Slang
Slang is foremost a functional language. Slang compiles to an intermediate byte code format reminiscent of lambda calculus. Bytecode emitted by the compiler is interpreted by the SlangVM. Targeting a custom virtual machine allows flexibility in mobile, and embedded applications. Use of an intermediate bytecode allows for simpler optimization at the lowest level. SlangVM has the ability to implement standard library components when application or device specific functionality is needed. 

Slang employs a strong and static type system. Strong typing complements the pattern matching facilities Slang provides. Static type checking allows for smaller bytecode executables as well as a quick, and memory efficient interpretation. 

```

def fib
| 0 = 1
| 1 = 1
| n = + (fib (- n 1)) (fib (- n 2))

```

## TODO
* [x] Lexer
* [ ] Parser
* [ ] AST
* [ ] Optimizer
* [ ] Runtime
