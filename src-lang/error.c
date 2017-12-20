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

void error_print(error_t * e) {
    if (e->inspect) {

    }
    else {
	printf("ERROR: %s\n", e->msg);
    }
}
