#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define SCAN_TOKEN_LEN 32

enum scan_token_enum {
    TK_INTEGER,
    TK_PLUS,
    TK_MINUS,
    TK_MUL,
    TK_DIV,
    TK_EOT,
};

struct scan_token_st {
    char name[SCAN_TOKEN_LEN];
    enum scan_token_enum id;
};

#define SCAN_TOKEN_TABLE_LEN 1024

struct scan_table_st {
    struct scan_token_st table[SCAN_TOKEN_TABLE_LEN];
    int len;
};

void scan_table_init(struct scan_table_st *st) {
    st->len = 0;
}

void scan_table_add(struct scan_table_st *st, enum scan_token_enum id, char *n) {
    st->table[st->len].id = id;
    strncpy(st->table[st->len].name, n, SCAN_TOKEN_LEN);
    st->len += 1;
}

bool is_digit(char c) {
/* return (c >= '0' && c <= '9') ? true : false */
    if (c >= '0' && c <= '9') {
        return true;
    }
    return false;
}

char *scan_integer(struct scan_table_st *st, char *p, char *end) {
    char str[SCAN_TOKEN_LEN];
    char *ps = str;
    str[0] = '\0';
    
    while (is_digit(*p) && p != end) {
        *ps = *p;
        ps += 1;
        p += 1;
    }
    scan_table_add(st, TK_INTEGER, str);
    return p;
}

char *scan_table_scan(struct scan_table_st *st, char *p, char *end) {
    if (p == end) {
        scan_table_add(st, TK_EOT, "");
        return NULL;
    } else if (is_digit(*p)) {
        return scan_integer(st, p, end);
    } else if (*p == '+') {
        scan_table_add(st, TK_PLUS, "+");
    } else if (*p == '-') {
        scan_table_add(st, TK_MINUS, "-");
    } else if (*p == '*') {
        scan_table_add(st, TK_MUL, "*");
    } else if (*p == '/') {
        scan_table_add(st, TK_DIV, "/");
    }
    return p + 1;
}

void scan_table_print(struct scan_table_st *st) {
    char *token_names[] = {"TK_INTEGER", "TK_PLUS", "TK_MINUS", "TK_MUL", "TK_DIV", "TK_EOT"};

    for (int i = 0; i < st->len; i++) {
        struct scan_token_st *pt = &st->table[i];
        printf("type: %s name: \"%s\"\n", token_names[pt->id], pt->name);
    }
}

int main(int argc, char **argv) {
    struct scan_table_st scan_tbl;
    scan_table_init(&scan_tbl);

    char *p = "+-*/123";
    char *end = &p[strlen(p)];
    do {
        p = scan_table_scan(&scan_tbl, p, end);
    } while (p != NULL);
    scan_table_print(&scan_tbl);
    return 0;
}
