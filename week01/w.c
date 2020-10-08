#include <stdbool.h>
#include <stdio.h>

bool is_whitespace(char ch) {
    return ch == ' ' || ch == '\t' || ch == '\n';
}

int main(int argc, char **argv) {
    int count = 0;
    bool in_word = false;
    
    if (argc < 2) {
        printf("usage: w <path>\n");
        return -1;
    }
    
    FILE *f = fopen(argv[1], "r");
    if (!f) {
        printf("failed to open %s\n", argv[1]);
        return -1;
    }

    do {
        char ch;
        if (!fread(&ch, sizeof(char), 1, f))
            break;
        if (in_word && is_whitespace(ch))
            count++;
        in_word = !is_whitespace(ch);            
    } while(true);

    printf("%d\n", count);

    fclose(f);
    
    return 0;
}
