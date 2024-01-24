/******************************************
 *         _             _               *
 *    ___ | | _   _   __| | _ __   ___   *
 *   / _ \| || | | | / _` || '__| / _ |  *
 *  |  __/| || |_| || (_| || |   |  __/  *
 *   \___||_| \__, | \__,_||_|    \___|  *
 *            |___/                      *
 *  ___________________________________  *
 *                                       *
 *   - langage : C                       *
 *   - GitHub  : github.com/elydre       *
 *   - License : GNU GPL v3              *
******************************************/

#ifndef KS_H
#define KS_H

#include <stddef.h>

#define VERSION "k-2.2"

#define STRING_OBJ(s) (obj_t){.type = STRING, .str_ptr = s}
#define ALLOCATED_STRING_OBJ(p) (obj_t){.type = ALLOCATED_STRING, .str_ptr = p}
#define INTEGER_OBJ(i) (obj_t){.type = INTEGER, .int_val = i}
#define NONE_OBJ (obj_t){.type = NONE}
#define BOOLEAN_OBJ(b) (obj_t){.type = BOOLEAN, .int_val = b}
#define FLOAT_OBJ(f) (obj_t){.type = FLOAT, .flt_val = f}

enum types {
    NONE,
    INTEGER,
    FLOAT,
    STRING,
    BOOLEAN,
    ALLOCATED_STRING
};

typedef struct {
    int type;
    union {
        int int_val;
        char *str_ptr;
        float flt_val;
    };
} obj_t;

typedef struct {
    obj_t *arr;
    int len;
} vars_t;

// tools.c
void  fi_clean_obj(obj_t obj);
void  fi_clean_up(vars_t *vars);

void  fi_create_var(vars_t *vars, int var_id, obj_t o);
obj_t fi_get_var(vars_t *vars, int var_id);

int fi_is(obj_t o);
int fi_int_val(obj_t o);

// fcm.c
obj_t f_print(int n, ...);
obj_t f_type(int n, obj_t a);
obj_t f_pass(int n, obj_t a);

obj_t f_sub(int n, obj_t a, obj_t b);
obj_t f_add(int n, obj_t a, obj_t b);
obj_t f_mul(int n, obj_t a, obj_t b);
obj_t f_mod(int n, obj_t a, obj_t b);
obj_t f_edv(int n, obj_t a, obj_t b);

obj_t f_eql(int n, obj_t a, obj_t b);
obj_t f_neq(int n, obj_t a, obj_t b);
obj_t f_inf(int n, obj_t a, obj_t b);
obj_t f_sup(int n, obj_t a, obj_t b);

obj_t f_not(int n, obj_t a);
obj_t f_or(int n, obj_t a, obj_t b);
obj_t f_and(int n, obj_t a, obj_t b);

#endif