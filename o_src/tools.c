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

obj_t NONE_OBJ = {.type = NONE};

obj_t *fi_new_string_obj(char *s) {
    obj_t *o = malloc(sizeof(obj_t));
    o->type = STRING;
    o->str_ptr = s;
    o->ref_count = 0;
    return o;
}

obj_t *fi_new_allocated_string_obj(char *p) {
    obj_t *o = malloc(sizeof(obj_t));
    o->type = ALLOCATED_STRING;
    o->str_ptr = p;
    o->ref_count = 0;
    return o;
}

obj_t *fi_new_integer_obj(int i) {
    obj_t *o = malloc(sizeof(obj_t));
    o->type = INTEGER;
    o->int_val = i;
    o->ref_count = 0;
    return o;
}

obj_t *fi_new_boolean_obj(int b) {
    obj_t *o = malloc(sizeof(obj_t));
    o->type = BOOLEAN;
    o->int_val = b;
    o->ref_count = 0;
    return o;
}

obj_t *fi_new_float_obj(float f) {
    obj_t *o = malloc(sizeof(obj_t));
    o->type = FLOAT;
    o->flt_val = f;
    o->ref_count = 0;
    return o;
}

/*****************************************
 *                                      *
 *           clean functions            *
 *                                      *
*****************************************/

void fi_clean_obj(obj_t *o) {
    if (o->ref_count > 0 || o->type == NONE) {
        return;
    }
    if (o->type == ALLOCATED_STRING) {
        free(o->str_ptr);
    }
    free(o);
}

void fi_clean_up(vars_t *vars) {
    for (int j = 0; j < vars->len; j++) {
        vars->arr[j]->ref_count = 0;
        fi_clean_obj(vars->arr[j]);
    }
    free(vars->arr);
}

/*****************************************
 *                                      *
 *            vars functions            *
 *                                      *
*****************************************/

void fi_create_var(vars_t *vars, int var_id, obj_t *o) { 
    if (vars->len <= var_id) {
        vars->arr = realloc(vars->arr, sizeof(obj_t *) * (var_id + 1));
        for (int i = vars->len; i <= var_id; i++) {
            vars->arr[i] = &NONE_OBJ;
        }
        vars->len = var_id + 1;
    }
    vars->arr[var_id]->ref_count--;
    fi_clean_obj(vars->arr[var_id]);

    vars->arr[var_id] = o;
    o->ref_count++;
}

obj_t *fi_get_var(vars_t *vars, int var_id) {
    if (vars->len <= var_id) {
        return &NONE_OBJ;
    }

    return vars->arr[var_id];
}

int fi_is(obj_t *o) {
    int ret = 0;
    if (
        o->type == ALLOCATED_STRING ||
        o->type == STRING
    ) {
        if (o->str_ptr != NULL && o->str_ptr[0])
            ret = 1;
    } else if (
        o->type == INTEGER ||
        o->type == BOOLEAN
    ) {
        ret = o->int_val != 0;
    }
    else if (o->type == FLOAT) {
        ret = o->flt_val != 0.0;
    }
    else if (o->type == NONE) {
        ret = 0;
    }
    else {
        printf("fi_is: unknown type [%d]\n", o->type);
    }
    fi_clean_obj(o);
    return ret;
}

int fi_int_val(obj_t *o) {
    int ret = 0;
    if (o->type == INTEGER) {
        ret = o->int_val;
    } else if (o->type == FLOAT) {
        ret = (int) o->flt_val;
    } else if (o->type == ALLOCATED_STRING) {
        ret = atoi(o->str_ptr);
    } else if (o->type == STRING) {
        ret = atoi(o->str_ptr);
    } else if (o->type == BOOLEAN) {
        ret = o->int_val;
    } else if (o->type == NONE) {
        ret = 0;
    } else {
        printf("fi_int_val: unknown type [%d]\n", o->type);
    }
    fi_clean_obj(o);
    return ret;
}
