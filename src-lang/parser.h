#ifndef _PARSER_H
#define _PARSER_H

#include "error.h"
#include "ast.h"
#include "lexer.h"
#include "util.h"

typedef struct {
    error_t   error;
    char    * buffer;
    lexer_t * lexer;
} parser_t;

parser_t   * parser_create(char * raw);
void         parser_destroy(parser_t * parser);
ast_t      * parser_parse(parser_t * parser);

#endif
