#include <stdbool.h>
#include <stdio.h>

bool is_word_char(char ch) {
    return ch != ' ' && ch != '\t' && ch != '\n';
}

int main(int argc, char **argv) {
    FILE *f;
    int count = 0;
    bool in_word = false;
    char ch;

    if (argc == 1) {
        printf("usage: wcount <path>\n");
        return -1;
    }

    f = fopen(argv[1], "r");
    if (!f) {
        printf("fopen failed\n");
        return -1;
    }

    do {
        if (!fread(&ch, sizeof(char), 1, f))
            break;
        if (in_word && !is_word_char(ch))
            count++;
        in_word = is_word_char(ch);
    } while (true);
    fclose(f);

    printf("%d\n", count);
    return 0;
}
