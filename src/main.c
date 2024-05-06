#include "../headers/chip8.h"

int main(){
    chip8 cpu;
    chip8_init(&cpu);
    cpu.memory[0x200]=0x22;
    cpu.memory[0x201]=0x06;
    cpu.memory[0x206]=0x00;
    cpu.memory[0x207]=0xE0;

    run(&cpu);
    return 0;
}
