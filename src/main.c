#include "parser.h"

int main(int argc, char ** argv) {
    printf("## slang 0.0.0\n");

    char * raw =
	"func fib (int int)"
	"| 0 = 1"
	"| 1 = 1"
	"| n = fib (- n 1) + fib (- n 2)";
    
    parser_t *parser = parser_create(raw);
    ast_t    *res    = parser_parse(parser);
    
    parser_destroy(parser);
}

/*

func fib (int int)
| 0 = 1
| 1 = 1
| n = fib (- n 1) + fib (- n 2)

*/
