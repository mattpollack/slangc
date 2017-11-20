#include "parser.h"
#include "lexer.h"

parser_t * parser_create(char * raw) {
    parser_t * res = malloc(sizeof(parser_t));
    res->lexer = lexer_create();
    res->lexer->buffer = raw;
    res->buffer = 0;
    
    return res;
}

void parser_destroy(parser_t * parser) {
    lexer_destroy(parser->lexer);
    free(parser);
}

/* PARSING */

#define LEXER parser->lexer
#define LEXER_NEXT lexer_next(parser->lexer)
#define LEXER_PEEK lexer_peek(parser->lexer)
#define LEXER_NEXT_IF(t) lexer_next_if(parser->lexer, (t))

// Defines a function that returns an error type
// Uses typeof to typedef the return type of the anonymous choice type
#define PARSER_F(type, body)				     \
    error_t(type ## _t) parse_ ## type (parser_t * parser) { \
	typedef typeof( parse_ ## type(parser)) __r_t__;     \
	(body);						     \
    }

#define PARSER_RET(d) (__r_t__) {.type=CHOICE_0,.d0=((__r_t__.d0) d)}
#define PARSER_MSG(m) (__r_t__) {.type=CHOICE_1,.d1=(m)}

PARSER_F(
    application, {
	return PARSER_MSG("TODO parse application");
    });

PARSER_F(
    signature, {
	return PARSER_MSG("TODO parse signature");
    });

PARSER_F(
    namespace, {
	return PARSER_MSG("TODO parse namespace");
    });

PARSER_F(
    function, {
	return PARSER_MSG("TODO parse function");
    });

#define BREAK_ERROR error = true; break

ast_t * parser_parse(parser_t * parser) {
    bool error = false;
    ast_t *ast = ast_create();

    while (!LEXER_NEXT_IF(BUFFER_END)) {
	if (LEXER_NEXT_IF(FUNC)) {
	    if (LEXER_PEEK.type != IDENTIFIER) {
		printf("Expected identifier\n");
		BREAK_ERROR;
	    }

	    token_t identifier = LEXER_NEXT;

	    AUTO(f, parse_function(parser));

	    if (is_error(f)) {
		printf("%s\n", f.d1);
	        BREAK_ERROR;
	    }

	    ast_push(ast, (base_t) { identifier, AST_FUNCTION, .f = f.d0 });
	}
	else if (LEXER_NEXT_IF(NAMESPACE)) {
	    
	}
	
	printf("Unexpected parser end\n");
	BREAK_ERROR;
    }

    if (error) {
        ast_destroy(ast);
	
	return 0;
    }
    else {
	return ast;
    }
}
