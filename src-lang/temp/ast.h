#ifndef _AST_H
#define _AST_H

#include "util.h"
#include "lexer.h"

/** TYPE **/

typedef struct type_s {} type_t;

/** EXPRESSION **/

typedef struct expr_s {
    enum  {
	EXPR_APPLICATION,
	EXPR_LITERAL,
	EXPR_IDENTIFIER,
	// ...
    } type;
} expr_t;

expr_t expr_create();
void   expr_destroy(expr_t *);

/** MATCH **/

typedef struct match_expr_s {
    enum  {
	MATCH_EXPR_IDENTIFIER,
	MATCH_EXPR_LITERAL,
    } type;

    union {
	token_t identifier;
	token_t literal;
    };
} match_expr_t;

match_expr_t match_expr_create();
void         match_expr_destroy(match_expr_t *);

typedef struct match_body_s {
    expr_t                body;
    array_t(match_expr_t) args;
} match_body_t;

match_body_t match_body_create();
void         match_body_destroy(match_body_t *);

/** SIGNATURE **/

typedef struct signature_s {
    // ...
} signature_t;

signature_t signature_create();
void        signature_destroy(signature_t *);

/** FUNC **/

typedef struct func_s {
    token_t               identifier;
    signature_t           signature;
    array_t(match_body_t) body;
} func_t;

func_t func_create();
void   func_destroy(func_t *);

/** BASE **/

typedef struct base_s {
    enum  {
	BASE_FUNC,
	BASE_TYPE,
    } type;

    union {
	func_t f;
	type_t t;
    };
} base_t;

base_t base_create();
void   base_destroy();

/** AST **/

typedef struct ast_s {
    array_t(base_t) nodes;
} ast_t;

ast_t * ast_create();
void    ast_destroy(ast_t * ast);
int     ast_push(ast_t * ast, base_t node);
void    ast_print(ast_t * ast);

#endif
