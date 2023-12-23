#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

#include "ks.h"

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
        }
        putchar(' ');
    }
    putchar('\n');
    va_end(ap);
    return NONE_OBJ;
}

obj_t f_add(int n, obj_t a, obj_t b) {
    if (n != 2) {
        printf("error: add takes 2 arguments, got %d\n", n);
        return NONE_OBJ;
    }

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
        if (a.type == ALLOCATED_STRING)
            free(a.str_ptr);
        if (b.type == ALLOCATED_STRING)
            free(b.str_ptr);
        return ALLOCATED_STRING_OBJ(buf);
    } else {
        printf("error: unsupported type for add [%d] [%d]\n", a.type, b.type);
    }
    return NONE_OBJ;
}

obj_t f_sub(int n, obj_t a, obj_t b) {
    if (n != 2) {
        printf("error: sub takes 2 arguments, got %d\n", n);
        return NONE_OBJ;
    }

    if (a.type == INTEGER && b.type == INTEGER) {
        return INTEGER_OBJ(a.int_val - b.int_val);
    } else if (a.type == FLOAT && b.type == FLOAT) {
        return FLOAT_OBJ(a.flt_val - b.flt_val);
    } else {
        printf("error: unsupported type for sub [%d] [%d]\n", a.type, b.type);
    }
    return NONE_OBJ;
}

obj_t f_mul(int n, obj_t a, obj_t b) {
    if (n != 2) {
        printf("error: mul takes 2 arguments, got %d\n", n);
        return NONE_OBJ;
    }

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
        if (a.type == ALLOCATED_STRING)
            free(a.str_ptr);
        return ALLOCATED_STRING_OBJ(buf);
    } else {
        printf("error: unsupported type for mul [%d] [%d]\n", a.type, b.type);
    }
    return NONE_OBJ;
}

obj_t f_eql(int n, obj_t a, obj_t b) {
    if (n != 2) {
        printf("error: eql takes 2 arguments, got %d\n", n);
        return NONE_OBJ;
    }

    if (a.type == INTEGER && b.type == INTEGER) {
        return BOOLEAN_OBJ(a.int_val == b.int_val);
    } else if (a.type == FLOAT && b.type == FLOAT) {
        return BOOLEAN_OBJ(a.flt_val == b.flt_val);
    } else if (
        (a.type == STRING || a.type == ALLOCATED_STRING) &&
        (b.type == STRING || b.type == ALLOCATED_STRING)
    ) {
        int res = strcmp(a.str_ptr, b.str_ptr) == 0;
        if (a.type == ALLOCATED_STRING)
            free(a.str_ptr);
        if (b.type == ALLOCATED_STRING)
            free(b.str_ptr);
        return BOOLEAN_OBJ(res);
    } else if (a.type == BOOLEAN && b.type == BOOLEAN) {
        return BOOLEAN_OBJ(a.int_val == b.int_val);
    } else if (a.type == NONE && b.type == NONE) {
        return BOOLEAN_OBJ(1);
    } else {
        printf("error: unsupported type for eql [%d] [%d]\n", a.type, b.type);
    }
    return NONE_OBJ;
}

obj_t f_inf(int n, obj_t a, obj_t b) {
    if (n != 2) {
        printf("error: inf takes 2 arguments, got %d\n", n);
        return NONE_OBJ;
    }

    if (a.type == INTEGER && b.type == INTEGER) {
        return BOOLEAN_OBJ(a.int_val < b.int_val);
    } else if (a.type == FLOAT && b.type == FLOAT) {
        return BOOLEAN_OBJ(a.flt_val < b.flt_val);
    } else {
        printf("error: unsupported type for inf [%d] [%d]\n", a.type, b.type);
    }
    return NONE_OBJ;
}

obj_t f_sup(int n, obj_t a, obj_t b) {
    if (n != 2) {
        printf("error: sup takes 2 arguments, got %d\n", n);
        return NONE_OBJ;
    }

    if (a.type == INTEGER && b.type == INTEGER) {
        return BOOLEAN_OBJ(a.int_val > b.int_val);
    } else if (a.type == FLOAT && b.type == FLOAT) {
        return BOOLEAN_OBJ(a.flt_val > b.flt_val);
    } else {
        printf("error: unsupported type for sup [%d] [%d]\n", a.type, b.type);
    }
    return NONE_OBJ;
}

obj_t f_mod(int n, obj_t a, obj_t b) {
    if (n != 2) {
        printf("error: mod takes 2 arguments, got %d\n", n);
        return NONE_OBJ;
    }

    if (a.type == INTEGER && b.type == INTEGER) {
        return INTEGER_OBJ(a.int_val % b.int_val);
    } else {
        printf("error: unsupported type for mod [%d] [%d]\n", a.type, b.type);
    }
    return NONE_OBJ;
}

obj_t f_type(int n, obj_t a) {
    if (n != 1) {
        printf("error: type takes 1 argument, got %d\n", n);
        return NONE_OBJ;
    }

    if (a.type == INTEGER) {
        return STRING_OBJ("int");
    } else if (a.type == STRING || a.type == ALLOCATED_STRING) {
        return STRING_OBJ("str");
    } else if (a.type == BOOLEAN) {
        return STRING_OBJ("bool");
    } else if (a.type == FLOAT) {
        return STRING_OBJ("float");
    } else if (a.type == NONE) {
        return STRING_OBJ("none");
    } else {
        printf("error: unknown type [%d]\n", a.type);
    }
    return NONE_OBJ;
}

obj_t f_pass(int n, obj_t a) {
    if (n != 1) {
        printf("error: pass takes 1 argument, got %d\n", n);
        return NONE_OBJ;
    }
    return a;
}

obj_t f_or(int n, obj_t a, obj_t b) {
    if (n != 2) {
        printf("error: or takes 2 arguments, got %d\n", n);
        return NONE_OBJ;
    }

    if (
        (a.type == BOOLEAN || a.type == INTEGER) &&
        (b.type == BOOLEAN || b.type == INTEGER)
    ) {
        return BOOLEAN_OBJ(a.int_val || b.int_val);
    } else {
        printf("error: unsupported type for or [%d] [%d]\n", a.type, b.type);
    }
    return NONE_OBJ;
}

obj_t f_not(int n, obj_t a) {
    if (n != 1) {
        printf("error: not takes 1 argument, got %d\n", n);
        return NONE_OBJ;
    }

    if (a.type == BOOLEAN || a.type == INTEGER) {
        return BOOLEAN_OBJ(!a.int_val);
    } else {
        printf("error: unsupported type for not [%d]\n", a.type);
    }
    return NONE_OBJ;
}

obj_t f_and(int n, obj_t a, obj_t b) {
    if (n != 2) {
        printf("error: and takes 2 arguments, got %d\n", n);
        return NONE_OBJ;
    }

    if (
        (a.type == BOOLEAN || a.type == INTEGER) &&
        (b.type == BOOLEAN || b.type == INTEGER)
    ) {
        return BOOLEAN_OBJ(a.int_val && b.int_val);
    } else {
        printf("error: unsupported type for and [%d] [%d]\n", a.type, b.type);
    }
    return NONE_OBJ;
}
