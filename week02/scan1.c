#include <stdio.h>
#include <string.h>

#define MAX_TOKEN_NAME 32

typedef enum {
    TT_EOT,
    TT_PLUS,
    TT_MINUS,
    TT_MUL,
    TT_DIV,
} token_type;

typedef struct {
    char name[MAX_TOKEN_NAME];
    token_type type;
} token;

#define MAX_TOKENS 128

typedef struct {
    token list[MAX_TOKENS];
    int len;
} token_table;

void token_table_init(token_table *tbl) {
    tbl->len = 0;
}

void token_table_add(token_table *tbl, token_type t, char *n) {
    tbl->list[tbl->len].type = t;
    strncpy(tbl->list[tbl->len].name, n, MAX_TOKEN_NAME);
    tbl->len += 1;
}

char *token_table_scan(token_table *tbl, char *p, char *end) {
    if (p == end) {
        token_table_add(tbl, TT_EOT, "");
        return p;
    } else if (*p == '+') {
        token_table_add(tbl, TT_PLUS, "+");
    } else if (*p == '-') {
        token_table_add(tbl, TT_MINUS, "-");
    } else if (*p == '*') {
        token_table_add(tbl, TT_MUL, "*");
    } else if (*p == '/') {
        token_table_add(tbl, TT_DIV, "/");
    }
    return p + 1;
}

void token_table_print(token_table *tbl) {
    char *token_names[] = {"TT_EOT", "TT_PLUS", "TT_MINUS", "TT_MUL", "TT_DIV"};

    for (int i = 0; i < tbl->len; i++) {
        token *pt = &tbl->list[i];
        printf("type: %s name: \"%s\"\n", token_names[pt->type], pt->name);
    }
}

int main(int argc, char **argv) {
    token_table ttbl;
    token_table_init(&ttbl);

    char *p = "+-*/";
    char *end = &p[strlen(p)];
    do {
        p = token_table_scan(&ttbl, p, end);
    } while (p != end);
    token_table_print(&ttbl);
    return 0;
}
