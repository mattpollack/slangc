# Slang Programming Language
Slang is a strong and statically typed pure functional language. Slang semantics enforce discrete manipulation of data through pattern matching, generics, and imperative-like side effects. 
```
# Fibonacci series
func fib int int {
  0 -> 1;
  1 -> 1;
  n -> fib (n - 1) + fib (n - 2);
}

# Output: 
# Fib: 5
func main [string] int {
  _ ->
    | print "Fib: " (fib 5);
    | 0;
}
```
## Introduction
Data manipulation and representation ultimately comprises operations on groups of bytes. Higher level abstraction facilitates programmer friendly interfaces into those bytes. Accomplishing these practices regularly requires unity between high and low level languages. Slang attempts to bridge this gap.

## Entry Point
Slang execution begins at 'main'. The function signature for Main resembles that of C/C++. It takes a list of string values [string] and returns an integer type int. Args is assigned to the string list, which is bound to it's body of 0, which is immediately returned.
```
func main [string] int {
  args -> 0;
}
```

## Pattern Matching
### Exhaustive Patterns
Function behaviour depends on the state of its input. A simple function, such as one that prints what it is given, can be accomplished as follows.
```
# Outputs its own parameters
func main [string] int {
  []     -> 0;
  [x:xs] -> 
    | print x;
    | main xs;
}
```
This simple example illustrates recursive pattern matching. When there is no input, return a status of 0, otherwise print the first of its input then recur on what remains. Each input state case matches an expression, and a result is guaranteed. This is known as an exhaustive pattern. If an input matches multiple cases, the first case is chosen.

Consider the fibonacci example. Main does not require a reference to its string argument parameter, this is denoted by '_'. Though it is non-exhaustive in a general sense, the compiler knows it operates only on literal values which match in all cases. 

### Non Exhaustive Patterns
Consider a function which does not match to all cases of its input.
```
# Contrived example
func example int int {
  0 -> 0;
}

# What happens here?
func main [string] int {
  # No matching case
  _ -> example 1;
}
```
TODO...

#### To be continued...