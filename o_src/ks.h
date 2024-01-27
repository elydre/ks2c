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

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

#define VERSION "2.3"

#ifndef UNUSED
#define UNUSED(x) (void)(x)
#endif

enum types {
    NONE,
    INTEGER,
    FLOAT,
    STRING,
    BOOLEAN,
    ALLOCATED_STRING
};

typedef struct {
    char type;
    union {
        int int_val;
        char *str_ptr;
        float flt_val;
    };
    int ref_count;
} obj_t;

typedef struct {
    obj_t **arr;
    int len;
} vars_t;

// tools.c
extern obj_t NONE_OBJ;

void   fi_clean_obj(obj_t *obj);
void   fi_clean_up(vars_t *vars);

void   fi_create_var(vars_t *vars, int var_id, obj_t *o);
obj_t *fi_get_var(vars_t *vars, int var_id);

int fi_is(obj_t *o);
int fi_int_val(obj_t *o);

obj_t *fi_new_string_obj(char *s);
obj_t *fi_new_allocated_string_obj(char *p);
obj_t *fi_new_integer_obj(int i);
obj_t *fi_new_boolean_obj(int b);
obj_t *fi_new_float_obj(float f);

// fcm.c
obj_t *f_print(int n, ...);
obj_t *f_type(int n, obj_t *a);
obj_t *f_pass(int n, obj_t *a);

obj_t *f_int(int n, obj_t *a);
obj_t *f_str(int n, obj_t *a);
obj_t *f_float(int n, obj_t *a);

obj_t *f_sub(int n, obj_t *a, obj_t *b);
obj_t *f_add(int n, obj_t *a, obj_t *b);
obj_t *f_mul(int n, obj_t *a, obj_t *b);
obj_t *f_mod(int n, obj_t *a, obj_t *b);
obj_t *f_div(int n, obj_t *a, obj_t *b);

obj_t *f_eql(int n, obj_t *a, obj_t *b);
obj_t *f_neq(int n, obj_t *a, obj_t *b);
obj_t *f_inf(int n, obj_t *a, obj_t *b);
obj_t *f_sup(int n, obj_t *a, obj_t *b);

obj_t *f_not(int n, obj_t *a);
obj_t *f_or(int n, obj_t *a, obj_t *b);
obj_t *f_and(int n, obj_t *a, obj_t *b);

#endif
