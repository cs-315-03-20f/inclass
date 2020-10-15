#include <stdint.h>
#include <stdio.h>

uint32_t add_s(uint32_t, uint32_t);

uint32_t code[16];

// Make the data processing opcode a subtract
uint32_t make_subtract(uint32_t i) {
    #define OPCODE_BIT 21
    #define SUB_OPCODE 0b0010

    // clear out bits 21-24
    i &= 0xFE1FFFFF; // or 0b11111110000111111111111111111111
    // set bits 21-24 to be the opcode for SUB
    i |= (SUB_OPCODE << OPCODE_BIT);
    return i;
}

int encode(uint32_t *dst, uint32_t *src) {
    uint32_t (*fp)(uint32_t, uint32_t); // fp is a ptr to a func which takes two uint32 and returns uint32
    dst[0] = make_subtract(*src);
    dst[1] = *(src + 1);
    fp = (uint32_t (*)(uint32_t, uint32_t)) dst;
    return fp(1, 2);
}

int main() {
    uint32_t r = encode(code, (uint32_t*) add_s);
    printf("sum: %d\n", r);
    return 0;    
}
