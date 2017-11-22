#ifndef _AST_H
#define _AST_H

#include "util.h"
#include "lexer.h"

typedef struct namespace_s   {} namespace_t; // probably todo later


typedef struct application_s {} application_t;
typedef struct match_body_s  {} match_body_t;
typedef struct match_s       {} match_t;
typedef struct signature_s   {} signature_t;

// Function definition
typedef struct function_s {
    signature_t  signature;
    match_body_t body;
} function_t;

// Access control data types
typedef enum {
    AST_FUNCTION,
    AST_NAMESPACE,
} base_type;

// Access control struct
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
