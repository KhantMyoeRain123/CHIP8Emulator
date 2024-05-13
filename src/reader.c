#include "../headers/chip8.h"
#include "../headers/memory.h"
#include <stdio.h>
#include <stdlib.h>

#define BYTE_BUFFER_SIZE 5

/*
TODO:rewrite the function
*/
int read_file(char * file_name, chip8* cpu){
    printf("Reading File\n");
    FILE *file=fopen(file_name,"r");
    char byte_buffer[BYTE_BUFFER_SIZE];
    int i=0;//used to index memory location
    int count=0;
    int c; //current character

    if(file==NULL){
        printf("File not found.\n");   
        return -1;
    }
    
    
    while((c=fgetc(file))!=EOF){
        //ignore whitespaces, 0 and x
        if(c=='\n' || c=='\t' || c=='\r'){
            continue;
        }
        if(count<BYTE_BUFFER_SIZE-1){
            byte_buffer[count]=(char) c;
            count++;
        }
        else{
            byte_buffer[count]='\0';
            count=0;
            cpu->memory[PROGRAM_START+i]=(byte)strtol(byte_buffer,NULL,16);
            printf("Read 0x%x\n",cpu->memory[PROGRAM_START+i]);
            i++;
            byte_buffer[count]=(char)c; 
            count++;
        }
    }

    return 0;

}