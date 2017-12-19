#include "error.h"
#include "parser.h"

parser_t * parser_create(char * raw) {
    parser_t * res = malloc(sizeof(parser_t));
    res->error = error_create(raw);
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

#define ERROR        parser->error.set
#define ERROR_SET(m) error_set_msg(&parser->error, m)
#define ERROR_EXIT					\
    if (ERROR) {					\
	ast_destroy(ast);				\
	return 0;					\
    }

ast_t * parse_integer(parser_t * parser) {
    if (LEXER_PEEK.type == INTEGER) {
	ast_t * ast = ast_create();
	ast->type   = AST_INTEGER;
	ast->value  = LEXER_NEXT;

	return ast;
    }
    else {
	ERROR_SET("Unexpected token when parsing integer");
	return 0;
    }
}

ast_t * parse_identifier(parser_t * parser) {
    if (LEXER_PEEK.type == IDENTIFIER) {
	ast_t * ast = ast_create();
	ast->type   = AST_IDENTIFIER;
	ast->value  = LEXER_NEXT;

	return ast;
    }
    else {
	ERROR_SET("Unexpected token when parsing identifier");
	return 0;
    }
}

ast_t * parse_expression(parser_t * parser, bool skip_end) {
    ast_t * ast = ast_create();
    ast->type = AST_EXPR;

    while (LEXER_PEEK.type != EXPR_END) LEXER_NEXT;
    
    if (!skip_end && !LEXER_NEXT_IF(EXPR_END)) {
	ERROR_SET("Expression must end with a semi-colon");
	ast_destroy(ast);
	return 0;
    }
    
    return ast;
}

ast_t * parse_match_body(parser_t * parser) {
    ast_t * ast = ast_create();
    ast->type = AST_MATCH_BODY;

    for (token_t peek = LEXER_PEEK;; peek = LEXER_PEEK) {
	ast_t * next = 0;

	/**/ if (peek.type == IDENTIFIER) {
	    next = parse_identifier(parser);
	}
	else if (peek.type == INTEGER) {
	    next = parse_integer(parser);
	}
	else {
	    break;
	}

	if (ERROR) {
	    ast_destroy(next);
	    ast_destroy(ast);

	    return 0;
	}
	else {
	    if (ast->args == 0) {
		ast->args = next;
	    }
	    else {
		ast_push(ast->args, next);
	    }
	}
    }

    if (LEXER_NEXT_IF(ARROW)) {
	ast->body = parse_expression(parser, false);

	if (ERROR) {
	    ast_destroy(ast);
	    return 0;
	}
    }
    else {
	ERROR_SET("Arrow must proceed match body arguments");
	ast_destroy(ast);
	return 0;
    }
    
    return ast;
}

ast_t * parse_signature(parser_t * parser, bool is_array) {
    ast_t * ast   = ast_create();
    ast->type     = AST_SIGNATURE;
    ast->is_array = false;
    
    for (token_t peek = LEXER_PEEK;; peek = LEXER_PEEK) {
	ast_t * next = 0;
	
	if (peek.type == IDENTIFIER) {
	    next = parse_identifier(parser);
	}
	else if (LEXER_NEXT_IF(OPEN_PAREN)) {
	    next = parse_signature(parser, false);
	    
	    if (!LEXER_NEXT_IF(CLOSE_PAREN)) {
		ERROR_SET("Function signature must end with a close paren");
	    }
	}
	else if (LEXER_NEXT_IF(OPEN_BRACKET)) {
	    next = parse_signature(parser, true);

	    if (!LEXER_NEXT_IF(CLOSE_BRACKET)) {
		ERROR_SET("Array signature must end with a close bracket");
	    }
	}
	else {
	    break;
	}

	if (ERROR) {
	    ast_destroy(next);
	    ast_destroy(ast);

	    return 0;
	}
	else {
	    if (ast->body == 0) {
		ast->body = next;
	    }
	    else {
		ast_push(ast->body, next);
	    }
	}

	if (is_array)
	    break;
    }
	    
    return ast;
}

ast_t * parse_func(parser_t * parser, bool skip_reserved) {
    if (!skip_reserved && !LEXER_NEXT_IF(FUNC)) {
	ERROR_SET("Expected token 'func' at the beginning of a function");
	return 0;
    }

    ast_t * ast     = ast_create();
    ast->type       = AST_FUNC;
    ast->identifier = parse_identifier(parser); ERROR_EXIT;
    ast->signature  = parse_signature(parser, false);  ERROR_EXIT;

    if (LEXER_NEXT_IF(OPEN_BRACE)) {
        while (!LEXER_NEXT_IF(CLOSE_BRACE)) {
	    ast_t * next = parse_match_body(parser);

	    if (ERROR) {
		ast_destroy(next);
		ast_destroy(ast);

		return 0;
	    }
	    
	    if (ast->body == 0) {
		ast->body = next;
	    }
	    else {
		ast_push(ast->body, next);
	    }
	}
    }
    else {
	ERROR_SET("Function body must begin with an open brace");
	ast_destroy(ast);
	
	return 0;
    }
    
    return ast;
}

ast_t * parser_parse(parser_t * parser) {
    ast_t * ast = ast_create();

    while (LEXER_PEEK.type != BUFFER_END) {
	if (LEXER_NEXT_IF(FUNC)) {
	    ast_push(ast, parse_func(parser, true));
	}
	else {
	    ERROR_SET("Unexpected token at base level");
	    break;
	}

	if (ERROR) break;
    }

    if (ERROR) {
	ast_destroy(ast);
	return 0;
    }
    else {
	return ast;
    }
}
