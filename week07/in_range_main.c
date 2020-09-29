#include <stdbool.h>
#include <stdio.h>

bool in_range_c(int, int, int);
bool in_range_s(int, int, int);

int main(int argc, char **argv) {
    bool i1 = in_range_c(1, 10, 5);
    bool i2 = in_range_s(1, 10, 5);
    bool i3 = in_range_c(1, 10, 15);
    bool i4 = in_range_s(1, 10, 15);

    printf("in_range_c(1,10,5) = %d, in_range_s(1,10,5) = %d\n", i1, i2);
    printf("in_range_c(1,10,15) = %d, in_range_s(1,10,15) = %d\n", i3, i4);
}
