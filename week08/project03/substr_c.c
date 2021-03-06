#include <stdbool.h>
#include <string.h>

/* start matching s2 at s1, for len2 chars. 
   return true if all chars match
*/
bool match(char *s1, char *s2, int len2) {
    for (int i = 0; i < len2; i++)
        if (s1[i] != s2[i])
            return false;

    return true;
}

/* Find s2 in s1, return index if found */
int substr_c(char *s1, char *s2) {
    int len2 = 0;
    while (s2[len2] != '\0')
        len2++;

    int i = 0;
    while (*s1 != '\0') {
        if (match(&s1[i], s2, len2))
            return i;
        i++;
    }
    return -1;
}
