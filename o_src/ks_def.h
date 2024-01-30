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

#ifndef KSDEF_H
#define KSDEF_H

#define f_print(lvl, n, ...) ff_print(n, __VA_ARGS__)
#define f_type(lvl, n, f1) ff_type(n, f1)
#define f_pass(lvl, n, f1) ff_pass(n, f1)

#define f_int(lvl, n, f1) ff_int(n, f1)
#define f_str(lvl, n, f1) ff_str(n, f1)
#define f_float(lvl, n, f1) ff_float(n, f1)

#define f_add(lvl, n,f1,f2) (a##lvl=f1,b##lvl=f2, a##lvl.type==INTEGER && b##lvl.type==INTEGER ? \
        fi_new_integer_obj(a##lvl.int_val+b##lvl.int_val) : ff_add(n,a##lvl,b##lvl))

#define f_sub(lvl, n,f1,f2) (a##lvl=f1,b##lvl=f2, a##lvl.type==INTEGER && b##lvl.type==INTEGER ? \
        fi_new_integer_obj(a##lvl.int_val-b##lvl.int_val) : ff_sub(n,a##lvl,b##lvl))

#define f_mul(lvl, n,f1,f2) (a##lvl=f1,b##lvl=f2, a##lvl.type==INTEGER && b##lvl.type==INTEGER ? \
        fi_new_integer_obj(a##lvl.int_val*b##lvl.int_val) : ff_mul(n,a##lvl,b##lvl))

#define f_div(lvl, n,f1,f2) (a##lvl=f1,b##lvl=f2, a##lvl.type==INTEGER && b##lvl.type==INTEGER ? \
        fi_new_integer_obj(a##lvl.int_val/b##lvl.int_val) : ff_div(n,a##lvl,b##lvl))

#define f_mod(lvl, n,f1,f2) (a##lvl=f1,b##lvl=f2, a##lvl.type==INTEGER && b##lvl.type==INTEGER ? \
        fi_new_integer_obj(a##lvl.int_val%b##lvl.int_val) : ff_mod(n,a##lvl,b##lvl))

#define f_eql(lvl, n,f1,f2) (a##lvl=f1,b##lvl=f2, a##lvl.type==INTEGER && b##lvl.type==INTEGER ? \
        fi_new_boolean_obj(a##lvl.int_val==b##lvl.int_val) : ff_eql(n,a##lvl,b##lvl))

#define f_neq(lvl, n,f1,f2) (a##lvl=f1,b##lvl=f2, a##lvl.type==INTEGER && b##lvl.type==INTEGER ? \
        fi_new_boolean_obj(a##lvl.int_val!=b##lvl.int_val) : f_neq(n,a##lvl,b##lvl))

#define f_inf(lvl, n,f1,f2) (a##lvl=f1,b##lvl=f2, a##lvl.type==INTEGER && b##lvl.type==INTEGER ? \
        fi_new_boolean_obj(a##lvl.int_val<b##lvl.int_val) : ff_inf(n,a##lvl,b##lvl))

#define f_sup(lvl, n,f1,f2) (a##lvl=f1,b##lvl=f2, a##lvl.type==INTEGER && b##lvl.type==INTEGER ? \
        fi_new_boolean_obj(a##lvl.int_val>b##lvl.int_val) : ff_sup(n,a##lvl,b##lvl))

#define f_or(lvl, n,f1,f2) (a##lvl=f1,b##lvl=f2, (a##lvl.type==INTEGER || a##lvl.type==BOOLEAN) && \
        (b##lvl.type==INTEGER || b##lvl.type==BOOLEAN) ? \
        fi_new_boolean_obj(a##lvl.int_val || b##lvl.int_val) : ff_or(n,a##lvl,b##lvl))

#define f_and(lvl, n,f1,f2) (a##lvl=f1,b##lvl=f2, (a##lvl.type==INTEGER || a##lvl.type==BOOLEAN) && \
        (b##lvl.type==INTEGER || b##lvl.type==BOOLEAN) ? \
        fi_new_boolean_obj(a##lvl.int_val && b##lvl.int_val) : ff_and(n,a##lvl,b##lvl))

#define f_not(lvl, n,f1) (a##lvl=f1, (a##lvl.type==INTEGER || a##lvl.type==BOOLEAN) ? \
        fi_new_boolean_obj(!a##lvl.int_val) : ff_not(n,a##lvl))

#endif
