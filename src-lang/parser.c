#include <string.h>
#include "parser.h"
#include "lexer.h"

parser_t * parser_create(char * raw) {
    parser_t * res = malloc(sizeof(parser_t));
    res->error = false;
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

#define ERROR_SET(msg)				\
    parser->error = true;			\
    parser->error_msg = (msg)
#define ERROR_BREAK				\
    if (parser->error)				\
	break

static match_body_t parse_match_body(parser_t * parser) {
    match_body_t res;
    
    ERROR_SET("TODO: match_body");
    
    return res;
}

static signature_t * parse_signature(parser_t * parser) {
    signature_t * res = malloc(sizeof(signature_t));
    res->next = 0;

    if /**/ (LEXER_NEXT_IF(OPEN_PAREN)) {
	res->type = SIG_FUNC;
	res->body = 0;
        
	signature_t * ptr = 0;
	
	while (!LEXER_NEXT_IF(CLOSE_PAREN)) {
	    if (ptr == 0) {
		res->body = parse_signature(parser);
		ptr = res->body;
	    }
	    else {
		ptr->next = parse_signature(parser);
		ptr = ptr->next;
	    }

	    ERROR_BREAK;
	}

	if (parser->error) {
	    while (res->body != 0) {
		ptr = res->body->next;
		free(res->body);
		res->body = ptr;
	    }
	}
    }
    else if (LEXER_NEXT_IF(OPEN_BRACKET)) {
	res->type = SIG_LIST;
	res->body = parse_signature(parser);
	
	if (!parser->error && !LEXER_NEXT_IF(CLOSE_BRACKET)) {
	    ERROR_SET("List signature must end with a close bracket");
	}
    }
    else if (LEXER_PEEK.type == IDENTIFIER) {
	res->type = SIG_IDENTIFIER;
	res->identifier = LEXER_NEXT;
    }
    else {
	ERROR_SET("Unexpected token when parsing signature");
    }

    if (parser->error) {
	free(res);
	return 0;
    }

    res->option = LEXER_NEXT_IF(OPTION);
    
    return res;
}

static function_t parse_function(parser_t * parser) {
    function_t res;
    res.signature = parse_signature(parser);

    if (parser->error)
	return res;

    res.body = parse_match_body(parser);

    return res;
}

ast_t * parser_parse(parser_t * parser) {
    ast_t * ast = ast_create();

    while (!LEXER_NEXT_IF(BUFFER_END) && !parser->error) {
	base_t node;
	
	if /**/ (LEXER_NEXT_IF(FUNC)) {
	    if (LEXER_PEEK.type != IDENTIFIER) {
		ERROR_SET("Expected identifier");
		break;
	    }
	    
	    node.identifier = LEXER_NEXT;
	    node.type       = AST_FUNCTION;
	    node.f          = parse_function(parser);
	}
	else {
	    ERROR_SET("Unexpected token at base level");
	}

	ERROR_BREAK;

	ast_push(ast, node);
    }

    if (parser->error) {
	ast_destroy(ast);
	
	return 0;
    }
    else {
	return ast;
    }
}
