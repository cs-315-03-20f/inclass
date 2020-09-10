/* interp.c */

#include "ntcalc.h"

void interp_table_init(struct interp_table_st *it) {
    it->len = 0;
}

void interp_error(char *err) {
    printf("intper_error: %s\n", err);
    exit(-1);
}

void interp_value_print(struct interp_value_st *iv) {
    if (iv->type == IT_INTVAL) {
        printf("%d\n", iv->intval.value);
    } else {
        interp_error("Bad value");
    }
}

struct interp_value_st interp_tree_expr(struct interp_table_st *it, 
                                        struct parse_node_st *np) {
    struct interp_value_st iv1, iv2;
    struct parse_node_st *np1, *np2;
    int v1, v2, result;

    if (np->type == INTVAL) {
        iv1.type = IT_INTVAL;
        iv1.intval.value = np->intval.value;
    } else if (np->type == OPER1) {
        np1 = np->oper1.expr;
        iv1 = interp_tree_expr(it, np1);
        if (np->oper1.oper == MINUS) {
            iv1.intval.value = -(iv1.intval.value);
        } else {
            interp_error("Invalid unary operator");
        }
    } else if (np->type == OPER2) {
        np1 = np->oper2.left;
        np2 = np->oper2.right;
        iv1 = interp_tree_expr(it, np1);
        iv2 = interp_tree_expr(it, np2);
        v1 = iv1.intval.value;
        v2 = iv2.intval.value;
        if (np->oper2.oper == PLUS) {
            result = v1 + v2;
        } else if (np->oper2.oper == MINUS) {
            result = v1 - v2;
        } else if (np->oper2.oper == MULT) {
            result = v1 * v2;
        } else if (np->oper2.oper == DIV) {
            result = v1 / v2;
        }
        iv1.type = IT_INTVAL;
        iv1.intval.value = result;
    }
    return iv1;
}

void interp_tree(struct interp_table_st *it, struct parse_node_st *np, bool show) {
    struct interp_value_st iv;
    
    iv = interp_tree_expr(it, np);
    interp_value_print(&iv);
}
