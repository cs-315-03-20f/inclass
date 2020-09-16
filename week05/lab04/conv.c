/* conv.h - performs conversions between string/uint and between bases */

#include <ctype.h>

#include "ntcalc.h"

uint32_t conv_str_to_uint32(char *str, uint32_t base) {
    uint32_t retval = 0;
    uint32_t place_val = 1;

    for (int i = strlen(str) - 1; i >= 0; i--) {

        char ch = tolower(str[i]);
        uint32_t digit;

        /* This handles binary and decimal digits
         * for project02: you handle hexadecimal digits
         */
         
        if (ch >= '0' && ch <= '9')
            digit = ch - '0';

        retval += digit * place_val;
        place_val *= base;
    }
    return retval;
}

void conv_uint32_to_decstr(struct ntlang_config_st *nc, uint32_t value, 
                           char *result_str) {
    uint32_t div, rem;
    int i, j = 0, len;
    int msb = nc->width - 1;
    char tmp[SCAN_INPUT_LEN];

    /* This handles non-negative numbers
     * for project02: you handle negative numbers using msb
     */

    len = 0;
    if (value == 0) {
        tmp[len++] = '0';
    } else {
        while (value != 0) {
            div = value / 10;
            rem = value % 10;
            tmp[len] = '0' + rem;
            len += 1;
            value = div;
        }
    }

    for (i = len; i > 0; i--, j++) {
        result_str[j] = tmp[i-1];
    }
    result_str[j] = '\0';
}

void conv_uint32_to_binstr(int width, uint32_t value, 
                           char *result_str) {
    int i, j;
    
    result_str[0] = '0';
    result_str[1] = 'b';
    j = 2;

    for (i = width - 1; i >= 0; i -= 1) {
        if (((value >> i) & 0b1) == 1)
            result_str[j] = '1';
        else
            result_str[j] = '0';
        j += 1;      
    }
    
    result_str[j] = '\0';
}

void conv_uint32_to_str(struct ntlang_config_st *nc, uint32_t value,
                        char *result_str) {
    uint32_t iresult;

    /* Mask value to nc->width */
#if 0 /* for project02: you write this */
     iresult = value & conv_width_mask(nc->width);
#else
    iresult = value;
#endif

    switch (nc->base) {
        case 2:
            conv_uint32_to_binstr(nc->width, iresult, result_str);
            break;
        case 10:
            conv_uint32_to_decstr(nc, iresult, result_str);
            break;
        case 16:
#if 0 /* for project02: you write this */
             conv_uint32_to_hexstr(nc->width, iresult, result_str);
#endif
            break;
    }
}
