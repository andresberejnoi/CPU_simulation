#include "gates.h"
#include "bit_tools.h"
#include "components.h"

//For Debugging
#include <stdio.h>
#include "bases.h"
#include "print_tools.h"

void halfAdder(int a, int b, int *sum_bit, int *carryOut){
    int output;
    //int sum_bit,carryOut;
    
    //sum_bit = XOR(a,b);
    //carryOut = AND(a,b);
    
    //output = (carryOut << 1) | sum_bit;
    *sum_bit = XOR(a,b);
    *carryOut = AND(a,b);
    
    //return output;
}

void fullAdder(int a, int b, int carryIn,int *output, int *finalCarry){
    //a and b are single bits
    int sum_carry;
    int carryOut1, carryOut2, sum_bit;
    
    halfAdder(a,b, &sum_bit, &carryOut1);             //sum_carry has both carry and sum bits. Most significant bit is carry and least sig. bit is sum
    //sum_bit = get_bit(sum_bit,0);
    //carryOut1 = get_bit(sum_carry,1);
    
    halfAdder(carryIn, sum_bit, output, &carryOut2);
    //sum_bit = get_bit(sum_carry,0);
    //carryOut2 = get_bit(sum_carry,1);
    
    *finalCarry = OR(carryOut1,carryOut2);
    //*output = (finalCarry << 1) | *output;
    
    //return output;
}

int fullAdder32(int reg_a,int reg_b, int carryIn, int *carryOut){
    int output, temp_out;
    int bit_a, bit_b, sum_bit, i;
    output = 0;
    
    //header_print("Initial State");
    //printf("carryIn: %d\ncarryOut: %d\n",carryIn, *carryOut);
    
    //printf("DEBUGGING FULL 32-BIT ADDER:\n");
    //printf("| A | B | Ci|| Co| S |\n");
    //printf("---------------------\n");
    
    
    for (i=0;i<32;i++){
        bit_a = get_bit(reg_a,i);
        bit_b = get_bit(reg_b,i);
        
        fullAdder(bit_a,bit_b,carryIn,&temp_out,carryOut);
        output = output | (temp_out << i);

        //printf("Adding %d + %d; bit %d: ",bit_a,bit_b,i); bin32(output);
        //printf("| %d | %d | %d || %d | %d |\n",bit_a,bit_b,carryIn,*carryOut,temp_out);
        carryIn = *carryOut;
    }
    
    /*
    if (*carryOut == 1){
        printf("WARNING: OVERFLOW OCCURED!\n");
    }
    */
    return output;
}

unsigned int barrel_shifter32(unsigned int reg_a, unsigned int shift_ammount, int direction){
    unsigned int output;
    
    unsigned int A_temp, B_temp, C_temp, D_temp;
    
    //first layer of multiplexers
    
    
    
    return output;
}