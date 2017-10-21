#include "ram.h"
#include <stdio.h>
#include <stdlib.h>  //needed for the abort function
#include "bases.h"

//Start RAM
int RAM[RAM_SIZE];

void init_ram(int seed){
    int i;
    for(i=0; i<RAM_SIZE; ++i){
        RAM[i] = seed;
    }
    printf("RAM initialized with seed: %d\n",seed);
}

int start_PC(){
    return INIT_OFFSET;
}

void write_ram(int value, int address){
    if (address<RAM_SIZE){
        RAM[address] = value;
    }
}

int read_ram(int address){
    int value;
    
    if (address<RAM_SIZE){
        value = RAM[address];
    }
    else {
        printf("Attempted to access RAM[%d]\n",address);
        abort();         //this will crash execution, hopefully
    }
    return value;
}

//Show values in registers in the range specified (inclusive)
void show_ram(int start_address, int end_address){
    int i;
    for(i=start_address; i<=end_address; ++i){
        printf("Register %03d: %010u  ",i, read_ram(i)); hex32(read_ram(i));
        //printf("Register %03d: % 10d\n",i,RAM[i]);
    }
}