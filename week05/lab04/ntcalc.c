/* ntcalc.c */

#include "ntcalc.h"

void ntlang_print_result(struct ntlang_config_st *nc, uint32_t result) {
    char result_str[SCAN_INPUT_LEN];

    conv_uint32_to_str(nc, result, result_str);
    printf("%s\n", result_str);
}

void ntlang_config_init(struct ntlang_config_st *cfg) {
    cfg->verbose = false;
    cfg->base = 10;
    cfg->width = 32;
    cfg->unsigned_output = false;
}

int main(int argc, char **argv) {
    struct scan_table_st scan_table;
    struct parse_table_st parse_table;
    struct parse_node_st *parse_tree;
    struct ntlang_config_st cfg;

    ntlang_config_init(&cfg);

    int len;
    uint32_t result = 0;

    for (int a = 1; a < argc; a++) {
        if (argv[a][0] == '-') {
            switch (argv[a][1]) {
                case 'e':
                    strncpy(cfg.input, argv[a+1], SCAN_INPUT_LEN);
                    len = strnlen(cfg.input, SCAN_INPUT_LEN);
                    a++;
                    break;
                case 'b':
                    cfg.base = atoi(argv[a+1]);
                    a++;
                    break;
                case 'v':
                    cfg.verbose = true;
                    break;
            }
        }
    }    

    scan_table_init(&scan_table);
    scan_table_scan(&scan_table, cfg.input, len);
    if (cfg.verbose) {
        scan_table_print(&scan_table);
    }

    parse_table_init(&parse_table);
    parse_tree = parse_expression(&parse_table, &scan_table);
    if (cfg.verbose) {
        parse_tree_print(parse_tree);
    }

    result = eval_tree(parse_tree);
    ntlang_print_result(&cfg, result);
    
    return 0;
}
