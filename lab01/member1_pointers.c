#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define ELEMENT_LEN 32

char *names[] = {"foo", "bar", "baz", "boo", "goo"};

bool is_member(char **table, char *element) {
    char **cur = table; 
    bool rv = false;

    while (*cur != NULL) {
        if (strncmp(*cur, element, ELEMENT_LEN) == 0) {
            rv = true;
            break;
        }
        cur = cur + 1;
    }

    return rv;
}

void print_names(char *table[]) {
    for (int i = 0; table[i] != NULL; i++) {
        printf("names[%d] = %s\n", i, table[i]);
    }
}

int main(int argc, char **argv) {
    
    print_names(names);
    printf("is_member(names, \"baz\") = %d\n", is_member(names, "baz"));
    printf("is_member(names, \"goo\") = %d\n", is_member(names, "goo"));
    printf("is_member(names, \"moo\") = %d\n", is_member(names, "moo"));

    return 0;
}
