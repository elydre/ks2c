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

obj_t f_print(int n, ...) {
    va_list ap;
    va_start(ap, n);
    for (int i = 0; i < n; i++) {
        obj_t o = va_arg(ap, obj_t);
        if (o.type == STRING) {
            fputs(o.str_ptr, stdout);
        } else if (o.type == INTEGER) {
            printf("%d", o.int_val);
        } else if (o.type == BOOLEAN) {
            printf("%s", o.int_val ? "true" : "false");
        } else if (o.type == NONE) {
            printf("none");
        } else if (o.type == ALLOCATED_STRING) {
            fputs(o.str_ptr, stdout);
            free(o.str_ptr);
        } else {
            printf("unknown type [%d]", o.type);
            fi_clean_obj(o);
        }
        putchar(' ');
    }
    putchar('\n');
    va_end(ap);
    return NONE_OBJ;
}

obj_t f_type(int n, obj_t a) {
    UNUSED(n);

    if (a.type == INTEGER) {
        return STRING_OBJ("int");
    } else if (a.type == STRING) {
        return STRING_OBJ("str");
    } else if (a.type == ALLOCATED_STRING) {
        free(a.str_ptr);
        return STRING_OBJ("str");
    } else if (a.type == BOOLEAN) {
        return STRING_OBJ("bool");
    } else if (a.type == FLOAT) {
        return STRING_OBJ("float");
    } else if (a.type == NONE) {
        return STRING_OBJ("none");
    }
    printf("error: unknown type [%d]\n", a.type);
    fi_clean_obj(a);
    return NONE_OBJ;
}

obj_t f_pass(int n, obj_t a) {
    UNUSED(n);
    return a;
}

/*****************************************
 *                                      *
 *          Casting functions           *
 *                                      *
*****************************************/

obj_t f_int(int n, obj_t a) {
    UNUSED(n);

    if (a.type == INTEGER) {
        return a;
    } else if (a.type == FLOAT) {
        return INTEGER_OBJ((int) a.flt_val);
    } else if (a.type == ALLOCATED_STRING) {
        int res = atoi(a.str_ptr);
        free(a.str_ptr);
        return INTEGER_OBJ(res);
    } else if (a.type == STRING) {
        int res = atoi(a.str_ptr);
        return INTEGER_OBJ(res);
    } else if (a.type == BOOLEAN) {
        return INTEGER_OBJ(a.int_val);
    } else if (a.type == NONE) {
        return INTEGER_OBJ(0);
    }
    printf("error: unsupported type for int [%d]\n", a.type);
    fi_clean_obj(a);
    return NONE_OBJ;
}

obj_t f_float(int n, obj_t a) {
    UNUSED(n);

    if (a.type == INTEGER) {
        return FLOAT_OBJ((float) a.int_val);
    } else if (a.type == FLOAT) {
        return a;
    } else if (a.type == ALLOCATED_STRING) {
        float res = atof(a.str_ptr);
        free(a.str_ptr);
        return FLOAT_OBJ(res);
    } else if (a.type == STRING) {
        float res = atof(a.str_ptr);
        return FLOAT_OBJ(res);
    } else if (a.type == BOOLEAN) {
        return FLOAT_OBJ(a.int_val);
    } else if (a.type == NONE) {
        return FLOAT_OBJ(0.0);
    }
    printf("error: unsupported type for float [%d]\n", a.type);
    fi_clean_obj(a);
    return NONE_OBJ;
}

obj_t f_str(int n, obj_t a) {
    UNUSED(n);

    if (a.type == INTEGER) {
        char *buf = malloc(12);
        sprintf(buf, "%d", a.int_val);
        return ALLOCATED_STRING_OBJ(buf);
    } else if (a.type == FLOAT) {
        char *buf = malloc(12);
        sprintf(buf, "%f", a.flt_val);
        return ALLOCATED_STRING_OBJ(buf);
    } else if (a.type == ALLOCATED_STRING) {
        return a;
    } else if (a.type == STRING) {
        return a;
    } else if (a.type == BOOLEAN) {
        char *buf = malloc(6);
        sprintf(buf, "%s", a.int_val ? "true" : "false");
        return ALLOCATED_STRING_OBJ(buf);
    } else if (a.type == NONE) {
        return ALLOCATED_STRING_OBJ("");
    }
    printf("error: unsupported type for str [%d]\n", a.type);
    fi_clean_obj(a);
    return NONE_OBJ;
}

/*****************************************
 *                                      *
 *         Operations functions         *
 *                                      *
*****************************************/

obj_t f_add(int n, obj_t a, obj_t b) {
    UNUSED(n);

    if (a.type == INTEGER && b.type == INTEGER) {
        return INTEGER_OBJ(a.int_val + b.int_val);
    } else if (a.type == FLOAT && b.type == FLOAT) {
        return FLOAT_OBJ(a.flt_val + b.flt_val);
    } else if (
        (a.type == STRING || a.type == ALLOCATED_STRING) &&
        (b.type == STRING || b.type == ALLOCATED_STRING)
    ) {
        char *buf = malloc(strlen(a.str_ptr) + strlen(b.str_ptr) + 1);
        strcpy(buf, a.str_ptr);
        strcat(buf, b.str_ptr);
        fi_clean_obj(a);
        fi_clean_obj(b);
        return ALLOCATED_STRING_OBJ(buf);
    }
    printf("error: unsupported type for add [%d] [%d]\n", a.type, b.type);
    fi_clean_obj(a);
    fi_clean_obj(b);
    return NONE_OBJ;
}

obj_t f_sub(int n, obj_t a, obj_t b) {
    UNUSED(n);

    if (a.type == INTEGER && b.type == INTEGER) {
        return INTEGER_OBJ(a.int_val - b.int_val);
    } else if (a.type == FLOAT && b.type == FLOAT) {
        return FLOAT_OBJ(a.flt_val - b.flt_val);
    }
    printf("error: unsupported type for sub [%d] [%d]\n", a.type, b.type);
    fi_clean_obj(a);
    fi_clean_obj(b);
    return NONE_OBJ;
}

obj_t f_mul(int n, obj_t a, obj_t b) {
    UNUSED(n);

    if (a.type == INTEGER && b.type == INTEGER) {
        return INTEGER_OBJ(a.int_val * b.int_val);
    } else if (a.type == FLOAT && b.type == FLOAT) {
        return FLOAT_OBJ(a.flt_val * b.flt_val);
    } else if (a.type == INTEGER && b.type == FLOAT) {
        return FLOAT_OBJ(a.int_val * b.flt_val);
    } else if (a.type == FLOAT && b.type == INTEGER) {
        return FLOAT_OBJ(a.flt_val * b.int_val);
    } else if (
        (a.type == STRING || a.type == ALLOCATED_STRING) &&
        b.type == INTEGER
    ) {
        char *buf = malloc(strlen(a.str_ptr) * b.int_val + 1);
        buf[0] = '\0';
        for (int i = 0; i < b.int_val; i++) {
            strcat(buf, a.str_ptr);
        }
        fi_clean_obj(a);
        return ALLOCATED_STRING_OBJ(buf);
    }
    printf("error: unsupported type for mul [%d] [%d]\n", a.type, b.type);
    fi_clean_obj(a);
    fi_clean_obj(b);
    return NONE_OBJ;
}

obj_t f_mod(int n, obj_t a, obj_t b) {
    UNUSED(n);

    if (a.type == INTEGER && b.type == INTEGER) {
        return INTEGER_OBJ(a.int_val % b.int_val);
    }
    printf("error: unsupported type for mod [%d] [%d]\n", a.type, b.type);
    fi_clean_obj(a);
    fi_clean_obj(b);
    return NONE_OBJ;
}

obj_t f_div(int n, obj_t a, obj_t b) {
    UNUSED(n);

    if (a.type == INTEGER && b.type == INTEGER) {
        return INTEGER_OBJ(a.int_val / b.int_val);
    } else if (a.type == FLOAT && b.type == FLOAT) {
        return FLOAT_OBJ(a.flt_val / b.flt_val);
    } else if (a.type == INTEGER && b.type == FLOAT) {
        return FLOAT_OBJ(a.int_val / b.flt_val);
    } else if (a.type == FLOAT && b.type == INTEGER) {
        return FLOAT_OBJ(a.flt_val / b.int_val);
    }
    printf("error: unsupported type for edv [%d] [%d]\n", a.type, b.type);
    fi_clean_obj(a);
    fi_clean_obj(b);
    return NONE_OBJ;
}

/*****************************************
 *                                      *
 *         Comparison functions         *
 *                                      *
*****************************************/

obj_t f_eql(int n, obj_t a, obj_t b) {
    UNUSED(n);

    if (a.type == INTEGER && b.type == INTEGER) {
        return BOOLEAN_OBJ(a.int_val == b.int_val);
    } else if (a.type == FLOAT && b.type == FLOAT) {
        return BOOLEAN_OBJ(a.flt_val == b.flt_val);
    } else if (
        (a.type == STRING || a.type == ALLOCATED_STRING) &&
        (b.type == STRING || b.type == ALLOCATED_STRING)
    ) {
        int res = strcmp(a.str_ptr, b.str_ptr) == 0;
        fi_clean_obj(a);
        fi_clean_obj(b);
        return BOOLEAN_OBJ(res);
    } else if (a.type == BOOLEAN && b.type == BOOLEAN) {
        return BOOLEAN_OBJ(a.int_val == b.int_val);
    } else if (a.type == NONE && b.type == NONE) {
        return BOOLEAN_OBJ(1);
    }
    printf("error: unsupported type for eql [%d] [%d]\n", a.type, b.type);
    fi_clean_obj(a);
    fi_clean_obj(b);
    return NONE_OBJ;
}

obj_t f_neq(int n, obj_t a, obj_t b) {
    UNUSED(n);

    obj_t res = f_eql(2, a, b);
    if (res.type == BOOLEAN) {
        res.int_val = !res.int_val;
    }
    return res;
}

obj_t f_inf(int n, obj_t a, obj_t b) {
    UNUSED(n);

    if (a.type == INTEGER && b.type == INTEGER) {
        return BOOLEAN_OBJ(a.int_val < b.int_val);
    } else if (a.type == FLOAT && b.type == FLOAT) {
        return BOOLEAN_OBJ(a.flt_val < b.flt_val);
    }
    printf("error: unsupported type for inf [%d] [%d]\n", a.type, b.type);
    fi_clean_obj(a);
    fi_clean_obj(b);
    return NONE_OBJ;
}

obj_t f_sup(int n, obj_t a, obj_t b) {
    UNUSED(n);

    if (a.type == INTEGER && b.type == INTEGER) {
        return BOOLEAN_OBJ(a.int_val > b.int_val);
    } else if (a.type == FLOAT && b.type == FLOAT) {
        return BOOLEAN_OBJ(a.flt_val > b.flt_val);
    }
    printf("error: unsupported type for sup [%d] [%d]\n", a.type, b.type);
    fi_clean_obj(a);
    fi_clean_obj(b);
    return NONE_OBJ;
}


/*****************************************
 *                                      *
 *          Boolean functions           *
 *                                      *
*****************************************/

obj_t f_not(int n, obj_t a) {
    UNUSED(n);

    if (a.type == BOOLEAN || a.type == INTEGER) {
        return BOOLEAN_OBJ(!a.int_val);
    }
    printf("error: unsupported type for not [%d]\n", a.type);
    fi_clean_obj(a);
    return NONE_OBJ;
}

obj_t f_or(int n, obj_t a, obj_t b) {
    UNUSED(n);

    if (
        (a.type == BOOLEAN || a.type == INTEGER) &&
        (b.type == BOOLEAN || b.type == INTEGER)
    ) {
        return BOOLEAN_OBJ(a.int_val || b.int_val);
    }
    printf("error: unsupported type for or [%d] [%d]\n", a.type, b.type);
    fi_clean_obj(a);
    fi_clean_obj(b);
    return NONE_OBJ;
}


obj_t f_and(int n, obj_t a, obj_t b) {
    UNUSED(n);

    if (
        (a.type == BOOLEAN || a.type == INTEGER) &&
        (b.type == BOOLEAN || b.type == INTEGER)
    ) {
        return BOOLEAN_OBJ(a.int_val && b.int_val);
    }
    printf("error: unsupported type for and [%d] [%d]\n", a.type, b.type);
    fi_clean_obj(a);
    fi_clean_obj(b);
    return NONE_OBJ;
}
