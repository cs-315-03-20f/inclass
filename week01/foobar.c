#include <stdio.h>

#include "foobar.h"

void foobar(struct foo *pfoo) {
    printf("in foobar, i: %d j: %d\n", pfoo->i, pfoo->j);
}
