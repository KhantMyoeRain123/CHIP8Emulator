#include "../headers/chip8.h"
#include "../headers/memory.h"
#include <stdio.h>
#include <stdlib.h>

/*
TODO:rewrite the function
*/
int read_file(char * file_name, chip8* cpu){
    FILE *file=fopen(file_name,"r");
    char byte_buffer[3];
    int i=0;//used to index memory location
    int count=0;
    int c; //current character

    if(file==NULL)
        return -1;
    
    while((c=fgetc(file))!=EOF){
        //ignore whitespaces, 0 and x
        if(c=='0' || c=='x' || c=='\n' || c=='\t' || c=='\r'){
            continue;
        }
        if(count<2){
            byte_buffer[count]=(char) c;
            count++;
        }
        else{
            byte_buffer[count]='\0';
            count=0;
            cpu->memory[PROGRAM_START+i]=(byte)atoi(byte_buffer);
            printf("Read 0x%x",cpu->memory[PROGRAM_START+i]);
            i++;
            byte_buffer[count]=(char)c; 
        }
    }

    return 0;

}