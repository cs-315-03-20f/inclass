typedef struct {
    char buf[32];
    int i;
} foobar;

char *func(foobar *pf) {
    return &pf->buf[1];
}

int main(int argc, char **argv) {
    foobar f;
    f.i = 0;
    f.buf[0] = '\0';
    func(&f);
}
