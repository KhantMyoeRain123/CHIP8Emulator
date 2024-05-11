#include "../headers/chip8.h"
#include "../headers/reader.h"

int main(){
    chip8 cpu;
    //initialize the cpu (reset)
    chip8_init(&cpu);

    /*cpu.memory[0x200]=0x22;
    cpu.memory[0x201]=0x06;
    cpu.memory[0x202]=0x00;
    cpu.memory[0x203]=0x00;
    cpu.memory[0x206]=0x00;
    cpu.memory[0x207]=0xE0;
    cpu.memory[0x208]=0x00;
    cpu.memory[0x209]=0xEE;
    */
   read_file("../tests/src.cp8",&cpu);

    run(&cpu);
    return 0;
}
