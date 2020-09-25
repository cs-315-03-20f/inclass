#include <stdio.h>

int max_s(int a, int b);
int max_c(int a, int b);

int main(int argc, char **argv) {
    int i = max_c(-1, 1);
    int j = max_s(-1, 1);

    printf("C result: %d, ASM result: %d\n", i, j);
    return 0;
}
