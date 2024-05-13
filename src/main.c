#include "../headers/chip8.h"
#include "../headers/reader.h"

int main(){
    chip8 cpu;
    //initialize the cpu (reset)
    chip8_init(&cpu);

    cpu.reg_set.v[0xF]=5;
    read_file("../tests/src.cp8",&cpu);
    run(&cpu);
    return 0;
}
