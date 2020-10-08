#include <stdbool.h>
#include <stdio.h>

#include "foobar.h"

int main(int argc, char **argv) {
    struct foo f;
    f.i = 1;
    f.j = 2;

    int si = 0;
    unsigned int ui = (unsigned int) si;
    foobar(&f);

    return 0;
}
