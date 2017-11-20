#include "ast.h"

ast_t * ast_create() {
    ast_t * res = malloc(sizeof(ast_t));
    array_init(res->nodes);
    
    return res;
}

void ast_destroy(ast_t * ast) {
    array_destroy(ast->nodes);
    free(ast);
}

int ast_push(ast_t * ast, base_t node) {
    array_push(base_t, ast->nodes, node);
    
    return array_size(ast->nodes);
}
