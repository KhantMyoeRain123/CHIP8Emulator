#include "chip8.h"

int main(){
    chip8 cpu;
    chip8_init(&cpu);
    cpu.memory[0x200]=0x12;
    cpu.memory[0x201]=0xEE;
    run(&cpu);
    return 0;
}
