#ifndef _ERROR_H
#define _ERROR_H

#include "lexer.h"

/*
  Passing and managing and displaying errors as they relate to the 
  source 
 */

typedef struct error_s {
    bool   set;
    char * buffer;
    char * msg;

    bool   inspect;
    char * ptr;
    int    ln;
    int    cn;
    int    length;
} error_t;

error_t error_create(char * buffer);
void    error_set_msg(error_t * error, char * msg);
void    error_set_msg_inspect(error_t * error, char * msg, token_t * token);
void    error_print(error_t * e);

#endif
