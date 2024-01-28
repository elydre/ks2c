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
#define fi_set_var(vars, var_id, o) ((vars)->len > var_id ? ((vars)->arr[var_id].type == INTEGER && o.type == INTEGER ? ((vars)->arr[var_id].int_val = o.int_val) : ff_set_var(vars, var_id, o)) : ff_set_var(vars, var_id, o))
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
fast_t f_print(int n, ...);
fast_t f_type(int n, fast_t a);
fast_t f_pass(int n, fast_t a);

fast_t f_int(int n, fast_t a);
fast_t f_str(int n, fast_t a);
fast_t f_float(int n, fast_t a);

#define f_add(n, a, b) (a.type == INTEGER && b.type == INTEGER ? fi_new_integer_obj(a.int_val + b.int_val) : ff_add(n, a, b))
#define f_eql(n, a, b) (a.type == INTEGER && b.type == INTEGER ? fi_new_boolean_obj(a.int_val == b.int_val) : ff_eql(n, a, b))
#define f_mod(n, a, b) (a.type == INTEGER && b.type == INTEGER ? fi_new_integer_obj(a.int_val % b.int_val) : ff_mod(n, a, b))
#define f_mul(n, a, b) (a.type == INTEGER && b.type == INTEGER ? fi_new_integer_obj(a.int_val * b.int_val) : ff_mul(n, a, b))
#define f_inf(n, a, b) (a.type == INTEGER && b.type == INTEGER ? fi_new_boolean_obj(a.int_val < b.int_val) : ff_inf(n, a, b))
#define f_or(n, a, b) ((a.type == INTEGER || a.type == BOOLEAN) && (b.type == INTEGER || b.type == BOOLEAN) ? fi_new_boolean_obj(a.int_val || b.int_val) : ff_or(n, a, b))

fast_t f_sub(int n, fast_t a, fast_t b);
fast_t ff_add(int n, fast_t a, fast_t b);
fast_t ff_mul(int n, fast_t a, fast_t b);
fast_t ff_mod(int n, fast_t a, fast_t b);
fast_t f_div(int n, fast_t a, fast_t b);

fast_t ff_eql(int n, fast_t a, fast_t b);
fast_t f_neq(int n, fast_t a, fast_t b);
fast_t ff_inf(int n, fast_t a, fast_t b);
fast_t f_sup(int n, fast_t a, fast_t b);

fast_t f_not(int n, fast_t a);
fast_t ff_or(int n, fast_t a, fast_t b);
fast_t f_and(int n, fast_t a, fast_t b);

#endif
