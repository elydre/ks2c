#ifndef KS_H
#define KS_H

#include <stddef.h>

#define VERSION "k-2.0"

#define STRING_OBJ(s) (obj_t){STRING, 0, s}
#define INTEGER_OBJ(i) (obj_t){INTEGER, i, NULL}
#define NONE_OBJ (obj_t){NONE, 0, NULL}

enum types {
    INTEGER,
    STRING,
    BOOLEAN,
    ALLOCATED_STRING,
    NONE
};

typedef struct {
    int type;
    int int_val;
    char *string_ptr;
} obj_t;

// fcm.c
obj_t f_print(int n, ...);

obj_t f_not(int n, obj_t a);
obj_t f_eql(int n, obj_t a, obj_t b);
obj_t f_neq(int n, obj_t a, obj_t b);
obj_t f_sup(int n, obj_t a, obj_t b);
obj_t f_inf(int n, obj_t a, obj_t b);
obj_t f_and(int n, obj_t a, obj_t b);
obj_t f_or(int n, obj_t a, obj_t b);

obj_t f_mul(int n, obj_t a, obj_t b);
obj_t f_edv(int n, obj_t a, obj_t b);
obj_t f_add(int n, obj_t a, obj_t b);
obj_t f_sub(int n, obj_t a, obj_t b);
obj_t f_mod(int n, obj_t a, obj_t b);

#endif
