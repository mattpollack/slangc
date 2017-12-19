#ifndef _AST_H
#define _AST_H

#include "lexer.h"

/* Global enum union style ast node
 */
typedef struct ast_s {
    enum  {
	AST_IDENTIFIER,
	AST_INTEGER,
	
	AST_FUNC,
	
	AST_SIGNATURE,

	AST_TYPE,
	AST_TYPE_EXPR,

	AST_MATCH,
        AST_MATCH_BODY,
        AST_MATCH_EXPR_ARRAY,

	AST_EXPR,
	AST_APPLICATION,
    } type;
    
    struct ast_s * next;
    
    union {
	// identifier, literal
	token_t value;

	// signature
	bool is_array;
	
	// func, type
	struct {
	    // func, type, match_body
	    struct ast_s * body;

	    union {
		// match_body
		struct ast_s * args;
		
		struct {
		    // func, type
		    struct ast_s * identifier;

		    // func
		    struct ast_s * signature;
		};
	    };
	};
    };
} ast_t;

ast_t * ast_create();
bool    ast_push(ast_t *, ast_t *);
void    ast_destroy(ast_t *);

#endif

/*
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

*/
