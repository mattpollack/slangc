#include <stdio.h>
#include "ast.h"

ast_t * ast_create() {
    ast_t * res = calloc(1, sizeof(ast_t));
    
    return res;
}

bool ast_push(ast_t ** base, ast_t * next) {
    if (next == 0) {
	return false;
    }
    else if (*base == 0) {
	*base = next;
    }
    else {
	ast_t * ptr = *base;
	
	while (ptr->next != 0) {
	    ptr = ptr->next;
	}

	ptr->next = next;

	return true;
    }
    
    return true;
}


bool ast_equal(ast_t * a, ast_t * b) {
    if (a == b)
	return true;
    
    if (a == 0 || b == 0)
	return false;

    if (a->type != b->type)
	return false;

    bool result = false;
    
    switch (a->type) {
    case AST_FUNC:
	result =
	    ast_equal(a->body,      b->body) &&
	    ast_equal(a->signature, b->signature);
	break;
    case AST_SIGNATURE:
	result = ast_equal(a->body, b->body);
	break;
    case AST_MATCH_BODY:
	result =
	    ast_equal(a->args, b->args) &&
	    ast_equal(a->body, b->body);
	break;
    case AST_EXPR:
	result = true;
	break;
    default:
	printf("AST_EQUAL: undefined type, default is false");
    }

    return result && ast_equal(a->next, b->next);
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

    ast_destroy(n->next);
    free(n);
}

void print_tab(int tab) {
    for (; tab > 0; --tab) {
	printf("  ");
    }
}

void ast_print(ast_t * ast, int tab) {
    for (; ast != 0; ast = ast->next) {
	switch (ast->type) {
	case AST_INTEGER:
	case AST_IDENTIFIER:
	    print_tab(tab);
	    token_print(ast->value);
	    printf("\n");
	    break;

	case AST_FUNC:
	    print_tab(tab); printf("FUNC {\n");
	    ast_print(ast->signature, tab + 1);
	    ast_print(ast->body, tab + 1);
	    print_tab(tab); printf("}\n");
	    break;
	    
	case AST_MATCH_BODY:
	    print_tab(tab); printf("MATCH_BODY {\n");
	    ast_print(ast->args, tab + 1);
	    ast_print(ast->body, tab + 1);
	    print_tab(tab); printf("}\n");
	    break;
	    
	case AST_SIGNATURE:
	    print_tab(tab);
	    
	    if (ast->is_array)
		 printf("A: \n");
	    else printf("S: \n");

	    ast_print(ast->body, tab + 1);
	    break;
	    
	case AST_EXPR:
	    print_tab(tab); printf("EXPRESSION {\n");
	    ast_print(ast->body, tab + 1);
	    print_tab(tab); printf("}\n");
	    break;
	    
	case AST_TYPE:
	case AST_TYPE_EXPR:
	case AST_MATCH:
	case AST_MATCH_EXPR_ARRAY:
	case AST_APPLICATION:
	default:
	    print_tab(tab);
	    printf("TODO print node of this type\n");
	}
    }
}
