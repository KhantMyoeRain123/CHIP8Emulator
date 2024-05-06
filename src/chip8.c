#include "../headers/memory.h"
#include "../headers/chip8.h"
#include "stdio.h"
void chip8_init(chip8* cpu){

    //set program pointer to starting address 0x200
    cpu->reg_set.pc.WORD=PROGRAM_START;
    //set delay and sound timers to zero
    cpu->reg_set.dt=0x00;
    cpu->reg_set.st=0x00;
    //set stack pointer to highest address-STACK_SIZE
    cpu->reg_set.sp.WORD=0x0FFF-STACK_SIZE;

    printf("Initializing CPU..\n");
    printf("PC is at 0x%x.\n",cpu->reg_set.pc.WORD);
    printf("Stack starts at 0x%x.\n",cpu->reg_set.sp.WORD);
    printf("------------------\n");
}
word fetch(chip8* cpu){
    printf("PC 0x%x\n",cpu->reg_set.pc.WORD);
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
    if(instr.WORD==0x0000){
        return EOP;
    }
    //we first get the first byte since this determines the instruction class
    word head;
    word last_twelve_bits;
    word last_byte;
    head.WORD=(instr.WORD & 0xF000)>>12;
    byte last_four_bits=(instr.WORD & 0x000F);
    last_twelve_bits.WORD=(instr.WORD & 0x0FFF);
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
    word first_byte_of_pc;
    word last_byte_of_pc;

    first_byte_of_pc.WORD=(cpu->reg_set.pc.WORD &0xFF00)>>8;
    last_byte_of_pc.WORD=(cpu->reg_set.pc.WORD & 0x00FF);

    switch(instr_t){
        case CLS:
        printf("Executing CLS instruction.\n");
        printf("------------------\n");
        break;
        case RET:
        printf("Executing RET instruction.\n");
        cpu->reg_set.pc.WORD=(cpu->memory[cpu->reg_set.sp.WORD-1]<<8) | (cpu->memory[cpu->reg_set.sp.WORD]);
        cpu->reg_set.sp.WORD-=2;
        printf("Stack pointer is now at 0x%x.\n",cpu->reg_set.sp.WORD);
        printf("PC is set to 0x%x.\n",cpu->reg_set.pc.WORD);
        printf("------------------\n");
        break;
        case JP:
        printf("Executing JP instruction.\n");
        cpu->reg_set.pc.WORD=cpu->reg_set.operand.WORD;
        printf("Setting PC to %x\n",cpu->reg_set.pc.WORD);
        printf("------------------\n");
        break;
        case CALL:
        printf("Executing CALL instruction.\n");
        //increment by one byte
        cpu->reg_set.sp.WORD+=1;
        //let lower address be the MSB of PC
        cpu->memory[cpu->reg_set.sp.WORD]=(byte)first_byte_of_pc.WORD;
        //increment again
        cpu->reg_set.sp.WORD+=1;
        //let higher address be the LSB of PC
        cpu->memory[cpu->reg_set.sp.WORD]=(byte)last_byte_of_pc.WORD;

        printf("Stack pointer is now at 0x%x.\n",cpu->reg_set.sp.WORD);
        printf("Top of stack (return address) has value 0x%x.\n",(cpu->memory[cpu->reg_set.sp.WORD-1]<<8)|(cpu->memory[cpu->reg_set.sp.WORD]));
        //set PC to subroutine's start address
        cpu->reg_set.pc.WORD=cpu->reg_set.operand.WORD;
        printf("Jumping to address 0x%x.\n",cpu->reg_set.pc.WORD);
        printf("------------------\n");
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
        if(instr_t==EOP){
            printf("End of Program");
            break;
        }
        execute(cpu,instr_t);
    }
}