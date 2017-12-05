#include "parser.h"

void error_print(parser_t * parser) {
    if (parser->error) {
	printf("%d:%d: %s\n",
	       parser->lexer->ln,
	       parser->lexer->cn,
	       parser->error_msg);
	
	char * curr = parser->lexer->token.buffer;
	int i = 0;

	while (curr[0] != '\n' &&
	       curr    != parser->buffer) {
	    ++i;
	    --curr;
	}

	if (curr[0] == '\n') {
	    --i;
	    ++curr;
	}
	
	while (curr[0] != '\n' &&
	       curr[0] != '\0') {
	    printf("%c", curr[0]);
	    ++curr;
	}

	printf("\n");

        for (; i > 0; --i) {
	    printf(" ");
	}

	printf("^\n");
    }
}

int main(int argc, char ** argv) {
    printf("## slang 0.0.0\n");

    char * raw =
	"func fib (int int) \n"
	"| 0 = 1 \n"
	"| 1 = 1 \n"
	"| n = (add (fib (sub n 1)) (fib (sub n 2))) \n";
    parser_t * parser = parser_create(raw);
    ast_t    * res    = parser_parse(parser);

    if (parser->error) {
	error_print(parser);
    }
    
    parser_destroy(parser);
}

/*

func fib (int int)
| 0 = 1
| 1 = 1
| n = fib (n - 1) + fib (n - 2)



*/
