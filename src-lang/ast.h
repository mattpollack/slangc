#ifndef _AST_H
#define _AST_H

#include "util.h"
#include "lexer.h"

typedef struct expression_s {
    /*
      THE HARDEST PART
      ----------------
      appl expr expr...
      (expr)
      integer
      float
      string
      

     */
    enum  {
	EXPR_APPLICATION,
	EXPR_IDENTIFIER,
	EXPR_L_INTEGER,
    } type;

    union {
	/* application */
	array_t(struct expression_s) application;
	token_t                      identifier;
	token_t                      integer;
    };
} expression_t;

typedef struct match_expr_s {
    /*
      TYPES
      -----
      x
      [x:y: ... :zs]
      any literal value NOTE: lexer only parses integers
      
      
     */
    enum  {
	MATCH_EXPR_IDENTIFIER,
	MATCH_EXPR_L_INTEGER,
    } type;
    union {
	token_t identifier;
	token_t integer;
    };
} match_expr_t;

typedef struct match_body_s  {
    /*
      args: [match_expr]
      body: expr
     */
    array_t(match_expr_t) args;
    expression_t          body;
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
    signature_t           * signature;
    array_t(match_body_t)   body;
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
void    ast_print(ast_t * ast);

#endif
