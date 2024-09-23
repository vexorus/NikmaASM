#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <windows.h>

#include "OpcodeFunctions.h"    
#include "Enums.h"

#define GET_FIRST_OPERAND_REG vm->instructions[i].first_operand.reg
#define GET_FIRST_OPERAND_NUM vm->instructions[i].first_operand.num
#define GET_FIRST_OPERAND_STR vm->instructions[i].first_operand.str

#define GET_SECOND_OPERAND_REG vm->instructions[i].second_operand.reg
#define GET_SECOND_OPERAND_NUM vm->instructions[i].second_operand.num
#define GET_SECOND_OPERAND_STR vm->instructions[i].second_operand.str

#define LOAD_STR_IN_STACK \
size_t str_len = strlen(str) + 1; \
size_t alignment = 4; \
size_t padded_len = str_len + (alignment - (str_len % alignment)) % alignment; \
memcpy(vm->registers[sp]-padded_len, str, str_len); \
if (padded_len > str_len) { \
    memset(vm->registers[sp]-padded_len+str_len, 0, padded_len-str_len); \
} \
vm->registers[sp] -= padded_len

#define LOAD_NUM_IN_STACK                          \
    memcpy(vm->registers[sp]-4, &num, 4);               \
    vm->registers[sp] -= 4;

void Error(char *text){
    printf("%s\n", text);
    _getch();
    exit(EXIT_FAILURE);
}
void mov(VM *vm, int8_t mode, int i) {
    if (mode) {
        int8_t first_reg = GET_FIRST_OPERAND_REG;
        int8_t second_reg = GET_SECOND_OPERAND_REG;
        vm->registers[first_reg] = vm->registers[second_reg];
    } else {
        int8_t first_reg = GET_FIRST_OPERAND_REG;
        int32_t num = GET_SECOND_OPERAND_NUM;
        vm->registers[first_reg] = num;
    }
}
void add(VM *vm, int8_t mode, int i) {
    if (mode) {
        int8_t first_reg = GET_FIRST_OPERAND_REG;
        int8_t second_reg = GET_SECOND_OPERAND_REG;
        vm->registers[first_reg] += vm->registers[second_reg];
    } else {
        int8_t first_reg = GET_FIRST_OPERAND_REG;
        int32_t num = GET_SECOND_OPERAND_NUM;
        vm->registers[first_reg] += num;
    }
}
void sub(VM *vm, int8_t mode, int i) {
    if (mode) {
        int8_t first_reg = GET_FIRST_OPERAND_REG;
        int8_t second_reg = GET_SECOND_OPERAND_REG;
        vm->registers[first_reg] -= vm->registers[second_reg];
    } else {
        int8_t first_reg = GET_FIRST_OPERAND_REG;
        int32_t num = GET_SECOND_OPERAND_NUM;
        vm->registers[first_reg] -= num;
    }
}
void mul(VM *vm, int8_t mode, int i) {
    if (mode) {
        int8_t first_reg = GET_FIRST_OPERAND_REG;
        int8_t second_reg = GET_SECOND_OPERAND_REG;
        vm->registers[first_reg] *= vm->registers[second_reg];
    } else {
        int8_t first_reg = GET_FIRST_OPERAND_REG;
        int32_t num = GET_SECOND_OPERAND_NUM;
        vm->registers[first_reg] *= num;
    }
}
void Div(VM *vm, int8_t mode, int i) {
    if (mode) {
        int8_t first_reg = GET_FIRST_OPERAND_REG;
        int8_t second_reg = GET_SECOND_OPERAND_REG;
        if (!vm->registers[second_reg]) {
            Error("DIV error: division by zero!");
        }
        vm->registers[first_reg] /= vm->registers[second_reg];
    } else {
        int8_t first_reg = GET_FIRST_OPERAND_REG;
        int32_t num = GET_SECOND_OPERAND_NUM;
        if (!num) {
            Error("DIV error: division by zero error!");
        }
        vm->registers[first_reg] /= num;
    }
}
void mod(VM *vm, int8_t mode, int i) {
    if (mode) {
        int8_t first_reg = GET_FIRST_OPERAND_REG;
        int8_t second_reg = GET_SECOND_OPERAND_REG;
        vm->registers[first_reg] %= vm->registers[second_reg];
    } else {
        int8_t first_reg = GET_FIRST_OPERAND_REG;
        int32_t num = GET_SECOND_OPERAND_NUM;
        vm->registers[first_reg] %= num;
    }
}
void xor (VM * vm, int8_t mode, int i) {
    if (mode) {
        int8_t first_reg = GET_FIRST_OPERAND_REG;
        int8_t second_reg = GET_SECOND_OPERAND_REG;
        vm->registers[first_reg] ^= vm->registers[second_reg];
    } else {
        int8_t first_reg = GET_FIRST_OPERAND_REG;
        int32_t num = GET_SECOND_OPERAND_NUM;
        vm->registers[first_reg] ^= num;
    }
} 
void and (VM * vm, int8_t mode, int i) {
    if (mode) {
        int8_t first_reg = GET_FIRST_OPERAND_REG;
        int8_t second_reg = GET_SECOND_OPERAND_REG;
        vm->registers[first_reg] &= vm->registers[second_reg];
    } else {
        int8_t first_reg = GET_FIRST_OPERAND_REG;
        int32_t num = GET_SECOND_OPERAND_NUM;
        vm->registers[first_reg] &= num;
    }
}
void or (VM * vm, int8_t mode, int i) {
    if (mode) {
        int8_t first_reg = GET_FIRST_OPERAND_REG;
        int8_t second_reg = GET_SECOND_OPERAND_REG;
        vm->registers[first_reg] |= vm->registers[second_reg];
    } else {
        int8_t first_reg = GET_FIRST_OPERAND_REG;
        int32_t num = GET_SECOND_OPERAND_NUM;
        vm->registers[first_reg] |= num;
    }
}
void push(VM *vm, int8_t mode, int i) {
    if (vm->registers[sp] <= vm->stack) {
        Error("PUSH error: stack overflow!");
    }
    if (mode == 1) {
        int8_t first_reg = GET_FIRST_OPERAND_REG;
        int32_t num = vm->registers[first_reg];
        LOAD_NUM_IN_STACK;
    }
    if (mode == 2) {
        char *str = GET_FIRST_OPERAND_STR;
        LOAD_STR_IN_STACK;
    } else {
        int32_t num = GET_FIRST_OPERAND_NUM;
        LOAD_NUM_IN_STACK;
    }
}
void pop(VM *vm, int i) {
    if (vm->registers[sp] < vm->stack) {
        Error("POP error: stack underflow!");
    }
    int8_t first_reg = GET_FIRST_OPERAND_REG;
    int32_t *ptr = vm->registers[sp];
    vm->registers[first_reg] = *ptr;
    vm->registers[sp] += 4;
    *ptr = 0;
}
void cmp(VM *vm, int8_t mode, int i) {
    if (mode) {
        int8_t first_reg = GET_FIRST_OPERAND_REG;
        int8_t second_reg = GET_SECOND_OPERAND_REG;
        if (vm->registers[first_reg] == vm->registers[second_reg]) {
            vm->flag = 1;
        } else {
            vm->flag = 0;
        }
    }
    if (mode == 2) {
        int8_t first_reg = GET_FIRST_OPERAND_REG;
        int8_t second_reg = GET_SECOND_OPERAND_REG;
        int8_t result = strcmp((char *)(vm->registers[first_reg]), (char *)(vm->registers[second_reg]));
        if (!result) {
            vm->flag = 1;
        } else {
            vm->flag = 0;
        }
    } else {
        int8_t first_reg = GET_FIRST_OPERAND_REG;
        int32_t num = GET_SECOND_OPERAND_NUM;
        if (vm->registers[first_reg] == num) {
            vm->flag = 1;
        } else {
            vm->flag = 0;
        }
    }
}
void jz(VM *vm, int8_t mode, int i) {
    if (mode) {
        if (!vm->flag) {
            int8_t first_reg = GET_FIRST_OPERAND_REG;
            int32_t jump_offset = vm->registers[first_reg];
            int32_t jump_address = vm->registers[ip] + jump_offset;
            if (jump_address + 1 < vm->instructions_count) {
                vm->registers[ip] = jump_address;
            } else {
                Error("JZ error: invalid jump address");
            }
        }
    } else {
        if (!vm->flag) {
            int8_t jump_offset = vm->instructions[i].first_operand.num;
            int32_t jump_address = vm->registers[ip] + jump_offset;
            if (jump_address + 1 < vm->instructions_count) {
                vm->registers[ip] = jump_address;
            } else {
                Error("JZ error: invalid jump address");
            }
        }
    }
}
void jnz(VM *vm, int8_t mode, int i) {
    if (mode) {
        if (vm->flag) {
            int8_t first_reg = GET_FIRST_OPERAND_REG;
            int32_t jump_offset = vm->registers[first_reg];
            int32_t jump_address = vm->registers[ip] + jump_offset;
            if (jump_address + 1 < vm->instructions_count) {
                vm->registers[ip] = jump_address;
            } else {
                Error("JNZ error: invalid jump address");
            }
        }
    } else {
        if (vm->flag) {
            int8_t jump_offset = vm->instructions[i].first_operand.num;
            int32_t jump_address = vm->registers[ip] + jump_offset;
            if (jump_address + 1 < vm->instructions_count) {
                vm->registers[ip] = jump_address;
            } else {
                Error("JNZ error: invalid jump address");
            }
        }
    }
}
void jmp(VM *vm, int8_t mode, int i) {
    if (mode) {
        int8_t first_reg = GET_FIRST_OPERAND_REG;
        int32_t jump_offset = vm->registers[first_reg];
        int32_t jump_address = vm->registers[ip] + jump_offset;
        if (jump_address + 1 < vm->instructions_count) {
            vm->registers[ip] = jump_address;
        } else {
            Error("JMP error: invalid jump address");
        }
    } else {
        int8_t jump_offset = vm->instructions[i].first_operand.num;
        int32_t jump_address = vm->registers[ip] + jump_offset;
        if (jump_address + 1 < vm->instructions_count) {
            vm->registers[ip] = jump_address;
        } else {
            Error("JMP error: invalid jump address");
        }
    }
}
void standartInput(VM *vm, int i) {
    char *str = calloc(vm->stack_max, sizeof(char));
        if (fgets(str, vm->stack_max, stdin) != NULL) { 
            if (str[strlen(str) - 1] == '\n') {         
                str[strlen(str) - 1] = '\0';             
            }                                            
            LOAD_STR_IN_STACK;
        } else {                                         
            Error("STDIN error: writing to the standard input failed");                    
        }                                                     
}
void standartOutput(VM *vm, int8_t mode, int i)
{
    int8_t first_reg = GET_FIRST_OPERAND_REG;
    if (mode) {
        printf("%s", vm->registers[first_reg]); 
    } else {
        printf("%d", vm->registers[first_reg]); 
    }
}
void exitProc(VM *vm, int8_t mode, int i)
{
    if (mode) {
        int8_t first_reg = GET_FIRST_OPERAND_REG;
        exit(vm->registers[first_reg]);
    } else {
        int8_t num = GET_FIRST_OPERAND_NUM;
        exit(num);
    }
}
void import(VM *vm, int8_t mode, int i) {
    if (mode) {
        int8_t first_reg = GET_FIRST_OPERAND_REG;
        HMODULE handle = LoadLibrary((char *)(vm->registers[first_reg]));
        if (handle == NULL)
        {
            Error("IMPORT error: failed to load dll");
        }
        else
        {
            vm->registers[ra] = (uint32_t)handle;
        }
    } else {
        char *str = GET_FIRST_OPERAND_STR;
        HMODULE handle = LoadLibrary(str);
        if (handle == NULL)
        {
            Error("IMPORT error: failed to load dll");
        }
        else
        {
            vm->registers[ra] = (uint32_t)handle;
        }
    }
}
void call(VM *vm, int8_t mode, int i) {
    if (vm->registers[ra] == 0)
        {
            Error("CALL error: no dll loaded");
        }
    if (mode) {
        int8_t first_reg = GET_FIRST_OPERAND_REG;
        FARPROC func = GetProcAddress((HMODULE)vm->registers[ra], (char *)(vm->registers[first_reg]));
        if (func == NULL)
        {
            Error("CALL error: func null");
        }
        typedef int (*FuncType)(void *, void *, void *, void *, void *, void *, void *);
        FuncType typed_func = (FuncType)func;
        void *args[7];
        args[0] = (void *)(uintptr_t)vm->registers[r1];
        args[1] = (void *)(uintptr_t)vm->registers[r2];
        args[2] = (void *)(uintptr_t)vm->registers[r3];
        args[3] = (void *)(uintptr_t)vm->registers[r4];
        args[4] = (void *)(uintptr_t)vm->registers[r5];
        args[5] = (void *)(uintptr_t)vm->registers[r6];
        args[6] = (void *)(uintptr_t)vm->registers[r7];
        int result = typed_func(args[0], args[1], args[2], args[3], args[4], args[5], args[6]);
        vm->registers[ra] = result;
    } else {
        char *str = GET_FIRST_OPERAND_STR;
        FARPROC func = GetProcAddress((HMODULE)vm->registers[ra], str);
        if (func == NULL)
        {
            Error("CALL error: func null");
        }
        typedef int (*FuncType)(void *, void *, void *, void *, void *, void *, void *);
        FuncType typed_func = (FuncType)func;
        void *args[7];
        args[0] = (void *)(uintptr_t)vm->registers[r1];
        args[1] = (void *)(uintptr_t)vm->registers[r2];
        args[2] = (void *)(uintptr_t)vm->registers[r3];
        args[3] = (void *)(uintptr_t)vm->registers[r4];
        args[4] = (void *)(uintptr_t)vm->registers[r5];
        args[5] = (void *)(uintptr_t)vm->registers[r6];
        args[6] = (void *)(uintptr_t)vm->registers[r7];
        int result = typed_func(args[0], args[1], args[2], args[3], args[4], args[5], args[6]);
        vm->registers[ra] = result;
    }
}
void clr(VM *vm) {
    memset(vm->stack, 0, vm->stack_max * sizeof(int32_t));
    vm->registers[sp] = vm->stack + vm->stack_max;
}
