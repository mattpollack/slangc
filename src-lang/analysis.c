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
