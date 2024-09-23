![Logo](https://github.com/vexorus/NikmaASM/blob/main/Logo.png)
<br /> <a href="https://github.com/vexorus/NikmaASM/releases/latest"> <img src="https://img.shields.io/github/v/release/vexorus/NikmaASM"></img> </a> <a href="#"> <img src="https://img.shields.io/github/downloads/vexorus/NikmaASM/total"></img> </a> <a href="https://github.com/vexorus/NikmaASM/commits/master"> <img src="https://img.shields.io/github/last-commit/vexorus/NikmaASM"></img> </a>

# NikmaASM

![Logo](https://github.com/vexorus/NikmaASM/blob/main/Debug.png)

NikmaASM is an assembly language and compiler written in C#, which translates assembly code into a C file containing an array of instruction structures. These instructions are then executed on the NikmaVM virtual processor. This project is designed for those interested in virtual machine development, assembly languages, and low-level programming.

**NikmaVM** is a 32-bit virtual processor fully written in C. The virtual machine has 14 registers for various purposes and a stack.

## NikmaASM offers programmers the following features:

- **Mathematical operations**: Support for standard arithmetic operations (addition, subtraction, etc.).
- **Logical operations**: Includes operations like and, or, xor, and others.
- **Conditional and unconditional jumps**: For controlling the flow of execution, creating loops, and branching.
- **Stack operations**: Push and pop commands for managing data on the stack.
- **Register operations**: Manipulation of values in registers.
- **External function calls**: Supports calling functions from external libraries like WinAPI via import and call instructions.
- **I/O operations**: Ability to input and output data.

> [!WARNING]
> This project is in beta testing. It may contain errors and bugs. Use at your own risk.
## Usage
```cmd
NikmaASM.exe <file.nikasm> [option]
Options:
    -h, --help     Get help
    -d, --debug    Enable VM debug
    -x64           Compile x64 (default x32)
```

# Example Instructions.h after compilation
```c
#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H
Instruction instructions[5] = {
{
.opcode = OP_MOV_n,
.first_operand.reg = ra,
.second_operand.num = 500
},
{
.opcode = OP_MOV_n,
.first_operand.reg = rc,
.second_operand.num = 100
},
{
.opcode = OP_SUB_r,
.first_operand.reg = ra,
.second_operand.reg = rc
},
{
.opcode = OP_MUL_n,
.first_operand.reg = ra,
.second_operand.num = 2
},
{
.opcode = OP_PUSH_r,
.first_operand.reg = ra
}
};
#endif INSTRUCTIONS_H
```

# Instruction Table

| Hex Value | Command   | Arguments         | Description                                                      | Example           |
|-----------|-----------|-------------------|------------------------------------------------------------------|-------------------|
| **`0x0E`** | **mov**   | *reg, num*        | Moves a numeric value into the register                           | **`mov ra, 1337`** |
| **`0x0F`** | **mov**   | *reg, reg*        | Moves the value from one register to another                      | **`mov ra, rb`**   |
| **`0x10`** | **add**   | *reg, num*        | Adds a number to the register and stores the result in the first register | **`add ra, 1337`** |
| **`0x11`** | **add**   | *reg, reg*        | Adds the values of two registers and stores the result in the first register | **`add ra, rb`**   |
| **`0x12`** | **sub**   | *reg, num*        | Subtracts a number from the register and stores the result in the first register | **`sub ra, 1337`** |
| **`0x13`** | **sub**   | *reg, reg*        | Subtracts the value of one register from another and stores the result in the first register | **`sub ra, rb`**   |
| **`0x14`** | **div**   | *reg, num*        | Divides the value of the register by a number and stores the result in the first register | **`div ra, 1337`** |
| **`0x15`** | **div**   | *reg, reg*        | Divides the value of one register by another and stores the result in the first register | **`div ra, rb`**   |
| **`0x16`** | **mul**   | *reg, num*        | Multiplies the value of the register by a number and stores the result in the first register | **`mul ra, 1337`** |
| **`0x17`** | **mul**   | *reg, reg*        | Multiplies the values of two registers and stores the result in the first register | **`mul ra, rb`**   |
| **`0x18`** | **mod**   | *reg, num*        | Stores the remainder of the division of the register by a number in the first register | **`mod ra, 1337`** |
| **`0x19`** | **mod**   | *reg, reg*        | Stores the remainder of the division of two registers in the first register | **`mod ra, rb`**   |
| **`0x1A`** | **and**   | *reg, num*        | Bitwise AND operation between the register and a number, stores the result in the first register | **`and ra, 1337`** |
| **`0x1B`** | **and**   | *reg, reg*        | Bitwise AND operation between two registers, stores the result in the first register | **`and ra, rb`**   |
| **`0x1C`** | **xor**   | *reg, num*        | Bitwise XOR operation between the register and a number, stores the result in the first register | **`xor ra, 1337`** |
| **`0x1D`** | **xor**   | *reg, reg*        | Bitwise XOR operation between two registers, stores the result in the first register | **`xor ra, rb`**   |
| **`0x1E`** | **or**    | *reg, num*        | Bitwise OR operation between the register and a number, stores the result in the first register | **`or ra, 1337`**  |
| **`0x1F`** | **or**    | *reg, reg*        | Bitwise OR operation between two registers, stores the result in the first register | **`or ra, rb`**    |
| **`0x20`** | **pop**   | *reg*             | Pops a value from the stack, stores it in the register, and increases **`sp`** by 4 | **`pop ra`**       |
| **`0x21`** | **push**  | *num*             | Pushes a numeric value onto the stack and decreases the **`sp`** register by 4 | **`push 12345`**   |
| **`0x22`** | **push**  | *reg*             | Pushes the value of a register onto the stack and decreases the **`sp`** register by 4 | **`push ra`**      |
| **`0x23`** | **push**  | *str*             | Pushes a string onto the stack and decreases the **`sp`** register by the length of the string | **`push "Hello world!"`** |
| **`0x24`** | **cmp**   | *reg, num*        | Compares the numeric value with the register, sets the flag to 1 if equal, otherwise 0 | **`cmp ra, 999`**  |
| **`0x25`** | **cmp**   | *reg, reg*        | Compares the values of two registers, sets the flag to 1 if equal, otherwise 0 | **`cmp ra, rb`**   |
| **`0x26`** | **cmp**   | *ptr, ptr*        | Compares the values of two pointers, sets the flag to 1 if equal, otherwise 0 | **`cmp [ra], [rb]`** |
| **`0x27`** | **jz**    | *num*             | Jumps by n instructions if the result is zero                       | **`jz 2`**         |
| **`0x28`** | **jz**    | *reg*             | Jumps by n instructions if the register value is zero               | **`jz ra`**        |
| **`0x29`** | **jnz**   | *num*             | Jumps by n instructions if the result is not zero                   | **`jnz 2`**        |
| **`0x2A`** | **jnz**   | *reg*             | Jumps by n instructions if the register value is not zero           | **`jnz ra`**       |
| **`0x2B`** | **jmp**   | *num*             | Jumps by n instructions                                             | **`jmp 2`**        |
| **`0x2C`** | **jmp**   | *reg*             | Jumps by n instructions stored in the register                      | **`jmp ra`**       |
| **`0x2D`** | **stdout**| *reg*             | Outputs the value of the register to standard output                | **`stdout ra`**    |
| **`0x2E`** | **stdout**| *ptr*             | Outputs data from a pointer to standard output                      | **`stdout [ra]`**  |
| **`0x2F`** | **stdin** | -                 | Reads user input and stores it in the register                      | **`stdin`**        |
| **`0x30`** | **exit**  | *num*             | Exits the program with the specified exit code                      | **`exit 100`**     |
| **`0x31`** | **exit**  | *reg*             | Exits the program, using the register value as the exit code        | **`exit ra`**      |
| **`0x32`** | **import**| *ptr*             | Imports functions from a library using a pointer from the register. Returns the library address to register **`ra`** | **`import [ra]`**  |
| **`0x33`** | **import**| *str*             | Imports functions from a library by name. Returns the library address to register **`ra`**. The function result is returned to **`ra`** | **`import user32.dll`** |
| **`0x34`** | **call**  | *ptr*             | Calls a function from a library whose address should be in register **`ra`**, using a pointer from the register | **`call [ra]`**    |
| **`0x35`** | **call**  | *str*             | Calls a function from a library whose address should be in register **`ra`**, by string. The function result is returned to register **`ra`** | **`call MessageBoxA`** |
| **`0x36`** | **clr**   | -                 | Clears the stack                                                    | **`clr`**          |

# Register Table

| Register Name | Register Description                                 |
|---------------|------------------------------------------------------|
| **`ra`**      | General-purpose register                             |
| **`rb`**      | General-purpose register                             |
| **`rc`**      | General-purpose register                             |
| **`rd`**      | General-purpose register                             |
| **`r1`**      | Register for argument 1                              |
| **`r2`**      | Register for argument 2                              |
| **`r3`**      | Register for argument 3                              |
| **`r4`**      | Register for argument 4                              |
| **`r5`**      | Register for argument 5                              |
| **`r6`**      | Register for argument 6                              |
| **`r7`**      | Register for argument 7                              |
| **`r8`**      | Register for argument 8                              |
| **`sp`**      | Stack pointer, points to the top of the stack        |
| **`ip`**      | Instruction pointer, points to the current instruction |

## Special Thanks
- [DosX](https://github.com/DosX-dev)
- [ac3ss0r](https://github.com/ac3ss0r)
- [horsicq](https://github.com/horsicq)
