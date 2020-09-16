/* ntcalc.h */

#ifndef _NTCALC_H
#define _NTCALC_H

#include <fcntl.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

/*
 * scan.c
 */

/*

# Scanner EBNF

tokenlist   ::= (token)*
token       ::= integer | symbol
integer     ::= digit (digit)*
symbol      ::= '+' | '-' | '*' | '/' | '(' | ')'
digit       ::= '0' | ... | '9'

# Ignore

whitespace  ::=  (' ' | '\t') (' ' | '\t')* 

*/

#define SCAN_TOKEN_LEN 32
#define SCAN_TOKEN_TABLE_LEN 1024
#define SCAN_INPUT_LEN 2048

enum scan_token_enum {
    TK_INTLIT, /* -123, 415 */
    TK_BINLIT, /* binary literal 0b011 */
    TK_LPAREN, /* ( */
    TK_RPAREN, /* ) */
    TK_PLUS,   /* + */
    TK_MINUS,  /* - */
    TK_MULT,   /* * */
    TK_DIV,    /* / */
    TK_LSL,    /* << */
    TK_NOT,    /* ~ */
    TK_EOT,    /* end of text */
    TK_ANY,    /* wildcard for parser */
};

#define SCAN_TOKEN_STRINGS {"TK_INTLIT", "TK_BINLIT", "TK_LPAREN", "TK_RPAREN", \
                            "TK_PLUS", "TK_MINUS", "TK_MULT", "TK_DIV", "TK_LSL", \
                            "TK_NOT" "TK_EOT", "TK_ANY"};

struct scan_token_st {
    enum scan_token_enum id;
    char value[SCAN_TOKEN_LEN];
};

struct scan_table_st {
    struct scan_token_st table[SCAN_TOKEN_TABLE_LEN];
    int len;
    int next;
};

void scan_table_init(struct scan_table_st *tt);
void scan_table_scan(struct scan_table_st *tt, char *input, int len);
void scan_table_print(struct scan_table_st *tt);

struct scan_token_st * scan_table_get(struct scan_table_st *st, int i);
bool scan_table_accept(struct scan_table_st *st, enum scan_token_enum tk_expected);


/*
 * parse.c
 */

/*
A simple grammar for the ntcalc langauge

# Parser

expression  ::= operand (operator operand)* EOT

operand     ::= integer 
              | '-' operand 
              | '(' expression ')'

*/

enum parse_expr_enum {EX_INTVAL, EX_OPER1, EX_OPER2};
enum parse_oper_enum {OP_PLUS, OP_MINUS, OP_MULT, OP_DIV, OP_LSL, OP_NOT};

struct parse_node_st {
    enum parse_expr_enum type;
    union {
        struct {uint32_t value;} intval;
        struct {enum parse_oper_enum oper;
                struct parse_node_st *expr;} oper1;
        struct {enum parse_oper_enum oper;
                struct parse_node_st *left;
                struct parse_node_st *right;} oper2;
    };
 };


#define PARSE_TABLE_LEN 1024

struct parse_table_st {
    struct parse_node_st table[PARSE_TABLE_LEN];
    int len;
    int next;
};

void parse_table_init(struct parse_table_st *pt);
struct parse_node_st * parse_expression(struct parse_table_st *pt,
                             struct scan_table_st *st);
void parse_tree_print(struct parse_node_st *np);

/*
 * ntlang.c
 */

 struct ntlang_config_st {
    char input[SCAN_INPUT_LEN];
    int base;
    int width;
    bool unsigned_output;
    bool verbose;
 };

/*
 * conv.c
 */

uint32_t conv_str_to_uint32(char *intstr, uint32_t base);
void conv_uint32_to_binstr(int width, uint32_t value, 
                           char *result_str);
void conv_uint32_to_str(struct ntlang_config_st *nc, uint32_t value, char *result_str);
 
/*
 * eval.c
 */

uint32_t eval_tree(struct parse_node_st *np);

#endif /* _NTCALC_H */
