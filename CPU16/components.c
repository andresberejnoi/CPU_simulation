#include "gates.h"
#include "bit_tools.h"
#include "components.h"

//For Debugging
#include <stdio.h>
#include "bases.h"
#include "pruint16_t_tools.h"

void halfAdder(uint16_t a, uint16_t b, uint16_t *sum_bit, uint16_t *carryOut){
    uint16_t output;
    //uint16_t sum_bit,carryOut;
    
    //sum_bit = XOR(a,b);
    //carryOut = AND(a,b);
    
    //output = (carryOut << 1) | sum_bit;
    *sum_bit = XOR(a,b);
    *carryOut = AND(a,b);
    
    //return output;
}

void fullAdder(uint16_t a, uint16_t b, uint16_t carryIn,uint16_t *output, uint16_t *finalCarry){
    //a and b are single bits
    uint16_t sum_carry;
    uint16_t carryOut1, carryOut2, sum_bit;
    
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

uint16_t fullAdder32(uint16_t reg_a,uint16_t reg_b, uint16_t carryIn, uint16_t *carryOut){
    uint16_t output, temp_out;
    uint16_t bit_a, bit_b, sum_bit, i;
    output = 0;
    
    //header_pruint16_t("Initial State");
    //pruint16_tf("carryIn: %d\ncarryOut: %d\n",carryIn, *carryOut);
    
    //pruint16_tf("DEBUGGING FULL 32-BIT ADDER:\n");
    //pruint16_tf("| A | B | Ci|| Co| S |\n");
    //pruint16_tf("---------------------\n");
    
    
    for (i=0;i<16;i++){
        bit_a = get_bit(reg_a,i);
        bit_b = get_bit(reg_b,i);
        
        fullAdder(bit_a,bit_b,carryIn,&temp_out,carryOut);
        output = output | (temp_out << i);

        //pruint16_tf("Adding %d + %d; bit %d: ",bit_a,bit_b,i); bin32(output);
        //pruint16_tf("| %d | %d | %d || %d | %d |\n",bit_a,bit_b,carryIn,*carryOut,temp_out);
        carryIn = *carryOut;
    }
    
    /*
    if (*carryOut == 1){
        pruint16_tf("WARNING: OVERFLOW OCCURED!\n");
    }
    */
    return output;
}