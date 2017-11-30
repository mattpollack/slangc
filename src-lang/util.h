#ifndef _UTIL_H
#define _UTIL_H

#include <stdlib.h>
#include <stdio.h>

#define option_t(T)				\
    struct {					\
	bool set;				\
	T    data;				\
    }

#define choice_t(T0, T1)			\
    struct {					\
	enum {					\
	    CHOICE_0,				\
	    CHOICE_1				\
	} type;					\
	union {					\
	    T0 d0;				\
	    T1 d1;				\
	};					\
    }

// Typeless
#define AUTO(n, c)   typeof((c)) n = (c);
#define AUTO_CAST(c) (typeof((c)))

// Misc
#define error_t(type)       choice_t(type, char*)
#define error_data(c, data) AUTO_CAST(c) {.type=CHOICE_0,.d0=(data)}
#define error_msg(c, msg)   AUTO_CAST(c) {.type=CHOICE_1,.d1=(msg)}
#define is_error(e)         (e.type==CHOICE_1)

#define true                            1
#define false                           0
#define bool                            char

#define ARRAY_DEFAULT_SIZE              8
#define array_t(type)                   struct { type * ptr; int max, at; }
#define array_init(a)                   ((a).at = (a).max = 0, (a).ptr = 0)
#define array_destroy(a)                if ((a).ptr) free((a).ptr)
#define array_push(type, a, v)          {   if ((a).at == (a).max) {                                            \
                                                (a).max = (a).max ? (a).max << 1 : ARRAY_DEFAULT_SIZE;          \
                                                (a).ptr = (type *) realloc((a).ptr, sizeof(type) * (a).max);    \
                                            }                                                                   \
                                            (a).ptr[(a).at++] = (v);                                            }
#define array_get(a, i)                 ((a).ptr[i])
#define array_size(a)                   ((a).at)
#define array_ptr(a)                    ((a).ptr)

#endif//_UTIL_H
