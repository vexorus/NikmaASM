#ifndef OPCODE_FUNCTIONS_H
#define OPCODE_FUNCTIONS_H

#include "Structures.h"

void Error(char *text);

void mov(VM *vm, int8_t mode, int i);
void add(VM *vm, int8_t mode, int i);
void sub(VM *vm, int8_t mode, int i);
void Div(VM *vm, int8_t mode, int i);
void mul(VM *vm, int8_t mode, int i);
void mod(VM *vm, int8_t mode, int i);
void and(VM *vm, int8_t mode, int i);
void xor(VM *vm, int8_t mode, int i);
void or(VM *vm, int8_t mode, int i);
void push(VM *vm, int8_t mode, int i);
void pop(VM *vm, int i);
void cmp(VM *vm, int8_t mode, int i);
void jz(VM *vm, int8_t mode, int i);
void jnz(VM *vm, int8_t mode, int i);
void jmp(VM *vm, int8_t mode, int i);
void standartOutput(VM *vm, int8_t mode, int i);
void standartInput(VM *vm, int i);
void import(VM *vm, int8_t mode, int i);
void exitProc(VM *vm, int8_t mode, int i);
void call(VM *vm, int8_t mode, int i);
void clr(VM *vm);

#endif