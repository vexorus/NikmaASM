#ifndef STRUCTURES_H
#define STRUCTURES_H

#define MAX_REGISTERS 14


typedef struct {
    uint8_t opcode;
    union {
        int32_t num;
        char *str;
        int8_t reg;
    } first_operand;
    union {
        int32_t num;
        char *str;
        int8_t reg;
    } second_operand;
} Instruction;

typedef struct
{
    int32_t registers[MAX_REGISTERS];
    int8_t flag;
    int32_t *stack;
    size_t stack_max;
    Instruction *instructions;
    size_t instructions_count;
} VM;

#endif