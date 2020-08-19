/*
 * replace.c - Starter code for CS315 Lab01 mail merge
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Key/value map
 */
#define MAP_KEY_LEN 64
#define MAP_VALUE_LEN 64
#define MAP_TABLE_LEN 128

struct map_pair_st {
    char key[MAP_KEY_LEN];
    char value[MAP_VALUE_LEN];
};

struct map_st {
    struct map_pair_st table[MAP_TABLE_LEN];
    int count;
};

void map_init(struct map_st *map) {
    map->count = 0;
}

void map_add(struct map_st *map, char *key, char *value) {
    if (map->count >= MAP_TABLE_LEN) {
        printf("No more room in map.\n");
        exit(-1);
    }
    strncpy(map->table[map->count].key, key, MAP_KEY_LEN);
    strncpy(map->table[map->count].value, value, MAP_VALUE_LEN);
    map->count += 1;
}

char * map_lookup(struct map_st *map, char *key) {
    int i;
    char *value = NULL;

    for (i = 0; i < map->count; i++) {
        if (strncmp(key, map->table[i].key, MAP_KEY_LEN) == 0) {
            value = map->table[i].value;
        }
    }

    return value;
}

/*
 * Replace
 */
enum {
    ARG_IPATH = 1,
    ARG_OPATH,
    ARG_FIRST_KEY
};

bool is_word_char(char ch) {
    return ch != ' ' && ch != '\t' && ch != '\n';
}

int main(int argc, char **argv) {

    /*
     * Your replace implementation goes here
     */

    return 0;
}
