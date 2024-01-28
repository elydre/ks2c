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
 *     memory allocation functions      *
 *                                      *
*****************************************/

typedef struct chain_s {
    void *addr;
    struct chain_s *next;
} chain_t;

chain_t *chain_head = NULL;
chain_t *used_chain_head = NULL;

obj_t *fi_get_address(void) {
    #if CUSTOM_MALLOC
    if (chain_head == NULL) {
        return malloc(sizeof(obj_t));
    }

    chain_t *tmp = chain_head;
    chain_head = chain_head->next;

    tmp->next = used_chain_head;
    used_chain_head = tmp;

    return tmp->addr;
    #else
    return malloc(sizeof(obj_t));
    #endif
}

void fi_free_address(obj_t *o) {
    #if CUSTOM_MALLOC
    if (o == NULL) {
        return;
    }

    chain_t *tmp;

    if (used_chain_head == NULL) {
        tmp = malloc(sizeof(chain_t));
        tmp->next = chain_head;
        tmp->addr = o;
        chain_head = tmp;
        return;
    }

    tmp = used_chain_head;
    used_chain_head = used_chain_head->next;

    tmp->addr = o;
    tmp->next = chain_head;
    chain_head = tmp;
    #else
    free(o);
    #endif
}

void fi_free_all(void) {
    #if CUSTOM_MALLOC
    chain_t *tmp = chain_head;

    while (tmp != NULL) {
        chain_t *next = tmp->next;
        free(tmp->addr);
        free(tmp);
        tmp = next;
    }
    chain_head = NULL;

    int chain_len = 0;
    tmp = used_chain_head;
    while (tmp != NULL) {
        chain_t *next = tmp->next;
        chain_len++;
        free(tmp);
        tmp = next;
    }
    used_chain_head = NULL;

    if (chain_len) {
        printf("fi_free_all: possible memory leak,"
            "%d objects found in used_chain\n", chain_len);
    }

    #endif
}

/*****************************************
 *                                      *
 *           object functions           *
 *                                      *
*****************************************/

fast_t fi_new_none_obj() {
    return (fast_t) {.type = NONE};
}

fast_t fi_new_integer_obj(int i) {
    return (fast_t) {.type = INTEGER, .int_val = i};
}

fast_t fi_new_float_obj(float f) {
    return (fast_t) {.type = FLOAT, .flt_val = f};
}

fast_t fi_new_string_obj(char *s) {
    obj_t *o = fi_get_address();
    o->str_ptr = s;
    o->ref_count = 0;
    return (fast_t) {.type = STRING, .obj_ptr = o};
}

fast_t fi_new_allocated_string_obj(char *p) {
    obj_t *o = fi_get_address();
    o->str_ptr = p;
    o->ref_count = 0;
    return (fast_t) {.type = ALLOCATED_STRING, .obj_ptr = o};
}

fast_t fi_new_boolean_obj(int b) {
    return (fast_t) {.type = BOOLEAN, .int_val = b};
}

/*****************************************
 *                                      *
 *           clean functions            *
 *                                      *
*****************************************/

void fi_clean_obj(fast_t o) {
    if (o.type != ALLOCATED_STRING && o.type != STRING) {
        return;
    }

    if (o.type == ALLOCATED_STRING) {
        free(o.obj_ptr->str_ptr);
    }
    fi_free_address(o.obj_ptr);
}

void fi_clean_up(vars_t *vars) {
    for (int j = 0; j < vars->len; j++) {
        if (vars->arr[j].type == ALLOCATED_STRING || vars->arr[j].type == STRING) {
            vars->arr[j].obj_ptr->ref_count = 0;
        }
        fi_clean_obj(vars->arr[j]);
    }
    free(vars->arr);
    fi_free_all();
}

/*****************************************
 *                                      *
 *            vars functions            *
 *                                      *
*****************************************/

void fi_create_var(vars_t *vars, int var_id, fast_t o) { 
    if (vars->len <= var_id) {
        vars->arr = realloc(vars->arr, sizeof(fast_t) * (var_id + 1));
        for (int i = vars->len; i <= var_id; i++) {
            vars->arr[i] = fi_new_none_obj();
        }
        vars->len = var_id + 1;
    }
    if (vars->arr[var_id].type == ALLOCATED_STRING || vars->arr[var_id].type == STRING) {
        vars->arr[var_id].obj_ptr->ref_count--;
        fi_clean_obj(vars->arr[var_id]);
    }

    vars->arr[var_id] = o;
    if (o.type == ALLOCATED_STRING || o.type == STRING) {
        o.obj_ptr->ref_count++;
    }
}


#if BYPASS_GETVAR
#else
fast_t fi_get_var(vars_t *vars, int var_id) {
    if (vars->len <= var_id) {
        printf("fi_get_var: var_id [%d] out of range\n", var_id);
        return fi_new_none_obj();
    }

    return vars->arr[var_id];
}
#endif

/*****************************************
 *                                      *
 *           tools functions            *
 *                                      *
*****************************************/

char *fi_get_type(char type) {
    switch (type) {
        case INTEGER:
            return "int";
        case STRING:
            return "str";
        case ALLOCATED_STRING:
            return "str";
        case BOOLEAN:
            return "bool";
        case FLOAT:
            return "float";
        case NONE:
            return "none";
        default:
            return "unknown";
    }
}

int fi_is(fast_t o) {
    int ret;
    if (
        o.type == INTEGER ||
        o.type == BOOLEAN
    ) {
        return o.int_val != 0;
    } else if (o.type == FLOAT) {
        return o.flt_val != 0.0;
    } else if (o.type == NONE) {
        return 0;
    }

    ret = 0;
    if (
        o.type == ALLOCATED_STRING ||
        o.type == STRING
    ) {
        if (o.obj_ptr->str_ptr != NULL) {
            ret = strlen(o.obj_ptr->str_ptr) > 0;
        }
    } else {
        printf("fi_is: unknown type [%d]\n", o.type);
    }
    fi_clean_obj(o);
    return ret;
}

int fi_int_val(fast_t o) {
    int ret;
    if (o.type == INTEGER) {
        return o.int_val;
    } else if (o.type == FLOAT) {
        return (int) o.flt_val;
    } else if (o.type == BOOLEAN) {
        return o.int_val;
    } else if (o.type == NONE) {
        return 0;
    }

    ret = 0;
    if (
        o.type == ALLOCATED_STRING ||
        o.type == STRING
    ) {
        if (o.obj_ptr->str_ptr != NULL) {
            ret = atoi(o.obj_ptr->str_ptr);
        }
    } else {
        printf("fi_int_val: unknown type [%d]\n", o.type);
    }
    fi_clean_obj(o);
    return ret;
}
