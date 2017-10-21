#include <stdio.h>
#include "alu.h"
#include "ram.h"
#include "bases.h"
#include "bit_tools.h"
#include "print_tools.h"


unsigned int fetch_instruction(int address){
    unsigned int inst;
    
    inst = read_ram(address);
    return inst;
}

unsigned int decode(unsigned int instruction, unsigned int mask, int shift){
    unsigned int output;
    output = (instruction & mask) >> shift;
    //printf("Decode Output: %#08x\n",output);
    return output;
}

void increment_PC(int * PC){
    *PC = *PC + 1;
}

void jump_PC(int *PC, unsigned int new_address){
    *PC = INIT_OFFSET + new_address;
}

void CPU(){
    unsigned int instruction;
    unsigned int PC;    //initialize the program counter
    unsigned int MAR;   //Memory Address Register
    unsigned int DRR;   //Data Read Register
    unsigned int A;     //A register that will be used mainly by the ALU
    unsigned int inst_bits, inst_mode, Binvert, Ainvert, alu_off_flag, opcode;
    unsigned int address, short_address_one, short_address_two, dest_address;
    
    int carryOut;     //This bit will be set to 1 if the arithmetic result of the ALU has a carry at the end of the operation
    int overflow;     //this flag is set by the ALU when overflow occurs
    int zr;           //this flag will be set to 1 by the ALU if all the bits in result are 0
    
    
    /***************************************************************************/
    //Declare masks to quickly decode instructions that arrive at the CPU
    unsigned int inst_shift=26,opcode_shift=0, Binvert_shift=2, Ainvert_shift=3;
    unsigned int mask_instruction = 0xfc000000;
    unsigned int mask_opcode = 0x00000003;
    unsigned int mask_Binvert = 0x00000004;
    unsigned int mask_Ainvert = 0x00000008;
    
    //Address masks
    int long_addr_shift=0, sh_addr1_shift=21, sh_addr2_shift=16,dest_addr_shift=0;
    unsigned int mask_long_address = 0x03ffffff;
    unsigned int mask_short_address_one = 0x03e00000;
    unsigned int mask_short_address_two = 0x001f0000;
    unsigned int mask_destination_address = 0x0000ffff;
    
    /***************************************************************************/
    PC = start_PC();   //the program counter points to the beginning of the program

    int clock_counter=1;        //this stores the instruction cycle counter
    //while((clock_counter++)<60){
    //while(PC < RAM_SIZE){
    while(1){
        //First, store current Program counter value into Memory Address Register and increment PC
        printf("Instruction Cycle: %d\tPC: %d\n",clock_counter,PC);
        //show_ram(PC,PC);
        MAR = PC;
        increment_PC(&PC);
        //PC++;
        
        //Fetch instruction from memory
        instruction = fetch_instruction(MAR);
        //printf("instruction: "); hex32(instruction);
        
        /***********************************************************************/
        //Decode instructions
        inst_bits = decode(instruction, mask_instruction, inst_shift);
        //printf("Instruction: "); hex32(instruction);
        //printf("inst_bits: %#02x\n",inst_bits);
        
        //Determine instruction mode from last bit
        inst_mode = get_bit(inst_bits,5);
        //printf("inst_mode: %d\n",inst_mode);
        
        if (inst_mode==1){          //read memory as address one, address 2 and address 3
            //header_print("Instruction Mode 1");
            short_address_one = decode(instruction,mask_short_address_one,sh_addr1_shift);
            short_address_two = decode(instruction,mask_short_address_two,sh_addr2_shift);
            dest_address      = decode(instruction,mask_destination_address,dest_addr_shift);
            if (inst_bits==0x21){   //jump if greater than
                //header_print("JGT command");
                if (read_ram(short_address_one) > read_ram(short_address_two)){
                    //printf("JUMPING TO LINE %d\n",dest_address);
                    jump_PC(&PC,dest_address);
                    //PC = dest_address;      //if value in address 1 is greate than in addresss 2, then set PC to address 3
                }
            }  //END OF JUMP IF GREATER THAN
            
        }
        else{
            //header_print("SIMPLE COMMAND AREA");
            alu_off_flag = get_bit(inst_bits,4);
            //printf("ALU flag: %d\n",alu_off_flag);
            
            //Load data from memory at address
            address = decode(instruction,mask_long_address,long_addr_shift);
            DRR = read_ram(address);
            //printf("RAM[%02d]: %d\n",address, DRR);
            //show_ram(address,address);
            
            if (alu_off_flag==0){
                //header_print("ALU COMMMANDS");
                //ALU operations
                opcode = decode(inst_bits,mask_opcode,opcode_shift);
                Binvert = decode(inst_bits,mask_Binvert,Binvert_shift);
                Ainvert = decode(inst_bits,mask_Ainvert,Ainvert_shift);
                
                //Execute the instruction given and put result back into register A
                //Also set all the bits necessary, but that has more to do with the ALU
                A = ALU(A,DRR,opcode,Binvert,&carryOut, &zr, &overflow);
            }  //end of  ALU if statement
            
            else{
                //The following is placeholder code for how the CPU will perform
                //different operations. I am just taking a shortcut until I learn how to make it better
                if (inst_bits==0x11){          //load value from address into A register
                    //printf("LOAD command\n");
                    A = DRR;
                    //continue;
                }
                else if (inst_bits==0x12){     //load inmediate value into A register. Treat address as the inmediate value
                    //printf("LOADI command\n");
                    A = address;    
                    //continue;
                }
                else if (inst_bits==0x13){     //save value from register A into memory address
                    //printf("SAVE command\n");
                    write_ram(A,address);
                    //continue;
                }
                else if (inst_bits==0x14){     //increment value in register A by 1
                    //printf("INCR command\n");
                    A += 1;
                    //continue;
                }
                else if (inst_bits==0x1c){    //print value in register A to console
                    printf("A_reg: %d\n",A);
                    //continue;
                }
                else if (inst_bits==0x1d){    //change the program counter to address
                    //printf("JUMP command\n");
                    jump_PC(&PC,address);
                    //PC = address;
                    //continue;
                }
                else if (inst_bits==0x1f){    //This is the halt instruction
                    printf("Program halted execution at PC: %d\n",PC);
                    return;
                } //end of ALU else clause
            }

        }  /*End of else*/
        
        clock_counter++;
    }  //End of instruction cycle
    
    //if we jumped to this point, it means that the program counter was trying 
    //to access a memory location that does not exist
    
    //return 0;
}



void CPU_old(){
    int instruction;
    int PC;   //initialize the program counter
    int MAR;   //Memory Address Register
    int DRR;   //Data Read Register
    int A;     //A register that will be used mainly by the ALU
    int opcodes, address,Binvert, cpu_codes;
    
    int carryOut;     //This bit will be set to 1 if the arithmetic result of the ALU has a carry at the end of the operation
    int overflow;     //this flag is set by the ALU when overflow occurs
    int zr;           //this flag will be set to 1 by the ALU if all the bits in result are 0
    
    //Declare masks to quickly decode instructions that arrive at the CPU
    int op_shift=16, address_shift=0,Binvert_shift=18,CPUcodes_shift=20;
    int mask_CPUcodes= 0x00f00000;
    int mask_opcodes = 0x00030000;       //opcodes are 2 bits for now
    int mask_Binvert = 0x00040000;       //Binvert comes after the opcodes
    int mask_address = 0x0000ffff;       //covers the last 16 bits
    
    
    PC = 0;   //the program counter points to the beginning of the ram
    
    //Here we need to load the program into RAM in order to execute it    

    int clock_counter=0;
    while((clock_counter++)<100){
    //while(PC < RAM_SIZE){
        //First, store current Program counter value into Memory Address Register and increment PC
        printf("Clock Cycle: %d\tPC: %d\n",clock_counter,PC);
        show_ram(PC,PC);
        MAR = PC;
        increment_PC(&PC);
        //PC++;
        
        //Fetch instruction from memory
        instruction = fetch_instruction(MAR);
        //printf("instruction: "); hex32(instruction);
        
        //Decode instructions
        cpu_codes = decode(instruction, mask_CPUcodes, CPUcodes_shift);
        opcodes   = decode(instruction, mask_opcodes, op_shift);
        address   = decode(instruction, mask_address, address_shift);
        Binvert   = decode(instruction, mask_Binvert, Binvert_shift);
        //printf("Address: "); hex32(address);
        
        
        //The following is placeholder code for how the CPU will perform
        //diffent operations. I am just taking a shortcut until I learn how to make it better
        if (cpu_codes==1){          //load value from address into A register
            A = read_ram(address);
            continue;
        }
        else if (cpu_codes==2){     //load inmediate value into A register. Treat address as the inmediate value
            A = address;    
            continue;
        }
        else if (cpu_codes==3){     //save value from register A into memory address
            write_ram(A,address);
            continue;
        }
        else if (cpu_codes==4){     //increment value in register A by 1
            A += 1;
            continue;
        }
        else if (cpu_codes==12){    //print value in register A to console
            printf("Syscall output: %d\n",A);
            continue;
        }
        else if (cpu_codes==13){    //change the program counter to address 
            PC = address;
            continue;
        }
        else if (cpu_codes==14){    //jump if conditional value is greater than 
            //I think this is cheating, but I am going to perform 2 operations 
            // in this clock cycle so that I can follow a conditional jump without
            // modifying the parser I have written
            continue;
        }
        else if (cpu_codes==15){    //This is the halt instruction
            printf("Program Halted execution at PC: %d\n",PC);
            return;
        }
        
        //Load data from memory at address
        DRR = read_ram(address);
        //show_ram(address,address);
        
        
        //Execute the instruction given and put result back into register A
        //Also set all the bits necessary, but that has more to do with the ALU
        printf("A_reg: "); hex32(A);
        printf("B_reg: "); hex32(DRR);
        A = ALU(A,DRR,opcodes,Binvert,&carryOut, &zr, &overflow);
        
        clock_counter++;
    }  //End of While loop
    
    //if we jumped to this point, it means that the program counter was trying 
    //to access a memory location that does not exist
    
    //return 0;
}