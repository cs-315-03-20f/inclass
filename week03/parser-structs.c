
struct expr {
    int operator;
    struct {
        int i;
    } int_val_left;
    struct {
        int i;
    } int_val_right;
    struct expr sub_expr;
    struct expr sub_sub_expr;
};

union foo {
    int i;
    int j;
    char k[4];
};

union foo f;
f.i = 0;
f.j = 1;
strncpy(f.k, "foo", 4);

&f.i == &f.j == f.k

// now let's make it useful

enum bar_key {
    e_i,
    e_k,
};

struct bar {
    enum bar_key; // type?
    union {
        struct {int i;} key_i;
        struct {int j;} key_j;
    };
};

struct bar b;
b.bar_key = e_i;
b.key_i.i = 0;

