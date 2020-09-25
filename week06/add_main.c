#include <stdio.h>

/* Declare C impl and the asm impl of add */
int add_s(int, int);
int add_c(int, int);

int main(int argc, char **argv) {
    int i = add_c(1, 2);
    int j = add_s(1, 2);
    printf("C result: %d\n ASM result: %d\n", i, j);
    return 0;
}
