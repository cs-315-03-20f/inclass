#include <stdio.h>

int fact_c(int);
int fact_s(int);

int main(int argc, char **argv) {
    int f1 = fact_c(5);
    int f2 = fact_s(5);

    printf("C: %d\nAssembly: %d\n", f1, f2);
}
