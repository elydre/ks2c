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

#include "ks.h"

/*****************************************
 *                                      *
 *           Basic functions            *
 *                                      *
*****************************************/

obj_t *f_print(int n, ...) {
    va_list ap;
    va_start(ap, n);
    for (int i = 0; i < n; i++) {
        obj_t *o = va_arg(ap, obj_t*);
        if (o->type == STRING) {
            fputs(o->str_ptr, stdout);
        } else if (o->type == INTEGER) {
            printf("%d", o->int_val);
        } else if (o->type == BOOLEAN) {
            printf("%s", o->int_val ? "true" : "false");
        } else if (o->type == NONE) {
            printf("none");
        } else if (o->type == ALLOCATED_STRING) {
            fputs(o->str_ptr, stdout);
        } else {
            printf("<?>");
        }
        fi_clean_obj(o);
        putchar(' ');
    }
    putchar('\n');
    va_end(ap);
    return &NONE_OBJ;
}

obj_t *f_type(int n, obj_t *a) {
    UNUSED(n);
    obj_t *res = fi_new_string_obj(fi_get_type(a->type));
    fi_clean_obj(a);
    return res;
}

obj_t *f_pass(int n, obj_t *a) {
    UNUSED(n);
    return a;
}

/*****************************************
 *                                      *
 *          Casting functions           *
 *                                      *
*****************************************/

obj_t *f_int(int n, obj_t *a) {
    UNUSED(n);
    int res;

    if (a->type == INTEGER) {
        return a;
    } else if (a->type == FLOAT) {
        res = (int) a->flt_val;
    } else if (a->type == ALLOCATED_STRING) {
        res = atoi(a->str_ptr);
    } else if (a->type == STRING) {
        res = atoi(a->str_ptr);
    } else if (a->type == BOOLEAN) {
        res = a->int_val;
    } else if (a->type == NONE) {
        res = 0;
    } else {
        printf("f_int: unsupported type [%s]\n", fi_get_type(a->type));
        fi_clean_obj(a);
        return &NONE_OBJ;
    }
    fi_clean_obj(a);
    return fi_new_integer_obj(res);
}

obj_t *f_float(int n, obj_t *a) {
    UNUSED(n);
    float res;

    if (a->type == INTEGER) {
        res = (float) a->int_val;
    } else if (a->type == FLOAT) {
        return a;
    } else if (a->type == ALLOCATED_STRING) {
        res = atof(a->str_ptr);
    } else if (a->type == STRING) {
        res = atof(a->str_ptr);
    } else if (a->type == BOOLEAN) {
        res = a->int_val;
    } else if (a->type == NONE) {
        res = 0;
    } else {
        printf("f_float: unsupported type [%s]\n", fi_get_type(a->type));
        fi_clean_obj(a);
        return &NONE_OBJ;
    }
    fi_clean_obj(a);
    return fi_new_float_obj(res);
}

obj_t *f_str(int n, obj_t *a) {
    UNUSED(n);
    char *res;

    if (a->type == INTEGER) {
        res = malloc(12);
        sprintf(res, "%d", a->int_val);
    } else if (a->type == FLOAT) {
        res = malloc(12);
        sprintf(res, "%f", a->flt_val);
    } else if (a->type == ALLOCATED_STRING) {
        res = malloc(strlen(a->str_ptr) + 1);
        strcpy(res, a->str_ptr);
    } else if (a->type == STRING) {
        res = malloc(strlen(a->str_ptr) + 1);
        strcpy(res, a->str_ptr);
    } else if (a->type == BOOLEAN) {
        res = malloc(6);
        sprintf(res, "%s", a->int_val ? "true" : "false");
    } else if (a->type == NONE) {
        res = malloc(5);
        sprintf(res, "%s", "none");
    } else {
        printf("f_str: unsupported type [%s]\n", fi_get_type(a->type));
        fi_clean_obj(a);
        return &NONE_OBJ;
    }
    fi_clean_obj(a);
    return fi_new_allocated_string_obj(res);
}

/*****************************************
 *                                      *
 *         Operations functions         *
 *                                      *
*****************************************/

obj_t *f_add(int n, obj_t *a, obj_t *b) {
    UNUSED(n);
    obj_t *res;

    if (a->type == INTEGER && b->type == INTEGER) {
        res = fi_new_integer_obj(a->int_val + b->int_val);
    } else if (a->type == FLOAT && b->type == FLOAT) {
        res = fi_new_float_obj(a->flt_val + b->flt_val);
    } else if (a->type == INTEGER && b->type == FLOAT) {
        res = fi_new_float_obj(a->int_val + b->flt_val);
    } else if (a->type == FLOAT && b->type == INTEGER) {
        res = fi_new_float_obj(a->flt_val + b->int_val);
    } else if (
        (a->type == STRING || a->type == ALLOCATED_STRING) &&
        (b->type == STRING || b->type == ALLOCATED_STRING)
    ) {
        char *buf = malloc(strlen(a->str_ptr) + strlen(b->str_ptr) + 1);
        strcpy(buf, a->str_ptr);
        strcat(buf, b->str_ptr);
        res = fi_new_allocated_string_obj(buf);
    } else {
        printf("f_add: no method to compute [%s] + [%s]\n", fi_get_type(a->type), fi_get_type(b->type));
        res = &NONE_OBJ;
    }

    fi_clean_obj(a);
    fi_clean_obj(b);
    return res;
}

obj_t *f_sub(int n, obj_t *a, obj_t *b) {
    UNUSED(n);
    obj_t *res;

    if (a->type == INTEGER && b->type == INTEGER) {
        res = fi_new_integer_obj(a->int_val - b->int_val);
    } else if (a->type == FLOAT && b->type == FLOAT) {
        res = fi_new_float_obj(a->flt_val - b->flt_val);
    } else if (a->type == INTEGER && b->type == FLOAT) {
        res = fi_new_float_obj(a->int_val - b->flt_val);
    } else if (a->type == FLOAT && b->type == INTEGER) {
        res = fi_new_float_obj(a->flt_val - b->int_val);
    } else {
        printf("f_sub: no method to compute [%s] - [%s]\n", fi_get_type(a->type), fi_get_type(b->type));
        res = &NONE_OBJ;
    }

    fi_clean_obj(a);
    fi_clean_obj(b);
    return res;
}

obj_t *f_mul(int n, obj_t *a, obj_t *b) {
    UNUSED(n);
    obj_t *res;

    if (a->type == INTEGER && b->type == INTEGER) {
        res = fi_new_integer_obj(a->int_val * b->int_val);
    } else if (a->type == FLOAT && b->type == FLOAT) {
        res = fi_new_float_obj(a->flt_val * b->flt_val);
    } else if (a->type == INTEGER && b->type == FLOAT) {
        res = fi_new_float_obj(a->int_val * b->flt_val);
    } else if (a->type == FLOAT && b->type == INTEGER) {
        res = fi_new_float_obj(a->flt_val * b->int_val);
    } else {
        printf("f_mul: no method to compute [%s] * [%s]\n", fi_get_type(a->type), fi_get_type(b->type));
        res = &NONE_OBJ;
    }

    fi_clean_obj(a);
    fi_clean_obj(b);
    return res;
}

obj_t *f_mod(int n, obj_t *a, obj_t *b) {
    UNUSED(n);
    obj_t *res;

    if (a->type == INTEGER && b->type == INTEGER) {
        res = fi_new_integer_obj(a->int_val % b->int_val);
    } else {
        printf("f_mod: no method to compute [%s] %% [%s]\n", fi_get_type(a->type), fi_get_type(b->type));
        res = &NONE_OBJ;
    }

    fi_clean_obj(a);
    fi_clean_obj(b);
    return res;
}

obj_t *f_div(int n, obj_t *a, obj_t *b) {
    UNUSED(n);
    obj_t *res;

    if (a->type == INTEGER && b->type == INTEGER) {
        res = fi_new_integer_obj(a->int_val / b->int_val);
    } else if (a->type == FLOAT && b->type == FLOAT) {
        res = fi_new_float_obj(a->flt_val / b->flt_val);
    } else if (a->type == INTEGER && b->type == FLOAT) {
        res = fi_new_float_obj(a->int_val / b->flt_val);
    } else if (a->type == FLOAT && b->type == INTEGER) {
        res = fi_new_float_obj(a->flt_val / b->int_val);
    } else {
        printf("f_div: no method to compute [%s] / [%s]\n", fi_get_type(a->type), fi_get_type(b->type));
        res = &NONE_OBJ;
    }

    fi_clean_obj(a);
    fi_clean_obj(b);
    return res;
}

/*****************************************
 *                                      *
 *         Comparison functions         *
 *                                      *
*****************************************/

obj_t *f_eql(int n, obj_t *a, obj_t *b) {
    UNUSED(n);
    obj_t *res;

    if (a->type == INTEGER && b->type == INTEGER) {
        res = fi_new_boolean_obj(a->int_val == b->int_val);
    } else if (a->type == FLOAT && b->type == FLOAT) {
        res = fi_new_boolean_obj(a->flt_val == b->flt_val);
    } else if (a->type == INTEGER && b->type == FLOAT) {
        res = fi_new_boolean_obj(a->int_val == b->flt_val);
    } else if (a->type == FLOAT && b->type == INTEGER) {
        res = fi_new_boolean_obj(a->flt_val == b->int_val);
    } else if (
        (a->type == STRING || a->type == ALLOCATED_STRING) &&
        (b->type == STRING || b->type == ALLOCATED_STRING)
    ) {
        res = fi_new_boolean_obj(strcmp(a->str_ptr, b->str_ptr) == 0);
    } else {
        printf("f_eql: no method to compute [%s] == [%s]\n", fi_get_type(a->type), fi_get_type(b->type));
        res = &NONE_OBJ;
    }

    fi_clean_obj(a);
    fi_clean_obj(b);
    return res;
    
}

obj_t *f_neq(int n, obj_t *a, obj_t *b) {
    UNUSED(n);

    obj_t *res = f_eql(2, a, b);
    if (res->type == BOOLEAN) {
        res->int_val = !res->int_val;
    }
    return res;
}

obj_t *f_inf(int n, obj_t *a, obj_t *b) {
    UNUSED(n);
    obj_t *res;

    if (a->type == INTEGER && b->type == INTEGER) {
        res = fi_new_boolean_obj(a->int_val < b->int_val);
    } else if (a->type == FLOAT && b->type == FLOAT) {
        res = fi_new_boolean_obj(a->flt_val < b->flt_val);
    } else if (a->type == INTEGER && b->type == FLOAT) {
        res = fi_new_boolean_obj(a->int_val < b->flt_val);
    } else if (a->type == FLOAT && b->type == INTEGER) {
        res = fi_new_boolean_obj(a->flt_val < b->int_val);
    } else {
        printf("f_inf: no method to compute [%s] -= [%s]\n", fi_get_type(a->type), fi_get_type(b->type));
        res = &NONE_OBJ;
    }

    fi_clean_obj(a);
    fi_clean_obj(b);
    return res;
}

obj_t *f_sup(int n, obj_t *a, obj_t *b) {
    UNUSED(n);
    obj_t *res;

    if (a->type == INTEGER && b->type == INTEGER) {
        res = fi_new_boolean_obj(a->int_val > b->int_val);
    } else if (a->type == FLOAT && b->type == FLOAT) {
        res = fi_new_boolean_obj(a->flt_val > b->flt_val);
    } else if (a->type == INTEGER && b->type == FLOAT) {
        res = fi_new_boolean_obj(a->int_val > b->flt_val);
    } else if (a->type == FLOAT && b->type == INTEGER) {
        res = fi_new_boolean_obj(a->flt_val > b->int_val);
    } else {
        printf("f_sup: no method to compute [%s] += [%s]\n", fi_get_type(a->type), fi_get_type(b->type));
        res = &NONE_OBJ;
    }

    fi_clean_obj(a);
    fi_clean_obj(b);
    return res;
}

/*****************************************
 *                                      *
 *          Boolean functions           *
 *                                      *
*****************************************/

obj_t *f_not(int n, obj_t *a) {
    UNUSED(n);
    obj_t *res;

    if (a->type == BOOLEAN) {
        res = fi_new_boolean_obj(!a->int_val);
    } else if (a->type == INTEGER) {
        res = fi_new_boolean_obj(!a->int_val);
    } else if (a->type == FLOAT) {
        res = fi_new_boolean_obj(!a->flt_val);
    } else {
        printf("f_not: unsupported type [%d]\n", a->type);
        res = &NONE_OBJ;
    }

    fi_clean_obj(a);
    return res;
}

obj_t *f_or(int n, obj_t *a, obj_t *b) {
    UNUSED(n);
    obj_t *res;

    if (
        (a->type == BOOLEAN || a->type == INTEGER) &&
        (b->type == BOOLEAN || b->type == INTEGER)
    ) {
        res = fi_new_boolean_obj(a->int_val || b->int_val);
    } else {
        printf("f_or: no method to compute [%s] or [%s]\n", fi_get_type(a->type), fi_get_type(b->type));
        res = &NONE_OBJ;
    }

    fi_clean_obj(a);
    fi_clean_obj(b);
    return res;
}


obj_t *f_and(int n, obj_t *a, obj_t *b) {
    UNUSED(n);
    obj_t *res;

    if (
        (a->type == BOOLEAN || a->type == INTEGER) &&
        (b->type == BOOLEAN || b->type == INTEGER)
    ) {
        res = fi_new_boolean_obj(a->int_val && b->int_val);
    } else {
        printf("f_and: no method to compute [%s] and [%s]\n", fi_get_type(a->type), fi_get_type(b->type));
        res = &NONE_OBJ;
    }

    fi_clean_obj(a);
    fi_clean_obj(b);
    return res;
}
