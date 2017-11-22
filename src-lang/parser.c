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

#define PARSER_RET(d) (__r_t__) {.type=CHOICE_0,.d0=(d)}
#define PARSER_MSG(m) (__r_t__) {.type=CHOICE_1,.d1=(m)}

// TODO begin
PARSER_F(namespace,   { return PARSER_MSG("TODO parse namespace"); });
PARSER_F(application, { return PARSER_MSG("TODO parse application"); });
PARSER_F(match,       { return PARSER_MSG("TODO parse match"); });
// TODO end

PARSER_F(
    match_body, {
	return PARSER_MSG("TODO parse match body");
    });

PARSER_F(
    signature, {
	return PARSER_MSG("TODO parse signature");
    });

PARSER_F(
    function, {
	if (LEXER_PEEK.type != OPEN_PAREN) {
	    return PARSER_MSG("Expected open paren to begin signature");
	}
	
	AUTO(signature, parse_signature(parser));
	
	if (is_error(signature)) {
	    return PARSER_MSG(signature.d1);
	}

	// switch on nature of body
	// assume only match body for now
	
	AUTO(body, parse_match_body(parser));

	if (is_error(body)) {
	    return PARSER_MSG(body.d1);
	}
	
	return PARSER_RET(((function_t) { signature.d0, body.d0 }));
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
	    if (LEXER_PEEK.type != IDENTIFIER) {
		printf("Expected identifier\n");
		BREAK_ERROR;
	    }

	    token_t identifier = LEXER_NEXT;

	    AUTO(n, parse_namespace(parser));

	    if (is_error(n)) {
		printf("%s", n.d1);
		BREAK_ERROR;
	    }

	    ast_push(ast, (base_t) { identifier, AST_NAMESPACE, .n = n.d0 });
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
