#include "ast.h"

/** MATCH **/

void match_body_destroy(match_body_t * m) {
    if (m == 0)
	return;
}

/** TYPE **/

void type_destroy(type_t * t) {
    if (t == 0)
	return;
    // ..
}

/** SIGNATURE **/

signature_t signature_create() {
    signature_t res;
    // ..
    
    return res;
}

void signature_destroy(signature_t * s) {
    if (s == 0)
	return;

    // ..
}
/** FUNC **/

func_t func_create() {
    func_t res;
    array_init(res.body);

    return res;
}

void func_destroy(func_t * f) {
    if (f == 0)
	return;
    
    for (int i = 0, s = array_size(f->body); i < s; ++i) {
	match_body_destroy(&array_get(f->body, i));
    }

    array_destroy(f->body);
}

/** BASE **/

base_t base_create() {
    base_t res;

    return res;
}

/** AST **/

ast_t * ast_create() {
    ast_t * res = malloc(sizeof(ast_t));
    array_init(res->nodes);
    
    return res;
}

void ast_destroy(ast_t * ast) {
    if (ast == 0)
	return;

    for (int i = 0, s = array_size(ast->nodes); i < s; ++i) {
	switch (array_get(ast->nodes, i).type) {
	case BASE_FUNC: func_destroy(&array_get(ast->nodes, i).f); break;
	case BASE_TYPE: type_destroy(&array_get(ast->nodes, i).t); break;
	default:
	    break;
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

void ast_print(ast_t * ast) {
    printf("-- AST PRINT --\n\n");
    printf("todo\n");
}
