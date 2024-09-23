#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H
Instruction instructions[21] = {
{
.opcode = OP_PUSH_s,
.first_operand.str = "Advapi32.dll"
},
{
.opcode = OP_IMPORT_p,
.first_operand.reg = sp
},
{
.opcode = OP_PUSH_s,
.first_operand.str = "aaaaaaaaaaaa"
},
{
.opcode = OP_MOV_r,
.first_operand.reg = r1,
.second_operand.reg = sp
},
{
.opcode = OP_MOV_r,
.first_operand.reg = rb,
.second_operand.reg = sp
},
{
.opcode = OP_PUSH_n,
.first_operand.num = 256
},
{
.opcode = OP_MOV_r,
.first_operand.reg = r2,
.second_operand.reg = sp
},
{
.opcode = OP_CALL_s,
.first_operand.str = "GetUserNameA"
},
{
.opcode = OP_IMPORT_s,
.first_operand.str = "kernel32.dll"
},
{
.opcode = OP_PUSH_s,
.first_operand.str = "bbbbbbbbbbbb"
},
{
.opcode = OP_MOV_r,
.first_operand.reg = r1,
.second_operand.reg = sp
},
{
.opcode = OP_MOV_r,
.first_operand.reg = rc,
.second_operand.reg = sp
},
{
.opcode = OP_PUSH_n,
.first_operand.num = 256
},
{
.opcode = OP_MOV_r,
.first_operand.reg = r2,
.second_operand.reg = sp
},
{
.opcode = OP_CALL_s,
.first_operand.str = "GetComputerNameA"
},
{
.opcode = OP_IMPORT_s,
.first_operand.str = "user32.dll"
},
{
.opcode = OP_XOR_r,
.first_operand.reg = r1,
.second_operand.reg = r1
},
{
.opcode = OP_MOV_r,
.first_operand.reg = r2,
.second_operand.reg = rc
},
{
.opcode = OP_MOV_r,
.first_operand.reg = r3,
.second_operand.reg = rb
},
{
.opcode = OP_MOV_n,
.first_operand.reg = r4,
.second_operand.num = 1
},
{
.opcode = OP_CALL_s,
.first_operand.str = "MessageBoxA"
}
};
#endif INSTRUCTIONS_H
