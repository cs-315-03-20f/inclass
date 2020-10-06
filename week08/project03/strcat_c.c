char *strcat_c(char *dst, char *src) {
    char *d = dst;
    while (*dst != '\0')
        dst++;
    while (*src != '\0') {
        *dst = *src;
        dst++;
        src++;
    }
    *dst = '\0';
    return d;
}
