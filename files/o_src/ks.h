#ifndef KS_H
#define KS_H

#include <stddef.h>

#define VERSION "k-2.0"

#define STRING_OBJ(s) (obj_t){.type = STRING, .str_ptr = s}
#define ALLOCATED_STRING_OBJ(p) (obj_t){.type = ALLOCATED_STRING, .str_ptr = p}
#define INTEGER_OBJ(i) (obj_t){.type = INTEGER, .int_val = i}
#define NONE_OBJ (obj_t){.type = NONE}
#define BOOLEAN_OBJ(b) (obj_t){.type = BOOLEAN, .int_val = b}
#define FLOAT_OBJ(f) (obj_t){.type = FLOAT, .flt_val = f}

enum types {
    INTEGER,
    FLOAT,
    STRING,
    BOOLEAN,
    ALLOCATED_STRING,
    NONE
};

typedef struct {
    int type;
    union {
        int int_val;
        char *str_ptr;
        float flt_val;
    };
} obj_t;

// fcm.c
void f_clean_obj(obj_t obj);

obj_t f_print(int n, ...);
obj_t f_type(int n, obj_t a);
obj_t f_pass(int n, obj_t a);

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
