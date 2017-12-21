#ifndef _ANALYSIS_H
#define _ANALYSIS_H

#include "ast.h"

typedef struct entry_s {
    struct entry_s * next;
    char           * name;
    ast_t          * data;
} entry_t;

typedef struct env_s {
    entry_t * names;
} env_t;

env_t * env_create();
void    env_destroy(env_t *);
ast_t * env_get  (env_t *, char *);
void    env_set  (env_t *, char *, ast_t *);
void    env_unset(env_t *, char *);

typedef ast_t * (* env_ast_transformer_t)(ast_t *, env_t *);

/*
  
  TODO
  typecheck
  undefined reference
  ... 

 */


#endif 
