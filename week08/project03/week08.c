#include <stdio.h>
#include <string.h>

char *strcat_c(char *dst, char *src);
char *strcat_s(char *dst, char *src);

int sum_array_rec_c(int *arr, int index, int len);
int sum_array_rec_s(int *arr, int index, int len);

int substr_c(char*, char*);
int substr_s(char*, char*);

#define ARRAY_MAX 128

int main(int argc, char **argv) {
    char buf[ARRAY_MAX];
    strncpy(buf, "hello ", ARRAY_MAX);
    strcat_c(buf, "world");
    printf("C: %s\n", buf);

    strncpy(buf, "hello ", ARRAY_MAX);
    strcat_s(buf, "world");
    printf("Assembly: %s\n", buf);

    int arr[4] = {1, 2, 3, 4};
    printf("C: %d\n", sum_array_rec_c(arr, 0, 4));
    printf("Assembly: %d\n", sum_array_rec_s(arr, 0, sizeof(arr)/sizeof(int)));

    printf("C: %d\n", substr_c("foobar", "bar"));
    printf("Assembly: %d\n", substr_s("foobar", "bar"));
    return 0;
}
