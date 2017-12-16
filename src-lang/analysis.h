#ifndef _ANALYSIS_H
#define _ANALYSIS_H

#include "ast.h"

/*
  ANALYSIS
  --------
  type checking
   - arg types
   - match_expr types
  pattern checking
   - runtime list size
   - exhaustion
  undefined refs
  compile time evaluation on literals

 */

typedef struct analyser_params_s {
    // ..
} analyser_params_t;

typedef struct analyzer_s {
    analyser_params_t   params;
    ast_t             * ast;
    bool                error;
    char              * error_msg;
} analyser_t;

#endif 