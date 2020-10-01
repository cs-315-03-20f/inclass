#include <stdio.h>

int strlen_c(char *str);
int strlen_s(char *str);

int main(int argc, char **argv) {
    int l1, l2;
    char *str = "foobar";
    
    l1 = strlen_c(str);
    l2 = strlen_s(str);

    printf("C: %d\nAssembly: %d\n", l1, l2);
    return 0;
}
