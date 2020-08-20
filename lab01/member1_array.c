#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define ELEMENT_LEN 32

char *names[] = {"foo", "bar", "baz", "boo", "goo", NULL};

bool is_member(char *table[], char *element) {
    bool rv = false;

    for (int i = 0; table[i] != NULL; i++) {
        if (strncmp(table[i], element, ELEMENT_LEN) == 0) {
            rv = true;
            break;
        }
    }

    return rv;
}

void print_names(char *table[]) {
    for (int i = 0; table[i] != NULL; i++) {
        printf("names[%d] = %s\n", i, table[i]);
    }
}

int main(int argc, char **argv) {
    int rv;
    
    print_names(names);

    rv = is_member(names, "baz");
    printf("is_member(names, \"baz\") = %d\n", rv);

    rv = is_member(names, "goo");
    printf("is_member(names, \"goo\") = %d\n", rv);

    rv = is_member(names, "moo");
    printf("is_member(names, \"moo\") = %d\n", rv);

    return 0;
}
