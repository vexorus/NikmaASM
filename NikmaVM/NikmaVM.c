#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <windows.h>
#include "Enums.h"
#include "OpcodeFunctions.h"
#include "Instructions.h"

char NikmaVersion[] = "1.0.0";
#define HANDLE_MOV_OPCODE \
    case OP_MOV_r: {      \
        mov(vm, 1, i);    \
        break;            \
    }                     \
    case OP_MOV_n: {      \
        mov(vm, 0, i);    \
        break;            \
    }
#define HANDLE_ADD_OPCODE \
    case OP_ADD_r: {      \
        add(vm, 1, i);    \
        break;            \
    }                     \
    case OP_ADD_n: {      \
        add(vm, 0, i);    \
        break;            \
    }
#define HANDLE_SUB_OPCODE \
    case OP_SUB_r: {      \
        sub(vm, 1, i);    \
        break;            \
    }                     \
    case OP_SUB_n: {      \
        sub(vm, 0, i);    \
        break;            \
    }
#define HANDLE_MUL_OPCODE \
    case OP_MUL_r: {      \
        mul(vm, 1, i);    \
        break;            \
    }                     \
    case OP_MUL_n: {      \
        mul(vm, 0, i);    \
        break;            \
    }
#define HANDLE_DIV_OPCODE \
    case OP_DIV_r: {      \
        Div(vm, 1, i);    \
        break;            \
    }                     \
    case OP_DIV_n: {      \
        Div(vm, 0, i);    \
        break;            \
    }
#define HANDLE_MOD_OPCODE \
    case OP_MOD_r: {      \
        mod(vm, 1, i);    \
        break;            \
    }                     \
    case OP_MOD_n: {      \
        mod(vm, 0, i);    \
        break;            \
    }
#define HANDLE_XOR_OPCODE \
    case OP_XOR_r: {      \
        xor(vm, 1, i);    \
        break;            \
    }                     \
    case OP_XOR_n: {      \
        xor(vm, 0, i);    \
        break;            \
    }
#define HANDLE_OR_OPCODE \
    case OP_OR_r: {      \
        or (vm, 1, i);   \
        break;           \
    }                    \
    case OP_OR_n: {      \
        or (vm, 0, i);   \
        break;           \
    }
#define HANDLE_AND_OPCODE \
    case OP_AND_r: {      \
        and(vm, 1, i);    \
        break;            \
    }                     \
    case OP_AND_n: {      \
        and(vm, 0, i);    \
        break;            \
    }
#define HANDLE_PUSH_OPCODE \
    case OP_PUSH_r: {      \
        push(vm, 1, i);    \
        break;             \
    }                      \
    case OP_PUSH_n: {      \
        push(vm, 0, i);    \
        break;             \
    }                      \
    case OP_PUSH_s: {      \
        push(vm, 2, i);    \
        break;             \
    }
#define HANDLE_POP_OPCODE \
    case OP_POP_r: {        \
        pop(vm, i);       \
        break;            \
    }
#define HANDLE_CMP_OPCODE \
    case OP_CMP_r: {      \
        cmp(vm, 1, i);    \
        break;            \
    }                     \
    case OP_CMP_n: {      \
        cmp(vm, 0, i);    \
        break;            \
    }                     \
    case OP_CMP_p: {      \
        cmp(vm, 2, i);    \
        break;            \
    }
#define HANDLE_JZ_OPCODE \
    case OP_JZ_r: {      \
        jz(vm, 1, i);    \
        break;           \
    }                    \
    case OP_JZ_n: {      \
        jz(vm, 0, i);    \
        break;           \
    }
#define HANDLE_JNZ_OPCODE \
    case OP_JNZ_r: {      \
        jnz(vm, 1, i);    \
        break;            \
    }                     \
    case OP_JNZ_n: {      \
        jnz(vm, 0, i);    \
        break;            \
    }
#define HANDLE_JMP_OPCODE \
    case OP_JMP_r: {      \
        jmp(vm, 1, i);    \
        break;            \
    }                     \
    case OP_JMP_n: {      \
        jmp(vm, 0, i);    \
        break;            \
    }
#define HANDLE_EXIT_OPCODE \
    case OP_EXIT_r: {      \
        exitProc(vm, 1, i);\
        break;             \
    }                      \
    case OP_EXIT_n: {      \
        exitProc(vm, 0, i);\
        break;             \
    }
#define HANDLE_STDOUT_OPCODE \
    case OP_STDOUT_p: {      \
        standartOutput(vm, 1, i);\
        break;            \
    }                     \
    case OP_STDOUT_r: {      \
        standartOutput(vm, 0, i);\
        break;            \
    }
#define HANDLE_STDIN_OPCODE \
    case OP_STDIN: {        \
        standartInput(vm, i); \
        break;              \
    }      
#define HANDLE_IMPORT_OPCODE \
    case OP_IMPORT_p: {   \
        import(vm, 1, i); \
        break;            \
    }                     \
    case OP_IMPORT_s: {   \
        import(vm, 0, i); \
        break;            \
    }                 
#define HANDLE_CALL_OPCODE\
    case OP_CALL_p: {     \
        call(vm, 1, i);   \
        break;            \
    }                     \
    case OP_CALL_s: {     \
        call(vm, 0, i);   \
        break;            \
    } 
#define HANDLE_CLR_OPCODE \
    case OP_CLR: {        \
        clr(vm);          \
        break;            \
    }                     

#ifdef DEBUG
void Debug_VM(VM *vm) {
    printf(" \nNikmaVM ver %s by vexor\nDebug mode on.\n", NikmaVersion);
    printf(" \n\nRegisters:");
    printf("\n-----------------------------\n");
    printf(" ra = %d\n rb = %d\n rc = %d\n rd = %d\n r1 = %d\n r2 = %d\n r3 = %d\n r4 = %d\n r5 = %d\n r6 = %d\n r7 = %d\n r8 = %d\n sp = %d\n ip = %d\n flag = %d\n ",
           vm->registers[ra], vm->registers[rb], vm->registers[rc], vm->registers[rd],
           vm->registers[r1], vm->registers[r2], vm->registers[r3], vm->registers[r4], vm->registers[r5], vm->registers[r6], vm->registers[r7], vm->registers[r8],
           vm->registers[sp], vm->registers[ip],
           vm->flag);
    printf("-----------------------------\n");
    
    printf(" Stack:\n---------------------------------\n");
    printf(" %-6s | %-11s | %-20s | %s\n", "Offset", "Address", "Hexadecimal", "ASCII");
    int columnCount = 0;
    for (int i = 0; i < vm->stack_max; i++) {
        unsigned char *byte_ptr = (unsigned char *)&vm->stack[i];
        printf(" %6d", columnCount);
        printf(" | ");
        printf(" %10p", (void *)(byte_ptr));
        printf(" | ");
        for (int j = 0; j < 4; j++) {
            printf(" 0x%02x", byte_ptr[j]);
        }
        printf(" | ");
        for (int j = 0; j < 4; j++) {
            if (isprint(byte_ptr[j])) {
                printf(" %c", byte_ptr[j]);
            } else {
                printf(" .");
            }
        }
        columnCount += 4;
        printf("\n");
    }
printf("\n-----------------------------\n");


    
    printf("Press any key to continue\n");
    getchar();
    system("cls");
}
#endif


void Initialize_VM(VM *vm, size_t stack_max) {
    for (int i = 0; i < MAX_REGISTERS; i++) {
        vm->registers[i] = 0;
    }
    vm->flag = 0;
    vm->stack_max = stack_max;
    vm->stack = calloc(stack_max, sizeof(int32_t));
    if (vm->stack == NULL) {
        Error("VM initialization error: stack allocation failed");
    };
    vm->registers[sp] = vm->stack + stack_max;
    #ifdef DEBUG
        printf("[DEBUG] Successful VM initialization\n");
    #endif
}

void Execute_VM(VM *vm) {
    int8_t flagDebug = 0;
    while (vm->registers[ip] < vm->instructions_count) {
        int i = vm->registers[ip];
        switch (vm->instructions[i].opcode) {
            HANDLE_MOV_OPCODE;
            HANDLE_ADD_OPCODE;
            HANDLE_SUB_OPCODE;
            HANDLE_MUL_OPCODE;
            HANDLE_DIV_OPCODE;
            HANDLE_XOR_OPCODE;
            HANDLE_MOD_OPCODE;
            HANDLE_AND_OPCODE;
            HANDLE_OR_OPCODE;
            HANDLE_PUSH_OPCODE;
            HANDLE_POP_OPCODE;
            HANDLE_CMP_OPCODE;
            HANDLE_JZ_OPCODE;
            HANDLE_JNZ_OPCODE;
            HANDLE_JMP_OPCODE;
            HANDLE_EXIT_OPCODE;
            HANDLE_STDIN_OPCODE;
            HANDLE_STDOUT_OPCODE;
            HANDLE_IMPORT_OPCODE;
            HANDLE_CALL_OPCODE;
            HANDLE_CLR_OPCODE;
            default:
                printf("OPCODE: %d", vm->instructions[i].opcode);
                Error("VM execution error: unknown opcode");
                
                break;
        }
        vm->registers[ip] += 1;
        #ifdef DEBUG
            Debug_VM(vm);
        #endif
    }
}

int main() {
    VM vm;
    Initialize_VM(&vm, 30);
    vm.instructions = instructions; 
    vm.instructions_count = sizeof(instructions) / sizeof(instructions[0]);
    Execute_VM(&vm);
    return 0;
}