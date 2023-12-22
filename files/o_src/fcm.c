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
            fputs(o.string_ptr, stdout);
        } else if (o.type == INTEGER) {
            printf("%d", o.int_val);
        } else if (o.type == BOOLEAN) {
            printf("%s", o.int_val ? "true" : "false");
        } else if (o.type == NONE) {
            printf("none");
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
    } else {
        printf("error: unsupported type for add [%d] [%d]\n", a.type, b.type);
    }
    return NONE_OBJ;
}