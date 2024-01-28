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

fast_t f_print(int n, ...) {
    va_list ap;
    va_start(ap, n);
    for (int i = 0; i < n; i++) {
        fast_t o = va_arg(ap, fast_t);
        if (o.type == STRING) {
            fputs(o.obj_ptr->str_ptr, stdout);
        } else if (o.type == INTEGER) {
            printf("%d", o.int_val);
        } else if (o.type == BOOLEAN) {
            printf("%s", o.int_val ? "true" : "false");
        } else if (o.type == NONE) {
            printf("none");
        } else if (o.type == ALLOCATED_STRING) {
            fputs(o.obj_ptr->str_ptr, stdout);
        } else {
            printf("<?>");
        }
        fi_clean_obj(o);
        putchar(' ');
    }
    putchar('\n');
    va_end(ap);
    return fi_new_none_obj();
}

fast_t f_type(int n, fast_t a) {
    UNUSED(n);
    fast_t res = fi_new_string_obj(fi_get_type(a.type));
    fi_clean_obj(a);
    return res;
}

fast_t f_pass(int n, fast_t a) {
    UNUSED(n);
    return a;
}

/*****************************************
 *                                      *
 *          Casting functions           *
 *                                      *
*****************************************/

fast_t f_int(int n, fast_t a) {
    UNUSED(n);
    int res;

    if (a.type == INTEGER)
        return a;

    if (a.type == FLOAT)
        return fi_new_integer_obj((int) a.flt_val);

    if (a.type == BOOLEAN)
        return fi_new_integer_obj(a.int_val);

    if (a.type == NONE)
        return fi_new_integer_obj(0);

    if (a.type == ALLOCATED_STRING || a.type == STRING) {
        res = atoi(a.obj_ptr->str_ptr);
        fi_clean_obj(a);
        return fi_new_integer_obj(res);
    }

    printf("f_int: unsupported type [%s]\n", fi_get_type(a.type));
    fi_clean_obj(a);
    return fi_new_none_obj();
}

fast_t f_float(int n, fast_t a) {
    UNUSED(n);
    float res;

    if (a.type == INTEGER)
        return fi_new_float_obj((float) a.int_val);

    if (a.type == FLOAT)
        return a;

    if (a.type == BOOLEAN)
        return fi_new_float_obj((float) a.int_val);

    if (a.type == NONE)
        return fi_new_float_obj(0.0);
    
    if (a.type == ALLOCATED_STRING || a.type == STRING) {
        res = atof(a.obj_ptr->str_ptr);
        fi_clean_obj(a);
        return fi_new_float_obj(res);
    }

    printf("f_float: unsupported type [%s]\n", fi_get_type(a.type));
    fi_clean_obj(a);
    return fi_new_none_obj();
}

fast_t f_str(int n, fast_t a) {
    UNUSED(n);
    char *res;

    if (a.type == INTEGER) {
        res = malloc(12);
        sprintf(res, "%d", a.int_val);
        return fi_new_allocated_string_obj(res);
    }

    if (a.type == FLOAT) {
        res = malloc(12);
        sprintf(res, "%f", a.flt_val);
        return fi_new_allocated_string_obj(res);
    }

    if (a.type == BOOLEAN) {
        res = malloc(6);
        sprintf(res, "%s", a.int_val ? "true" : "false");
        return fi_new_allocated_string_obj(res);
    }

    if (a.type == NONE) {
        return fi_new_string_obj("none");
    }
    
    if (a.type == ALLOCATED_STRING || a.type == STRING) {
        return a;
    }

    printf("f_str: unsupported type [%s]\n", fi_get_type(a.type));
    fi_clean_obj(a);
    return fi_new_none_obj();
}

/*****************************************
 *                                      *
 *         Operations functions         *
 *                                      *
*****************************************/

fast_t ff_add(int n, fast_t a, fast_t b) {
    UNUSED(n);
    fast_t res;

    if (a.type == FLOAT && b.type == FLOAT) {
        res = fi_new_float_obj(a.flt_val + b.flt_val);
    } else if (a.type == INTEGER && b.type == FLOAT) {
        res = fi_new_float_obj(a.int_val + b.flt_val);
    } else if (a.type == FLOAT && b.type == INTEGER) {
        res = fi_new_float_obj(a.flt_val + b.int_val);
    } else if (
        (a.type == STRING || a.type == ALLOCATED_STRING) &&
        (b.type == STRING || b.type == ALLOCATED_STRING)
    ) {
        char *str = malloc(strlen(a.obj_ptr->str_ptr) + strlen(b.obj_ptr->str_ptr) + 1);
        strcpy(str, a.obj_ptr->str_ptr);
        strcat(str, b.obj_ptr->str_ptr);
        res = fi_new_allocated_string_obj(str);
    } else {
        printf("f_add: no method to compute [%s] + [%s]\n", fi_get_type(a.type), fi_get_type(b.type));
        res = fi_new_none_obj();
    }

    fi_clean_obj(a);
    fi_clean_obj(b);
    return res;
}

fast_t f_sub(int n, fast_t a, fast_t b) {
    UNUSED(n);
    fast_t res;

    if (a.type == INTEGER && b.type == INTEGER) {
        res = fi_new_integer_obj(a.int_val - b.int_val);
    } else if (a.type == FLOAT && b.type == FLOAT) {
        res = fi_new_float_obj(a.flt_val - b.flt_val);
    } else if (a.type == INTEGER && b.type == FLOAT) {
        res = fi_new_float_obj(a.int_val - b.flt_val);
    } else if (a.type == FLOAT && b.type == INTEGER) {
        res = fi_new_float_obj(a.flt_val - b.int_val);
    } else {
        printf("f_sub: no method to compute [%s] - [%s]\n", fi_get_type(a.type), fi_get_type(b.type));
        res = fi_new_none_obj();
    }

    fi_clean_obj(a);
    fi_clean_obj(b);
    return res;
}

fast_t ff_mul(int n, fast_t a, fast_t b) {
    UNUSED(n);
    fast_t res;

    if (a.type == FLOAT && b.type == FLOAT) {
        res = fi_new_float_obj(a.flt_val * b.flt_val);
    } else if (a.type == INTEGER && b.type == FLOAT) {
        res = fi_new_float_obj(a.int_val * b.flt_val);
    } else if (a.type == FLOAT && b.type == INTEGER) {
        res = fi_new_float_obj(a.flt_val * b.int_val);
    } else {
        printf("f_mul: no method to compute [%s] * [%s]\n", fi_get_type(a.type), fi_get_type(b.type));
        res = fi_new_none_obj();
    }

    fi_clean_obj(a);
    fi_clean_obj(b);
    return res;
}

fast_t ff_mod(int n, fast_t a, fast_t b) {
    UNUSED(n);

    printf("f_mod: no method to compute [%s] %% [%s]\n", fi_get_type(a.type), fi_get_type(b.type));

    fi_clean_obj(a);
    fi_clean_obj(b);
    return fi_new_none_obj();;
}

fast_t f_div(int n, fast_t a, fast_t b) {
    UNUSED(n);
    fast_t res;

    if (a.type == INTEGER && b.type == INTEGER) {
        res = fi_new_integer_obj(a.int_val / b.int_val);
    } else if (a.type == FLOAT && b.type == FLOAT) {
        res = fi_new_float_obj(a.flt_val / b.flt_val);
    } else if (a.type == INTEGER && b.type == FLOAT) {
        res = fi_new_float_obj(a.int_val / b.flt_val);
    } else if (a.type == FLOAT && b.type == INTEGER) {
        res = fi_new_float_obj(a.flt_val / b.int_val);
    } else {
        printf("f_div: no method to compute [%s] / [%s]\n", fi_get_type(a.type), fi_get_type(b.type));
        res = fi_new_none_obj();
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

fast_t ff_eql(int n, fast_t a, fast_t b) {
    UNUSED(n);
    fast_t res;

    if (a.type == FLOAT && b.type == FLOAT) {
        res = fi_new_boolean_obj(a.flt_val == b.flt_val);
    } else if (a.type == INTEGER && b.type == FLOAT) {
        res = fi_new_boolean_obj(a.int_val == b.flt_val);
    } else if (a.type == FLOAT && b.type == INTEGER) {
        res = fi_new_boolean_obj(a.flt_val == b.int_val);
    } else if (
        (a.type == STRING || a.type == ALLOCATED_STRING) &&
        (b.type == STRING || b.type == ALLOCATED_STRING)
    ) {
        res = fi_new_boolean_obj(strcmp(a.obj_ptr->str_ptr, b.obj_ptr->str_ptr) == 0);
    } else {
        printf("f_eql: no method to compute [%s] == [%s]\n", fi_get_type(a.type), fi_get_type(b.type));
        res = fi_new_none_obj();
    }

    fi_clean_obj(a);
    fi_clean_obj(b);
    return res;
    
}

fast_t f_neq(int n, fast_t a, fast_t b) {
    UNUSED(n);

    fast_t res = f_eql(2, a, b);
    if (res.type == BOOLEAN) {
        res.int_val = !res.int_val;
    }
    return res;
}

fast_t ff_inf(int n, fast_t a, fast_t b) {
    UNUSED(n);
    fast_t res;

    if (a.type == FLOAT && b.type == FLOAT) {
        res = fi_new_boolean_obj(a.flt_val < b.flt_val);
    } else if (a.type == INTEGER && b.type == FLOAT) {
        res = fi_new_boolean_obj(a.int_val < b.flt_val);
    } else if (a.type == FLOAT && b.type == INTEGER) {
        res = fi_new_boolean_obj(a.flt_val < b.int_val);
    } else {
        printf("f_inf: no method to compute [%s] -= [%s]\n", fi_get_type(a.type), fi_get_type(b.type));
        res = fi_new_none_obj();
    }

    fi_clean_obj(a);
    fi_clean_obj(b);
    return res;
}

fast_t f_sup(int n, fast_t a, fast_t b) {
    UNUSED(n);
    fast_t res;

    if (a.type == INTEGER && b.type == INTEGER) {
        res = fi_new_boolean_obj(a.int_val > b.int_val);
    } else if (a.type == FLOAT && b.type == FLOAT) {
        res = fi_new_boolean_obj(a.flt_val > b.flt_val);
    } else if (a.type == INTEGER && b.type == FLOAT) {
        res = fi_new_boolean_obj(a.int_val > b.flt_val);
    } else if (a.type == FLOAT && b.type == INTEGER) {
        res = fi_new_boolean_obj(a.flt_val > b.int_val);
    } else {
        printf("f_sup: no method to compute [%s] += [%s]\n", fi_get_type(a.type), fi_get_type(b.type));
        res = fi_new_none_obj();
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

fast_t f_not(int n, fast_t a) {
    UNUSED(n);
    fast_t res;

    if (a.type == BOOLEAN) {
        res = fi_new_boolean_obj(!a.int_val);
    } else if (a.type == INTEGER) {
        res = fi_new_boolean_obj(!a.int_val);
    } else if (a.type == FLOAT) {
        res = fi_new_boolean_obj(!a.flt_val);
    } else {
        printf("f_not: unsupported type [%d]\n", a.type);
        res = fi_new_none_obj();
    }

    fi_clean_obj(a);
    return res;
}

fast_t ff_or(int n, fast_t a, fast_t b) {
    UNUSED(n);

    printf("f_or: no method to compute [%s] or [%s]\n", fi_get_type(a.type), fi_get_type(b.type));

    fi_clean_obj(a);
    fi_clean_obj(b);
    return fi_new_none_obj();
}


fast_t f_and(int n, fast_t a, fast_t b) {
    UNUSED(n);
    fast_t res;

    if (
        (a.type == BOOLEAN || a.type == INTEGER) &&
        (b.type == BOOLEAN || b.type == INTEGER)
    ) {
        res = fi_new_boolean_obj(a.int_val && b.int_val);
    } else {
        printf("f_and: no method to compute [%s] and [%s]\n", fi_get_type(a.type), fi_get_type(b.type));
        res = fi_new_none_obj();
    }

    fi_clean_obj(a);
    fi_clean_obj(b);
    return res;
}
