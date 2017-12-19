#include <stdio.h>
#include "ast.h"

ast_t * ast_create() {
    ast_t * res = calloc(1, sizeof(ast_t));
    
    return res;
}

bool ast_push(ast_t * base, ast_t * next) {
    if (base == 0 || next == 0) {
	return false;
    }
    else {
	while (base->next != 0) {
	    base = base->next;
	}

	base->next = next;

	return true;
    }
}

void ast_destroy(ast_t * n) {
    if (n == 0)
	return;
    
    switch (n->type) {
    case AST_FUNC:
	ast_destroy(n->identifier);
	ast_destroy(n->signature);
	ast_destroy(n->body);
	break;
    case AST_SIGNATURE:
	ast_destroy(n->body);
	break;
    case AST_MATCH_BODY:
	ast_destroy(n->args);
	ast_destroy(n->body);
	break;
    case AST_EXPR:
	ast_destroy(n->body);
	break;
    default:
	break;
    }

    if (n->next != 0)
	ast_destroy(n->next);

    free(n);
}
