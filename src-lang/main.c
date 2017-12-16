#include "parser.h"
#include "error.h"

#define DEBUG 1

int main(int argc, char ** argv) {
    printf("## slang 0.0.0\n");

    char * raw =
	"func fib int int {\n"
	"  0 -> 1; \n"
	"  1 -> 1; \n"
	"  n -> fib (n - 1) + fib (n - 2);\n"
	"}\n";
    parser_t * parser = parser_create(raw);
    ast_t    * res    = parser_parse(parser);

    if (DEBUG)
	printf("\n-- RAW PRINT --\n%s---------------\n\n", raw);
    
    if (parser->error) {
	error_t e = error_create(&parser->lexer->token, raw, parser->error_msg);
	error_print(&e);
    }

    if (DEBUG && !parser->error)
	ast_print(res);
    
    ast_destroy(res);
    parser_destroy(parser);
}

/*

type list a = a (list a) | empty

func fib int int {
  0 -> 1
  1 -> 1
  n -> (+ (fib (- n 1)) (fib (- n 2)))
  n -> fib (n - 1) + fib (n + 2)
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
: match_expr_list "->" expression

match_expr_list
: match_expr match_expr_list
| match_expr

match_expr
: identifier
| number

type 
: 

*/
