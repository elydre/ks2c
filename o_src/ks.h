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

#include "ks_def.h"

#define VERSION "2.4"

#define CUSTOM_MALLOC 1
#define BYPASS_GETVAR 1
#define FAST_INT_VARS 1

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
    int ref_count;
    union {
        char *str_ptr;
    };
} obj_t;

typedef struct {
    char type;
    union {
        int int_val;
        float flt_val;
        obj_t *obj_ptr;
    };
} fast_t;

typedef struct {
    fast_t *arr;
    int len;
} vars_t;

// tools.c
void   fi_clean_obj(fast_t o);
void   fi_clean_up(vars_t *vars);

#if BYPASS_GETVAR
#define fi_get_var(vars, var_id) ((vars)->arr[var_id])
#else
fast_t fi_get_var(vars_t *vars, int var_id);
#endif

void   ff_set_var(vars_t *vars, int var_id, fast_t o);

#define fi_is(o) (o.type == INTEGER || o.type == BOOLEAN ? o.int_val != 0 : ff_is(o))

#if FAST_INT_VARS
#define fi_set_var(vars, var_id, o) ((vars)->len > var_id ? \
        ((vars)->arr[var_id].type == INTEGER && o.type == INTEGER ? \
        ((vars)->arr[var_id].int_val = o.int_val) : \
        ff_set_var(vars, var_id, o)) : ff_set_var(vars, var_id, o))
#else
#define fi_set_var(vars, var_id, o) ff_set_val(vars, var_id, o)
#endif

int ff_is(fast_t o);
int fi_int_val(fast_t o);
char *fi_get_type(char type);

#define fi_new_none_obj() ((fast_t){.type = NONE})
#define fi_new_integer_obj(i) ((fast_t){.type = INTEGER, .int_val = i})
#define fi_new_float_obj(f) ((fast_t){.type = FLOAT, .flt_val = f})
#define fi_new_boolean_obj(b) ((fast_t){.type = BOOLEAN, .int_val = b})

fast_t fi_new_string_obj(char *s);
fast_t fi_new_allocated_string_obj(char *p);

// fcm.c
fast_t ff_print(int n, ...);
fast_t ff_type(int n, fast_t a);
fast_t ff_pass(int n, fast_t a);

fast_t ff_int(int n, fast_t a);
fast_t ff_str(int n, fast_t a);
fast_t ff_float(int n, fast_t a);

fast_t ff_sub(int n, fast_t a, fast_t b);
fast_t ff_add(int n, fast_t a, fast_t b);
fast_t ff_mul(int n, fast_t a, fast_t b);
fast_t ff_mod(int n, fast_t a, fast_t b);
fast_t ff_div(int n, fast_t a, fast_t b);

fast_t ff_eql(int n, fast_t a, fast_t b);
fast_t ff_neq(int n, fast_t a, fast_t b);
fast_t ff_inf(int n, fast_t a, fast_t b);
fast_t ff_sup(int n, fast_t a, fast_t b);

fast_t ff_not(int n, fast_t a);
fast_t ff_or(int n, fast_t a, fast_t b);
fast_t ff_and(int n, fast_t a, fast_t b);

#endif
