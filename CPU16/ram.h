#ifndef RAM_H
#define RAM_H

#include "stdint.h"

//The size of ram (number of 32-bit registers in simulated ram)
#define RAM_SIZE 1000
#define INIT_OFFSET 32       //offset in RAM when a program starts (this will be the initial value for the program counter)

void init_ram(uint16_t);    //initializes all ram registers to indicated value

uint16_t start_PC();     //returns the initial offset in RAM for the program counter

void write_ram(uint16_t, uint16_t);   //write value to RAM at especified locations

uint16_t read_ram(uint16_t);          //get value from ram 

void show_ram(uint16_t, uint16_t);     //display values in ram registers in the range given

#endif