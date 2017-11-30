#ifndef _PARSER_H
#define _PARSER_H

#include "ast.h"
#include "lexer.h"
#include "util.h"

typedef struct {
    bool      error;
    char    * error_msg;
    char    * buffer;
    lexer_t * lexer;
} parser_t;

parser_t * parser_create(char * raw);
void       parser_destroy(parser_t * parser);
ast_t    * parser_parse(parser_t * parser);

#endif
