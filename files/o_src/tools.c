#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "ks.h"

typedef struct {
    obj_t *arr;
    int len;
} vars_t;

typedef struct {
    vars_t *vars;
    int len;
} all_vars_t;

all_vars_t g_vars = {NULL, 0};

void fi_clean_obj(obj_t o) {
    if (o.type == ALLOCATED_STRING) {
        free(o.str_ptr);
    }
}

void fi_clean_up(void) {
    for (int i = 0; i < g_vars.len; i++) {
        for (int j = 0; j < g_vars.vars[i].len; j++) {
            fi_clean_obj(g_vars.vars[i].arr[j]);
        }
        free(g_vars.vars[i].arr);
    }
    free(g_vars.vars);
}

void fi_create_var(int func_id, int var_id, obj_t o) {
    if (g_vars.len <= func_id) {
        g_vars.vars = realloc(g_vars.vars, sizeof(vars_t) * (func_id + 1));
        for (int i = g_vars.len; i <= func_id; i++) {
            g_vars.vars[i].arr = NULL;
            g_vars.vars[i].len = 0;
        }
        g_vars.len = func_id + 1;
    }
    
    if (g_vars.vars[func_id].len <= var_id) {
        g_vars.vars[func_id].arr = realloc(g_vars.vars[func_id].arr, sizeof(obj_t) * (var_id + 1));
        for (int i = g_vars.vars[func_id].len; i <= var_id; i++) {
            g_vars.vars[func_id].arr[i] = NONE_OBJ;
        }
        g_vars.vars[func_id].len = var_id + 1;
    }

    fi_clean_obj(g_vars.vars[func_id].arr[var_id]);
    g_vars.vars[func_id].arr[var_id] = o;
}

obj_t fi_get_var(int func_id, int var_id) {
    if (g_vars.len <= func_id) {
        return NONE_OBJ;
    }
    
    if (g_vars.vars[func_id].len <= var_id) {
        return NONE_OBJ;
    }

    return g_vars.vars[func_id].arr[var_id];
}

int fi_is(obj_t o) {
    int ret = 0;
    if (
        o.type == ALLOCATED_STRING ||
        o.type == STRING
    ) {
        if (o.str_ptr != NULL && o.str_ptr[0])
            ret = 1;
    } else if (
        o.type == INTEGER ||
        o.type == BOOLEAN
    ) {
        ret = o.int_val != 0;
    }
    else if (o.type == FLOAT) {
        ret = o.flt_val != 0.0;
    }
    else if (o.type == NONE) {
        ret = 0;
    }
    else {
        printf("fi_is: unknown type [%d]\n", o.type);
    }
    fi_clean_obj(o);
    return ret;
}
