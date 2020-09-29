#include <stdbool.h>

bool in_range_c(int lower, int upper, int x) {
    if (x >= lower && x <= upper) {
        return true;
    }
    return false;
}
