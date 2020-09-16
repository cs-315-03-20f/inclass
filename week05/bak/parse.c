/* parse.c - parsing and parse tree construction */

#include "ntcalc.h"


void parse_table_init(struct parse_table_st *pt) {
    pt->len = 0;
}

struct parse_node_st * parse_node_new(struct parse_table_st *pt) {
    struct parse_node_st *np;

    np = &(pt->table[pt->len]);
    pt->len += 1;

    return np;
}

void parse_error(char *err) {
    printf("parse_error: %s\n", err);
    exit(-1);
}

char *parse_oper_strings[] = {"PLUS", "MINUS", "MULT", "DIV", "NOT"};

void parse_tree_print_indent(int level) {
    level *= 2;
    for (int i = 0; i < level; i++) {
        printf(".");
    }
}

void parse_tree_print_expr(struct parse_node_st *np, int level) {
    parse_tree_print_indent(level);
    printf("EXPR ");

    if (np->type == EX_INTVAL) {
        printf("INTVAL %d\n", np->intval.value);
    } else if (np->type == EX_OPER2) {
        printf("OPER2 %s\n", parse_oper_strings[np->oper2.oper]);
        parse_tree_print_expr(np->oper2.left, level+1);
        parse_tree_print_expr(np->oper2.right, level+1);
    }
}

void parse_tree_print(struct parse_node_st *np) {
    parse_tree_print_expr(np, 0);
    
}


/* These prototypes are needed for the mutual recursion between
   parse_expression() and parse_operand()
*/

struct parse_node_st * parse_program(struct parse_table_st *pt, 
                                        struct scan_table_st *st);
struct parse_node_st * parse_expression(struct parse_table_st *pt, 
                                        struct scan_table_st *st);
struct parse_node_st * parse_operand(struct parse_table_st *pt,
                                     struct scan_table_st *st);


struct parse_node_st * parse_program(struct parse_table_st *pt, 
                                        struct scan_table_st *st) {
    struct parse_node_st *np1;

    np1 = parse_expression(pt, st);

    if (!scan_table_accept(st, TK_EOT)) {
        parse_error("Expecting EOT");        
    }

    return np1;                                       
}

struct parse_oper_pair_st {
    enum scan_token_enum tkid;
    enum parse_oper_enum opid;
};

struct parse_oper_pair_st parse_oper_map[] = {
    {TK_PLUS, OP_PLUS},
    {TK_MINUS, OP_MINUS},
    {TK_MULT, OP_MULT},
    {TK_DIV, OP_DIV},
    {TK_NOT, OP_NOT},
    {TK_NONE, OP_NONE}
};

enum parse_oper_enum parse_oper_lookup(enum scan_token_enum tkid) {
    int i = 0;

    while (parse_oper_map[i].tkid != TK_NONE) {
        if (parse_oper_map[i].tkid == tkid)
            return parse_oper_map[i].opid;
        i++;
    }
    return OP_NONE;
}

bool parse_is_valid_oper(enum scan_token_enum tkid) {
    return parse_oper_lookup(tkid) != OP_NONE;
}

struct parse_node_st * parse_expression(struct parse_table_st *pt, 
                                        struct scan_table_st *st) {
    struct scan_token_st *tp;
    struct parse_node_st *np1, *np2;

    np1 = parse_operand(pt, st);

    while (true) {    
        tp = scan_table_get(st, 0);
        if (parse_is_valid_oper(tp->id)) {
            scan_table_accept(st, TK_ANY);
            np2 = parse_node_new(pt);
            np2->type = EX_OPER2;
            np2->oper2.oper = parse_oper_lookup(tp->id);
            np2->oper2.left = np1;
            np2->oper2.right = parse_operand(pt, st);
            np1 = np2;
        } else {
            break;
        }
    }

    return np1;
}

struct parse_node_st * parse_operand(struct parse_table_st *pt,
                                     struct scan_table_st *st) {
    struct scan_token_st *tp;
    struct parse_node_st *np, *np1;

    if (scan_table_accept(st, TK_INTLIT)) {
        tp = scan_table_get(st, -1);
        np1 = parse_node_new(pt);
        np1->type = EX_INTVAL;
        np1->intval.value = atoi(tp->value);
    } else if (scan_table_accept(st, TK_NOT)) {
        tp = scan_table_get(st, -1);
        np1 = parse_node_new(pt);
        np1->type = EX_OPER1;
        np1->oper1.oper = OP_NOT;
        np1->oper1.operand = parse_operand(pt, st);
        np = np1;
    } else {
        parse_error("Bad operand");
    }

    return np1;
}
