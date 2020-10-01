#include <stdio.h>

int count_zeros_c(int *arr, int len);
int count_zeros_s(int *arr, int len);

int main(int argc, char **argv) {
    int c1, c2;
    int arr[8] = {0, 1, 0, 2, 0, 3, 0, 8};

    c1 = count_zeros_c(arr, sizeof(arr)/sizeof(int));
    c2 = count_zeros_s(arr, sizeof(arr)/sizeof(int));

    printf("C: %d\nAssembly: %d\n", c1, c2);
    return 0; 
}
