// n - num
// r - register
// p - pointer
// s - string


enum {
    OP_MOV_n = 14, OP_MOV_r,
    OP_ADD_n, OP_ADD_r,
    OP_SUB_n, OP_SUB_r,
    OP_DIV_n, OP_DIV_r,
    OP_MUL_n, OP_MUL_r,
    OP_MOD_n, OP_MOD_r,
    OP_AND_n, OP_AND_r,
    OP_XOR_n, OP_XOR_r,
    OP_OR_n, OP_OR_r,
    OP_POP_r,
    OP_PUSH_n, OP_PUSH_r, OP_PUSH_s,
    OP_CMP_n, OP_CMP_r, OP_CMP_p,
    OP_JZ_n, OP_JZ_r,
    OP_JNZ_n, OP_JNZ_r,
    OP_JMP_n, OP_JMP_r,
    OP_STDOUT_r, OP_STDOUT_p,
    OP_STDIN,
    OP_EXIT_n, OP_EXIT_r,
    OP_IMPORT_p, OP_IMPORT_s,
    OP_CALL_p, OP_CALL_s,
    OP_CLR
};

enum {
    ra, rb, rc, rd,
    r1, r2, r3, r4, r5, r6, r7, r8,
    sp, ip
};
