#ifndef RAM_H
#define RAM_H

//The size of ram (number of 32-bit registers in simulated ram)
#define RAM_SIZE 1000
#define INIT_OFFSET 32       //offset in RAM when a program starts (this will be the initial value for the program counter)

void init_ram(int);    //initializes all ram registers to indicated value

int start_PC();     //returns the initial offset in RAM for the program counter

void write_ram(int, int);   //write value to RAM at especified locations

int read_ram(int);          //get value from ram 

void show_ram(int, int);     //display values in ram registers in the range given

#endif