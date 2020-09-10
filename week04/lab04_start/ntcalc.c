/* ntcalc.c */

#include "ntcalc.h"

int main(int argc, char **argv) {
    struct scan_table_st scan_table;
    struct parse_table_st parse_table;
    struct parse_node_st *parse_tree;

    char input[SCAN_INPUT_LEN];
    int len;
    int base = 10;
    uint32_t result = 0;

    for (int a = 1; a < argc; a++) {
        if (argv[a][0] == '-') {
            switch (argv[a][1]) {
                case 'e':
                    strncpy(input, argv[a+1], SCAN_INPUT_LEN);
                    len = strnlen(input, SCAN_INPUT_LEN);
                    a++;
                    break;
                case 'b':
                    base = atoi(argv[a+1]);
                    a++;
                    break;
            }
        }
    }    

    scan_table_init(&scan_table);
    scan_table_scan(&scan_table, input, len);
    // scan_table_print(&scan_table);

    parse_table_init(&parse_table);
    parse_tree = parse_expression(&parse_table, &scan_table);
    parse_tree_print(parse_tree);

    result = eval_tree(parse_tree);
    /* you will need something like this
     * eval_tree_print(result, base);
     */
    
    return 0;
}
