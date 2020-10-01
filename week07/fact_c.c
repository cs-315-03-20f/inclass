int fact_c(int x) {
    if (x == 1)
        return x;
    return x * fact_c(x -1);
}
