#include "parser.h"
#include "analysis.h"
#include "file.h"

#define DEBUG 0

int main(int argc, char ** argv) {
    char * version =
	"  __\n"
	" /     |     * SLANG\n"
	" \\\\\\\\  |     * 0.0.0\n"
	"  __/  |___  * Matt Pollack\n"
	"\n";
    
    printf("%s", version);
    
    file_t src = file_load("examples/test.sl");

    if (DEBUG) {
	printf("-- src begin --\n");
	printf("%s\n", src.buffer);
	printf("-- src end ----\n");
    }

    if (src.buffer == 0) {
	printf("Cannot find file '%s'\n", src.name);
    }
    else {
	parser_t * parser = parser_create(src.buffer);
	ast_t    * ast    = parser_parse(parser);
	
	if (parser->error.set) {
	    error_print(&parser->error);
	}
	else {
	    env_t * env    = env_create();
	    ast_t * stage1 = prepare(ast, env);
	    
	    env_destroy(env);
	}
	
	ast_destroy(ast);
	parser_destroy(parser);
    }
    
    file_destroy(&src);

    return 0;
}
