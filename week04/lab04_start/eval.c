#include <stdio.h>

#include "ntcalc.h"

unsigned int eval_tree(struct parse_node_st *np) {
    unsigned int retval = 0;
    unsigned int r = 0;
    unsigned int l = 0;

    switch (np->type) {
        case EX_INTVAL:
            retval = np->intval.value;
            break;
        case EX_OPER1:
            retval = eval_tree(np->oper1.expr);
            if (np->oper1.oper == OP_MINUS) {
                retval = -retval;
            } else {
                printf("unsupported unary operator\n");
            }
            break;
        case EX_OPER2:
            r = eval_tree(np->oper2.right);
            l = eval_tree(np->oper2.left);
            switch (np->oper2.oper) {
                case OP_PLUS:
                    retval = l + r;
                    break;
                case OP_MINUS:
                    retval = l - r;
                    break;
                case OP_MULT:
                    retval = l * r;
                    break;
                case OP_DIV:
                    retval = l / r;
                    break;
            }
            break;
    }
    return retval;
}
