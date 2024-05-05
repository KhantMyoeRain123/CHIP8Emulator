#include "memory.h"
#include "chip8.h"
#include "stdio.h"
void chip8_init(chip8* cpu){

    //set program pointer to starting address 0x200
    cpu->reg_set.pc.WORD=0x200;
    //set delay and sound timers to zero
    cpu->reg_set.dt=0x00;
    cpu->reg_set.st=0x00;
    //set stack pointer to highest address as it will grow down
    cpu->reg_set.sp.WORD=0x0FFF;
}
word fetch(chip8* cpu){
    //fetch the instruction word
    byte high=cpu->memory[cpu->reg_set.pc.WORD];
    byte low=cpu->memory[cpu->reg_set.pc.WORD+1];
    word instr;
    instr.BYTE.high=high;
    instr.BYTE.low=low;

    cpu->reg_set.pc.WORD+=2; //increment to next instruction word
    return instr;
}

void set_operand(chip8* cpu,word value){
    cpu->reg_set.operand.WORD=value.WORD;
}

instr_type decode(chip8* cpu,word instr){
    //we first get the first byte since this determines the instruction class
    word head;
    head.WORD=(instr.WORD & 0xF000)>>12;
    byte last_four_bits=(instr.WORD & 0x000F);
    word last_twelve_bits;
    last_twelve_bits.WORD=(instr.WORD & 0x0FFF);
    word last_byte;
    last_byte.WORD=(instr.WORD & 0x00FF);

    switch(head.WORD){
        case 0:
            switch(last_four_bits){
                //Clear command
                case 0x0:
                printf("Fetched CLS\n");
                return CLS;
                break;
                //Return from subroutine
                case 0xE:
                printf("Fetched RET\n");
                return RET;
                break;
            }
        break;
        case 1:
            printf("Fetched JP\n");
            //set operand to last twelve bits which is the jump location
            set_operand(cpu,last_twelve_bits);

            return JP;
        break;
        case 2:
            printf("Fetched CALL\n");
            //set operand to last twelve bits which is the subroutine location
            set_operand(cpu,last_twelve_bits);

            return CALL;
        break;
        case 3:
            printf("Fetched SEb\n");
            //set operand to last byte
            set_operand(cpu,last_byte);

            return SEb;
        break;
        case 4:
        break;
        case 5:
        break;
        case 6:
        break;
        case 7:
        break;
        case 8:
        break;
        case 9:
        break;
        case 0xA:
        break;
        case 0xB:
        break;
        case 0xC:
        break;
        case 0xD:
        break;
        case 0xF:
        break;
        default:
        break;
    }
    return JP;

}

void execute(chip8* cpu,instr_type instr_t){
    switch(instr_t){
        case CLS:
        break;
        case RET:
        break;
        case JP:
        printf("Executing JP instruction.\n");
        cpu->reg_set.pc.WORD=cpu->reg_set.operand.WORD;
        printf("Setting PC to %x\n",cpu->reg_set.pc.WORD);
        break;
        case CALL:
        break;
        case SEb:
        break;
        default:
        break;

    }
}

void run(chip8* cpu){
    while(1){
        word instr=fetch(cpu);
        instr_type instr_t=decode(cpu,instr);
        execute(cpu,instr_t);
        break;
    }
}