#include "ast.h"

ast_t * ast_create() {
    ast_t * res = malloc(sizeof(ast_t));
    array_init(res->nodes);
    
    return res;
}

void ast_destroy_expression(expression_t * e) {
    if (e->type == EXPR_APPLICATION) {
	for (int i = 0, l = array_size(e->application); i < l; ++i) {
	    ast_destroy_expression(&array_get(e->application, i));
	}
	array_destroy(e->application);
    }
}

void ast_destroy_match_body(match_body_t * m) {
    array_destroy(m->args);
    ast_destroy_expression(&m->body);
}

void ast_destroy_signature(signature_t * s) {
    switch (s->type) {
    case SIG_IDENTIFIER: break;
    case SIG_LIST:       ast_destroy_signature(s->body); break;
    case SIG_FUNC:
	{
	    signature_t * ptr  = s->body;
	    signature_t * next = 0;
	    
	    while (ptr != 0) {
		next = ptr->next;
		ast_destroy_signature(ptr);
		ptr = next;
	    }
	}
    }

    free(s);
}

void ast_destroy_function(function_t * f) {
    ast_destroy_signature(f->signature);

    for (int i = 0, l = array_size(f->body); i < l; ++i) {
	ast_destroy_match_body(&array_get(f->body, i));
    }

    array_destroy(f->body);
}

void ast_destroy(ast_t * ast) {
    if (ast == 0) return;
    
    for (int i = 0, l = array_size(ast->nodes); i < l; ++i) {
	base_t b = array_get(ast->nodes, i);
	
	switch (b.type) {
	case AST_FUNCTION:
	    ast_destroy_function(&b.f);
	}
    }
    
    array_destroy(ast->nodes);
    free(ast);
}

int ast_push(ast_t * ast, base_t node) {
    array_push(base_t, ast->nodes, node);
    
    return array_size(ast->nodes);
}

/** AST PRINT **/

static void print_tab(int tab) {
    while (tab > 0) {
	printf("  ");
	--tab;
    }
}

#define TAB print_tab(tab)
#define NL  printf("\n")

void ast_print_match_body(int tab, match_body_t * node) {
    TAB;
    for (int i = 0, l = array_size(node->args); i < l; ++i) {
	printf("TODO ");
    }
    NL;
}

void ast_print_sig(signature_t * node) {
    switch (node->type) {
    case SIG_IDENTIFIER:
	token_print(node->identifier);
	break;
    case SIG_LIST:

	printf("[ ");
	ast_print_sig(node->body);
	printf(" ]");
	
	break;
    case SIG_FUNC:
	printf("( ");
	signature_t * ptr = node->body;
	
	while (ptr != 0) {
	    ast_print_sig(ptr);
	    printf(" ");
	    ptr = ptr->next;
	}
	
	printf(")");
	break;
    }
}

void ast_print_func(int tab, function_t * node) {
    TAB; printf("sig: ");
    ast_print_sig(node->signature);
    NL;
    TAB; printf("body: \n");
    
    for (int i = 0, l = array_size(node->body); i < l; ++i) {
	ast_print_match_body(tab + 1, &array_get(node->body, i));
    }
}

void ast_print_base(int tab, base_t * node) {
    TAB; token_print(node->identifier);

    switch(node->type) {
    case AST_FUNCTION:
	printf(": func\n");
	ast_print_func(tab + 1, &node->f);
    }
}

void ast_print(ast_t * ast) {
    if (ast == 0) return;
    
    printf("-- AST PRINT --\n\n");

    for (int i = 0, l = array_size(ast->nodes); i < l; ++i) {
	ast_print_base(0, &array_get(ast->nodes, i));
    }

    NL;
}
