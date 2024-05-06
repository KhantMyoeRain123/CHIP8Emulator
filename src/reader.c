#include "../headers/chip8.h"
#include "../headers/memory.h"
#include <stdio.h>
#include <stdlib.h>
int read_file(char * file_name, chip8* cpu){
    FILE *file=fopen(file_name,"r");
    char byte_buffer[3];
    int i=0;//used to index memory location
    int count=0;
    int c; //current character

    if(file==NULL)
        return -1;
    
    while((c=fgetc(file))!=EOF){
        if(c=='0' || c=='x'){
            continue;
        }
        if(count<2){
            byte_buffer[count]=(char) c;
            count++;
        }
        else{
            byte_buffer[count]='\0';
            count=0;
            cpu->memory[PROGRAM_START+2*i]=(byte)atoi(byte_buffer);
            i++;
            byte_buffer[count]=(char)c; 
        }
    }

    return 0;

}