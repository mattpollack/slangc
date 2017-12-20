#include "error.h"

error_t error_create(char * buffer) {
    error_t res;
    res.set     = false;
    res.buffer  = buffer;
    res.msg     = 0;

    res.inspect = false;
    res.ptr     = 0;
    res.ln      = 0;
    res.cn      = 0;
    
    return res;
}

void error_set_msg(error_t * error, char * msg) {
    error->set = true;
    error->msg = msg;
}

void error_set_msg_inspect(error_t * error, char * msg, token_t * token) {
    error_set_msg(error, msg);
    error->inspect = true;
    error->ptr     = token->buffer;
    error->ln      = token->ln;
    error->cn      = token->cn;
}

void error_print(error_t * e) {
    if (e->inspect) {
	printf("ERROR [%d:%d] %s\n", e->ln, e->cn, e->msg);

	int    l   = 0;
	char * ptr = e->ptr;

	// Start from the error ptr, work backwards to find either 2
	// lines or the beginning of the src
	for (; l < 3 && ptr != e->buffer; --ptr) {
	    if (ptr[0] == '\n') {
		++l;
	    }
	}

	if (ptr != e->buffer) {
	    ptr += 2;
	    --l;
	}

	// Print the next two lines or until end of buffer
	for (; l >= 0 && ptr[0] != '\0'; ++ptr) {
	    if (ptr[0] == '\n') {
		printf("\n");
		--l;
	    }
	    else {
		printf("%c", ptr[0]);
	    }
	}

	// Print cursor
	for (l = 0; l < e->cn; ++l) printf(" ");
	
	printf("^\n");
    }
    else {
	printf("ERROR: %s\n", e->msg);
    }
}
