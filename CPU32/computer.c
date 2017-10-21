#include <stdio.h>
#include "cpu.h"
#include "bases.h"
#include "ram.h"
#include "print_tools.h"

void read_bin_file(char * filename){
    char line[20];
    FILE *file;             //file pointer
    unsigned int hex_instruction, ram_index;
    ram_index = start_PC();
    
    file = fopen(filename,"rt");
    while(fgets(line, 20, file) != NULL){  // get a line, up to 20 chars from fr.  done if NULL 
    
    	sscanf (line, "%i", &hex_instruction);  //read program instruction into variable 'hex_instruction'
    	
    	//Write the value read into RAM:
    	write_ram(hex_instruction,ram_index);
    	ram_index+=1;
    	//printf ("%d\n", hex_instruction);
    	//hex32(hex_instruction);
    }
    
    fclose(file);  //close file
}


int main(int argc, char *argv[]){
    int ram_seed;
    char *filename;
    
    //Initialize RAM
    if (argc>2){                    //if at least two command line arguments were passed along with this program, then assume the second one is ram seed
        if (sscanf (argv[2], "%i", &ram_seed) != 1) {       //read the argument as an integer, and if it isn't then give an error
            fprintf(stderr, "Error - seed not integer\n");
        }
    }
    else{
        ram_seed = 0;               //if no value is provided for initializing the ram, then set it to zero
    }
    init_ram(ram_seed);
    
    //Read program from file and load it into memory:
    filename = argv[1];
    read_bin_file(filename);
    
    //start the CPU
    CPU();
    
    //next lines are for testing before I get a mini assembly parser going:
    line_print();
    printf("End of Execution.\n");
    header_print("RAM STATE");
    show_ram(0,31);
    
    return 0;
}