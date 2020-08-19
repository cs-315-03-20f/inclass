#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define ELEMENT_LEN 32

char *names[] = {"foo", "bar", "baz", "boo", "goo"};

bool is_member(char *table[], char *element) {
    int i = 0;
    bool rv = false;

    while (table[i] != NULL) {
        if (strncmp(table[i], element, ELEMENT_LEN) == 0) {
            rv = true;
            break;
        }
        i += 1;
    }

    return rv;
}

int main(int argc, char **argv) {
    printf("is_member(names, \"baz\") = %d\n", is_member(names, "baz"));
    printf("is_member(names, \"goo\") = %d\n", is_member(names, "goo"));
    printf("is_member(names, \"moo\") = %d\n", is_member(names, "moo"));

    return 0;
}
