#ifndef _LEXER_H
#define _LEXER_H

#include "util.h"

typedef enum {
    // Lexer
    TOKEN_LIST_END,
    BUFFER_START,
    BUFFER_END,
    ERROR,

    // Reserved
    NAMESPACE,
    FUNC,
    LET,
    IN,
    IF,
    EL,
    DEF,
    MATCH,
    
    // Dynamic
    INTEGER,
    IDENTIFIER,
    
    // Structure
    OPEN_PAREN,    // (
    CLOSE_PAREN,   // )
    OPEN_BRACE,    // {
    CLOSE_BRACE,   // }
    OPEN_BRACKET,  // [
    CLOSE_BRACKET, // ]
    
    VBAR,          // |
    OPTION,        // ?
    ARROW, // ->

    // Special
    UNDERSCORE, // pattern matching,
                // partial application
    
    // Binary infix
    EQUAL,
    CONCAT,
    ADD,
    SUB,
    MUL,
    DIV,
    GRE,
    GR,
    LEE,
    LE,
} token_type;

typedef struct {
    token_type  type;
    char       *buffer;
    int         ln; // line #
    int         cn; // char #
    int         length;
} token_t;

void token_print(token_t token);

typedef struct lexer_s {
    token_t         token;
    char           *buffer;
    int             ln; // line #
    int             cn; // char #
} lexer_t;

lexer_t *lexer_create();
void     lexer_destroy(lexer_t * lexer);
token_t  lexer_next(lexer_t * lexer);
bool     lexer_next_if(lexer_t * lexer, token_type t);
token_t  lexer_peek(lexer_t * lexer);

#endif
