/* codegen.c - machine code generation */

#include "armasm.h"

struct codegen_map_st codegen_opcode_map[] = CODEGEN_OPCODE_MAP;
struct codegen_map_st codegen_bcc_map[] = CODEGEN_BCC_MAP;

#define COND_BIT 28

void codegen_error(char *err) {
    printf("codegen_error: %s\n", err);
    exit(-1);
}

void codegen_table_init(struct codegen_table_st *ct, struct parse_node_st *tree) {
    ct->len = 0;
    ct->next = 0;
    ct->tree = tree;
}

void codegen_add_inst(struct codegen_table_st *ct, uint32_t inst) {
    ct->table[ct->len] = inst;
    ct->len += 1;
}

uint32_t codegen_lookup(char *name, struct codegen_map_st *map, int map_len) {
    int i;
    for (i = 0; i < map_len; i++) {
        if (strncmp(name, map[i].name, SCAN_TOKEN_LEN) == 0) {
            return map[i].bits;
        }
    }

    codegen_error(name);
    return (uint32_t) -1;
}

uint32_t codegen_lookup_opcode(char *name) {
    int len = sizeof(codegen_opcode_map) / sizeof(codegen_opcode_map[0]);
    return codegen_lookup(name, codegen_opcode_map, len);
}

void codegen_dp_common(struct codegen_table_st *ct, uint32_t imm, uint32_t op, 
    uint32_t set_status, uint32_t rn, uint32_t rd, uint32_t op2) {

    const uint32_t DP_IMM_BIT = 25;
    const uint32_t DP_OP_BIT  = 21;
    const uint32_t DP_S_BIT   = 20;
    const uint32_t DP_RN_BIT  = 16;
    const uint32_t DP_RD_BIT  = 12;
    uint32_t inst = 0;

    inst = (COND_AL << COND_BIT)
        | (imm << DP_IMM_BIT)
        | (op  << DP_OP_BIT)
        | (set_status << DP_S_BIT)
        | (rn  << DP_RN_BIT)
        | (rd  << DP_RD_BIT)
        | op2;
    codegen_add_inst(ct, inst);
}

void codegen_dp3(struct codegen_table_st *ct, struct parse_node_st *np) {
    codegen_dp_common(
        ct,
        0, /*imm*/
        codegen_lookup_opcode(np->stmt.inst.name),
        0, /* set status */
        np->stmt.inst.dp3.rn,
        np->stmt.inst.dp3.rd,
        np->stmt.inst.dp3.rm);
}

void codegen_mem_common(struct codegen_table_st *ct, char *name, uint32_t imm, uint32_t rd, 
    uint32_t rn, uint32_t updown, uint32_t offset) {
    const uint32_t MEM_CONST_BIT = 26;
    const uint32_t MEM_IMM_BIT = 25;
    const uint32_t MEM_PRE_BIT = 24;
    const uint32_t MEM_UPDOWN_BIT = 23;
    const uint32_t MEM_LDRSTR_BIT = 20;
    const uint32_t MEM_RN_BIT = 16;
    const uint32_t MEM_RD_BIT = 12;

    uint32_t ls = !strcmp(name, "ldr") ? 1 : 0;
    uint32_t inst = 0; /* imm = 0, byteword = 0, writeback = 0 */
    inst = (COND_AL << COND_BIT)
        | (0b01 << MEM_CONST_BIT)
        | (imm  << MEM_IMM_BIT)
        | (1 << MEM_PRE_BIT)
        | (updown << MEM_UPDOWN_BIT)
        | (ls << MEM_LDRSTR_BIT)
        | (rn << MEM_RN_BIT)
        | (rd << MEM_RD_BIT)
        | offset;
    codegen_add_inst(ct, inst);
}

#if 0
ldr r0, [r1, ip] /* register form, imm bit is 1, offset is 12 */
ldr r0, [r1, #4] /* immediate form, imm bit is 0, offset is 4 */
ldr r0, [r1, #0] /* immediate form, imm bit is 0, offset is 0 */
#endif

void codegen_mem(struct codegen_table_st *ct, struct parse_node_st *np) {
    codegen_mem_common(
        ct,
        np->stmt.inst.name,
        1, /*imm*/
        np->stmt.inst.mem.rd,
        np->stmt.inst.mem.rn,
        1, /*up*/
        np->stmt.inst.mem.rm
    );
}

void codegen_memi(struct codegen_table_st *ct, struct parse_node_st *np) {
    codegen_mem_common(
        ct,
        np->stmt.inst.name,
        0, /*imm*/
        np->stmt.inst.memi.rd,
        np->stmt.inst.memi.rn,
        1, /*up*/
        np->stmt.inst.memi.imm
    );
}

void codegen_bx(struct codegen_table_st *ct, struct parse_node_st *np) {
    const uint32_t BX_CODE_BIT = 4;
    const uint32_t bx_code = 0b000100101111111111110001;

    uint32_t inst = (COND_AL << COND_BIT)
        | (bx_code << BX_CODE_BIT)
        | np->stmt.inst.bx.rn;
    codegen_add_inst(ct, inst);
}

void codegen_mul(struct codegen_table_st *ct, struct parse_node_st *np) {
    const uint32_t MUL_RD_BIT = 16;
    const uint32_t MUL_RS_BIT = 8;
    const uint32_t MUL_CONST_BIT = 4;

    uint32_t inst = 0;
    inst |= (COND_AL << COND_BIT)
        | (np->stmt.inst.mul.rd << MUL_RD_BIT)
        | (np->stmt.inst.mul.rs << MUL_RS_BIT)
        | (0b1001 << MUL_CONST_BIT)
        | np->stmt.inst.mul.rm;
    codegen_add_inst(ct, inst);
}

void codegen_inst(struct codegen_table_st *ct, struct parse_node_st *np) {

    switch (np->stmt.inst.type) {
        case DP3 : codegen_dp3(ct, np); break;
        case BX  : codegen_bx(ct, np); break;
        case MEM : codegen_mem(ct, np); break;
        case MEMI: codegen_memi(ct, np); break;
        case MUL : codegen_mul(ct, np); break;
        default  : codegen_error("unknown stmt.inst.type");
    }
}

void codegen_stmt(struct codegen_table_st *ct, struct parse_node_st *np) {

    if (np->type == INST) {
        codegen_inst(ct, np);
    } else if (np->type == SEQ) {
        codegen_stmt(ct, np->stmt.seq.left);
        codegen_stmt(ct, np->stmt.seq.right);
    }
}

void codegen_print_hex(struct codegen_table_st *ct) {
    int i;

    printf("v2.0 raw\n");
    for (i = 0; i < ct->len; i++) {
        printf("%8X\n", ct->table[i]);
    }
}

void codegen_write(struct codegen_table_st *ct, char *path) {
    int i;
    FILE *obj = fopen(path, "w");

    fprintf(obj, "v2.0 raw\n");
    for (i = 0; i < ct->len; i++) {
        fprintf(obj, "%8X\n", ct->table[i]);
    }
    fclose(obj);
}

void codegen_hex_write(struct codegen_table_st *ct, struct parse_node_st *np, char *path) {
    codegen_write(ct, path);
}
