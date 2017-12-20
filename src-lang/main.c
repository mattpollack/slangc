#include "parser.h"
#include "analysis.h"

#define DEBUG 0

int main(int argc, char ** argv) {
/* Sketchpad, before escaping     
  __
 /     |     * SLANG             
 \\\\  |     * 0.0.0             
  __/  |___  * Matt Pollack      
*/
    char * version =
	"  __\n"
	" /     |     * SLANG\n"
	" \\\\\\\\  |     * 0.0.0\n"
	"  __/  |___  * Matt Pollack\n\n"
	;
    
    printf("%s", version);

    char * raw =
	"func fib int int {\n"
	"  0 -> 1; \n"
	"  1 -> 1; \n"
	"  n -> add (fib (sub n 1)) (fib (sub n 2));\n"
	"}\n"
	"\n"
	"func main [string] int {\n"
	"  args -> \n"
	"    | print (fib 5)\n"
	"    | 0;\n"
	"}\n"
        ;
    
    parser_t * parser = parser_create(raw);
    ast_t    * res    = parser_parse(parser);

    if (DEBUG) {
	printf("\n-- RAW PRINT --\n%s\n", raw);
    }

    if (parser->error.set) {
	error_print(&parser->error);
    }
    
    ast_destroy(res);
    parser_destroy(parser);
}

/*

type List a = a (List a) | empty;
type Pair a b = a b;

func merge [A] [A] [A] {
  a      []     -> a;
  []     b      -> b;
  [x:xs] [y:ys] ->
    match (x > y) {
      true -> x ++ (merge xs (y ++ ys));
      _    -> y ++ (merge (x ++ xs) ys);
    }
}

func marge_sort [A] [A] {
  []   -> [];
  [x]  -> [x];
  list -> # ...
}

func fib int int {
  0 -> 1;
  1 -> 1;
  n -> fib (n - 1) + fib (n + 2);
}

func main [string] IO {
  []     -> IO;
  [x:xs] ->
    match res {
      ? -> print "Cannot parse int from x";
      n -> print n " " (main xs);
    }
}

GRAMMAR
-------

base
: function
| type

function
: "func" identifier type_list function_body

function_body
: "{" match_body_list "}"

match
: "match" expression "{" match_body_list "}"

match_body_list
: match_body match_body_list
| match_body

match_body
: match_expr_list "->" expression ";"

match_expr_list
: match_expr match_expr_list
| match_expr

match_expr
: identifier
| number


expression
: "%"

*/
