#include <string.h>
#include "analysis.h"

env_t * env_create() {
    env_t * res = malloc(sizeof(env_t));
    res->names = 0;
    
    return res;
}

void env_destroy(env_t * env) {
    while (env->names != 0) {
	entry_t * ptr = env->names->next;
	free(env->names);
	env->names = ptr;
    }
    
    free(env);
}

ast_t * env_get(env_t * env, char * name) {
    entry_t * ptr = env->names;

    while (ptr != 0 && strcmp(ptr->name, name) != 0)
	ptr = ptr->next;

    if (ptr == 0) {
	return 0;
    }
    else {
	return ptr->data;
    }
}

void env_set(env_t * env, char * name, ast_t * data) {
    if (env->names == 0) {
	env->names = malloc(sizeof(entry_t));
	env->names->name = name;
	env->names->data = data;
	env->names->next = 0;
    }
    else {
	entry_t * ptr = env->names;

	while (ptr->next != 0) ptr = ptr->next;

	ptr->next = malloc(sizeof(entry_t));
        ptr->next->name = name;
	ptr->next->data = data;
        ptr->next->next = 0;
    }
}

void env_unset(env_t * env, char * name) {
    if (env->names == 0)
	return;

    entry_t * last = 0;
    entry_t * ptr  = env->names;

    while (ptr != 0 && strcmp(ptr->name, name) != 0) {
	last = ptr;
	ptr  = ptr->next;
    }

    if (last == 0) {
	last = env->names->next;
	free(env->names);
	env->names = last;
    }
    else {
	ptr = ptr->next;
	free(last->next);
	last->next = ptr;
    }
}

ast_t * type_check(ast_t * ast, env_t * env) {
    if (ast == 0)
	return 0;

    switch (ast->type) {
    case AST_FUNC:
    case AST_NATIVE:
    case AST_IDENTIFIER:
    case AST_INTEGER:
    case AST_DO:
    case AST_SIGNATURE:
    case AST_TYPE:
    case AST_TYPE_EXPR:
    case AST_MATCH:
    case AST_MATCH_BODY:
    case AST_MATCH_EXPR_ARRAY:
    case AST_EXPR:
    case AST_APPLICATION:
    default:
	printf("TODO: typecheck type");
    };
	
    return 0;
}

ast_t * type_infer(ast_t * ast, env_t * env) {
    return 0;
}

ast_t * prepare(ast_t * ast, env_t * env) {
    ast_t * main = 0;

    /*
      TODO
      ----
      Typecheck
      Function constructors
      - Populate env with the available references in scope
      
     */
    
    // Find main
    for (ast_t * ptr = ast; ptr != 0; ptr = ptr->next)
	if (ptr->type == AST_FUNC && token_equal_str(ptr->identifier->value, "main"))
	    main = ptr;

    if (main == 0) {
	printf("ERROR: Slang program must contain a main function\n");

	return 0;
    }

    

    return 0;
}
