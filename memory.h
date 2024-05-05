#ifndef MEMORY_H
#define MEMORY_H
#define STACK_SIZE 512
typedef unsigned char byte;
typedef union{
    unsigned short int WORD;
    struct
    {
        byte low,high;
    } BYTE;
}word;

typedef struct{
    byte v[0x10]; //registers
    word i; //index register
    word pc; //program counter
    word sp; //stack pointer
    byte dt; //delay timer
    byte st; //sound timer
    word operand; //current operand
}chip8regset;


#endif
