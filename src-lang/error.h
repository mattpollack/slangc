#ifndef _ERROR_H
#define _ERROR_H

#include "lexer.h"

/*
  Passing an managing and displaying errors as they relate to the 
  source 
 */

typedef struct error_s {
    bool   set;
    char * msg;
    char * buffer;
    char * ptr;
    int    ln;
    int    cn;
} error_t;

error_t error_create(token_t * t, char * buffer, char * msg) {
    error_t res;
    res.set    = true;
    res.msg    = msg;
    res.buffer = buffer;
    res.ptr    = t->buffer;
    res.ln     = t->ln;
    res.cn     = t->cn;
    
    return res;
}

void error_print(error_t * e) {
    printf("%d:%d: %s\n", e->ln, e->cn, e->msg);
    
    char * ptr = e->ptr;
    int l;
    
    for (l = 0; ptr != e->buffer; --ptr) {
	if (ptr[0] == '\n') {
	    if (l > 0) {
		++ptr;
		
		break;
	    }
	    else {
		++l;
	    }
	}
    }

    for (l = 0; l <= 1; ++ptr) {
	if (ptr[0] == '\n')
	    ++l;

	if (ptr[0] == '\0')
	    break;
	
	printf("%c", ptr[0]);
    }

    for (l = 0; l < e->cn; ++l) {
	printf(" ");
    }

    printf("^\n");
}

#endif
