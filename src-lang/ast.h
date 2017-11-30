#ifndef _AST_H
#define _AST_H

#include "util.h"
#include "lexer.h"

typedef struct application_s {} application_t;
typedef struct match_body_s  {
    
} match_body_t;

typedef enum {
    SIG_IDENTIFIER,
    SIG_LIST,
    SIG_FUNC
} sig_type;

typedef struct signature_s {
    sig_type             type;
    bool                 option;
    struct signature_s * next;
    
    union {
	token_t              identifier;
	struct signature_s * body;
    };
} signature_t;

// Function definition
typedef struct function_s {
    signature_t  * signature;
    match_body_t   body;
} function_t;

// Base node types
typedef enum {
    AST_FUNCTION,
} base_type;

// Access control struct
typedef struct base_s {
    token_t   identifier;
    base_type type;
    
    union {
	function_t  f;
    };
} base_t;

typedef struct ast_s {
    array_t(base_t) nodes;
} ast_t;

ast_t * ast_create();
void    ast_destroy(ast_t * ast);
int     ast_push(ast_t * ast, base_t node);

#endif
