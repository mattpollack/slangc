#include "lexer.h"
#include <stdlib.h>
#include <stdio.h>

void token_print(token_t token) {
    switch (token.type) {
    case ERROR:
	printf("%s [l:%d c:%d]", token.buffer, token.ln, token.cn);
	break;
	
    case BUFFER_START: printf("START");             break;
    case BUFFER_END:   printf("END");               break;
    case NAMESPACE:    printf("NAMESPACE");         break;
    case FUNC:         printf("FUNC");              break;
    case TYPE:         printf("TYPE");              break;
    case DEF:          printf("DEF");               break;
    case LET:          printf("LET");               break;
    case IN:           printf("IN");                break;
    case IF:           printf("IF");                break;
    case EL:           printf("EL");                break;
	
    case INTEGER:
    case IDENTIFIER:
	if (token.type == IDENTIFIER)
	    printf("@");
	while (token.length > 0) {
	    printf("%c", *token.buffer);
	    --token.length;
	    ++token.buffer;
	}
	break;

    case OPEN_PAREN:   printf("("); break;
    case CLOSE_PAREN:  printf(")"); break;
    case OPEN_BRACE:   printf("{"); break;
    case CLOSE_BRACE:  printf("}"); break;
    case OPEN_BRACKET: printf("["); break;
    case CLOSE_BRACKET:printf("]"); break;
    case VBAR:         printf("|"); break;
    case OPTION:       printf("?"); break;
    case ARROW:        printf("->"); break;
	
    case UNDERSCORE:   printf("_"); break;
    case EXPR_END:     printf(";"); break;
	
    case EQUAL:        printf("="); break;
    case CONCAT:       printf("++"); break;
    case ADD:          printf("+"); break;
    case SUB:          printf("-"); break;
    case MUL:          printf("*"); break;
    case DIV:          printf("/"); break;
    case GRE:          printf(">="); break;
    case GR:           printf(">"); break;
    case LEE:          printf("<="); break;
    case LE:           printf("<"); break;
	
    default:
	printf("/*NEEDS DEF*/");
	break;
    }
}

bool token_equal(token_t a, token_t b) {
    if (a.length == b.length) {
	for (int i = 0; i < a.length; ++i)
	    if (a.buffer[i] != b.buffer[i])
		return false;

	return true;
    }

    return false;
}

typedef struct {
    token_type  type;
    char       *string;
} token_type_t;

static token_type_t reserved_list[] = {
    {.type = NAMESPACE,      .string = "NAMESPACE"},
    {.type = FUNC,           .string = "func"},
    {.type = TYPE,           .string = "type"},
    {.type = DEF,            .string = "def"},
    {.type = LET,            .string = "let"},
    {.type = IF,             .string = "if"},
    {.type = EL,             .string = "el"},
    {.type = MATCH,          .string = "match"},

    // end of token list
    {.type = TOKEN_LIST_END, .string = "\0"},
};

static token_type_t token_list[] = {
    {.type = CONCAT,         .string = "++"},
    {.type = GRE,            .string = ">="},
    {.type = LEE,            .string = "<="},
    {.type = ARROW,          .string = "->"},
    
    {.type = IN,             .string = "in"},
    
    {.type = OPEN_PAREN,     .string = "("},
    {.type = CLOSE_PAREN,    .string = ")"},
    
    {.type = OPEN_BRACE,     .string = "{"},
    {.type = CLOSE_BRACE,    .string = "}"},
    
    {.type = OPEN_BRACKET,   .string = "["},
    {.type = CLOSE_BRACKET,  .string = "]"},
    {.type = VBAR,           .string = "|"},
    {.type = OPTION,         .string = "?"},
    
    {.type = UNDERSCORE,     .string = "_"},
    {.type = EXPR_END,       .string = ";"},
    
    {.type = EQUAL,          .string = "="},
    {.type = ADD,            .string = "+"},
    {.type = SUB,            .string = "-"},
    {.type = MUL,            .string = "*"},
    {.type = DIV,            .string = "/"},
    {.type = GR,             .string = ">"},
    {.type = LE,             .string = "<"},
    
    // end of token list
    {.type = TOKEN_LIST_END, .string = "\0"},
};

lexer_t * lexer_create() {
    lexer_t * res = malloc(sizeof(lexer_t));
    res->token.type = BUFFER_START;
    res->token.buffer = 0;
    res->token.ln = 1;
    res->token.cn = 1;
    res->token.length = 0;
    res->buffer = 0;
    res->ln = 1;
    res->cn = 1;

    return res;
}

void lexer_destroy(lexer_t * lexer) {
    free(lexer);
}

#define WS(c)     (c == ' '   ||  \
	           c == '\n'  ||  \
	           c == '\t')
#define DIGIT(c)  (c >= '0'   &&  \
		   c <= '9')
#define ALPHA(c) ((c >= 'a'   &&  \
		   c <= 'z')  ||  \
		  (c >= 'A'   &&  \
		   c <= 'Z'))

static int str_cmp(char * a, char * b) {
    char * begin = a;
    
    while (*a != '\0') {
	if (*b == '\0' ||
	    *a != *b) {
	    return 0;
	}
	++a;
	++b;
    }

    return a - begin;
}

token_t lexer_next(lexer_t * lexer) {
 BEGIN:
    // Skip WS
    while (WS(*lexer->buffer)) {
	if (*lexer->buffer == '\n') {
	    lexer->cn = 1;
	    ++lexer->ln;
	}
	else {
	    ++lexer->cn;
	}

	++lexer->buffer;
    }

    if (*lexer->buffer == '\0') {
	token_t res;
	res.type = BUFFER_END;
	res.buffer = lexer->buffer;
	res.ln = lexer->ln;
	res.cn = lexer->cn;
	res.length = 0;

	return (lexer->token = res);
    }

    { // Reserved
	token_type_t * ptr = reserved_list;

	while (ptr->type != TOKEN_LIST_END) {
	    int parsed = str_cmp(ptr->string, lexer->buffer);
	    
	    if (parsed > 0) {
		token_t res;
		res.type = ptr->type;
		res.buffer = lexer->buffer;
		res.ln = lexer->ln;
		res.cn = lexer->cn;
		res.length = parsed;

		lexer->buffer += parsed;
		lexer->cn += parsed;

		return res;
	    }
	    
	    ++ptr;
	}
    }

    // Identifier
    if (ALPHA(*lexer->buffer)) {
	char * start = lexer->buffer;
	char * ptr   = lexer->buffer + 1;

	int c = lexer->cn;
	
	while (ALPHA(*ptr) ||
	       DIGIT(*ptr) ||
	       *ptr == '_') {
	    ++ptr;
	    ++lexer->cn;
	}

	token_t res;
	res.type = IDENTIFIER;
	res.buffer = start;
	res.ln = lexer->ln;
	res.cn = c;
	res.length = ptr - start;

	lexer->buffer = ptr;

	return (lexer->token = res);
    }

    // Literal integer
    if (DIGIT(*lexer->buffer)) {
	char * start = lexer->buffer;
	char * ptr   = lexer->buffer;

	int c = lexer->cn;

	while (DIGIT(*ptr)) {
	    ++ptr;
	    ++lexer->cn;
	}

	token_t res;
	res.type = INTEGER;
	res.buffer = start;
	res.ln = lexer->ln;
	res.cn = c;
	res.length = ptr - start;

	lexer->buffer = ptr;

	return (lexer->token = res);
    }

    { // Operator
	token_type_t * ptr = token_list;

	while (ptr->type != TOKEN_LIST_END) {
	    int parsed = str_cmp(ptr->string, lexer->buffer);
	    
	    if (parsed > 0) {
		token_t res;
		res.type = ptr->type;
		res.buffer = lexer->buffer;
		res.ln = lexer->ln;
		res.cn = lexer->cn;
		res.length = parsed;

		lexer->buffer += parsed;
		lexer->cn += parsed;

		return (lexer->token = res);
	    }
	    
	    ++ptr;
	}
    }

    { // Comments
	if (*lexer->buffer == '#') {
	    while (*lexer->buffer != '\0' &&
		   *lexer->buffer != '\n') ++lexer->buffer;
	    goto BEGIN;
	}
    }

    token_t error;
    error.type = ERROR;
    error.buffer = "Unable to lex token";
    error.ln = lexer->ln;
    error.cn = lexer->cn;
    error.length = 0;

    return (lexer->token = error);
}

bool lexer_next_if(lexer_t * lexer, token_type t) {
    if (lexer_peek(lexer).type == t) {
	lexer_next(lexer);
	return true;
    }

    return false;
}

token_t lexer_peek(lexer_t * lexer) {
    lexer_t saved = *lexer;
    token_t token = lexer_next(lexer);
    *lexer = saved;

    return token;
}
