#ifndef CHIP8_H
#define CHIP8_H
#include "memory.h"
typedef struct{
    byte memory[4096]; //main memory 
    chip8regset reg_set;
}chip8;

typedef enum{
    CLS,
    RET,
    JP,
    CALL,
    SEb,
    SNEb,
    SEr,
    LD,
    ADDb,
    MOV,
    OR,
    AND,
    XOR,
    ADDr,
    SUB,
    SHR,
    SHL,
    SNEr,
    LDI,
    JPI,
    RND,
    DRW
}instr_type;

void chip8_init(chip8* cpu);
void run(chip8* cpu);
word fetch(chip8* cpu);
void set_operand(chip8* cpu, word value);
instr_type decode(chip8* cpu,word instr);
void execute(chip8* cpu,instr_type instr_t);
#endif
