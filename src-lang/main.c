#include "parser.h"
#include "analysis.h"
#include "file.h"

#define DEBUG 1

int main(int argc, char ** argv) {
    char * version =
	"  __\n"
	" /     |     * SLANG\n"
	" \\\\\\\\  |     * 0.0.0\n"
	"  __/  |___  * Matt Pollack\n"
	"\n";
    
    printf("%s", version);
    
    file_t src = file_load("examples/test.sl");

    if (src.buffer == 0) {
	printf("Cannot find file '%s'\n", src.name);
    }
    else {
	parser_t * parser = parser_create(src.buffer);
	ast_t    * res    = parser_parse(parser);

	error_print(&parser->error);

	ast_destroy(res);
	parser_destroy(parser);
    }
    
    file_destroy(&src);

    return 0;
}
