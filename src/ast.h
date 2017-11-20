#ifndef _AST_H
#define _AST_H

#include "util.h"
#include "lexer.h"

// TODO
typedef struct application_s {} application_t;
typedef struct signature_s   {} signature_t;
typedef struct function_s    {} function_t;

typedef struct namespace_s   {} namespace_t;

typedef enum {
    AST_FUNCTION,
    AST_NAMESPACE,
} base_type;

typedef struct base_s {
    token_t   identifier;
    base_type type;
    
    union {
	function_t  f;
	namespace_t n;
    };
} base_t;

typedef struct ast_s {
    array_t(base_t) nodes;
} ast_t;

ast_t * ast_create();
void    ast_destroy(ast_t * ast);
int     ast_push(ast_t * ast, base_t node);

#endif
