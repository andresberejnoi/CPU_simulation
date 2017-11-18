#include <stdio.h>
#include "gates.h"
#include "bases.h"
#include "components.h"
#include "alu.h"
#include "bit_tools.h"

uint16_t ALU(uint16_t A_reg, uint16_t B_reg, uint16_t opcode, uint16_t Binvert, uint16_t *carryOut, uint16_t *zr, uint16_t *overflow_bit){
    uint16_t output, sum_result, ng_full, xor_b,set_less_than;
    uint16_t ANDed,ORed;
    ng_full = fill_register(Binvert);          // I will need 32 bit ng wires for the XOR gates, so I create a register full of ones
    xor_b = XOR(B_reg,ng_full);           //Passing B through conditional inverter gate
    
    /***************************************************************************/
    //Arithmetic Unit:
    sum_result = fullAdder32(A_reg, xor_b, Binvert, carryOut);
    set_less_than = get_msb(sum_result);
    
    //Determine overflow
    //overflow_bit = (~A[31] * ~B[31])*result[31] + (A[31]*B[31]* (~result[31]))
    *overflow_bit = get_msb((~A_reg & ~xor_b)&sum_result | (A_reg & xor_b & (~sum_result)));

    
    /***************************************************************************/
    //Logical Unit 
    ANDed = A_reg & xor_b;
    ORed = A_reg | xor_b;
    
    
    /***************************************************************************
     *Set the output wires by using a MUX gate.
     * The opcodes are the following for now:
     * 00 -> AND(A,B)
     * 01 -> OR(A,B)
     * 10 -> A + B      (The Binvert bit will determine if this is subtraction)
     * 11 -> A < B      (only makes sense when Binvert is set to 1)
     * 
     */
    output = MUX4way(ANDed,ORed,sum_result,set_less_than, opcode);
    
    //Set the zero value to true if all the bits in result are zero
    //I am doing it in a very inefficient way for now. I will try to improve it later.
    //To test that all the bits in the output are zero, I need 31 AND gates and 31 inverters 
    // at the end:
    
    /*
    uint16_t i,cur_bit,next_bit,neg_AND_result;
    
    cur_bit = get_bit(output, 0);
    next_bit = get_bit(output, 1);
    neg_AND_result = NOR(cur_bit,next_bit);
    
    for (i=2;i<31;i+=2){
        cur_bit = get_bit(output,i);
        next_bit = get_bit(output, i+1);
        
        neg_AND_result = NOR(neg_AND_result, NOR(cur_bit,next_bit));
    }
    *zr = get_bit(neg_AND_result,0);
    */
    //I will take a shortcut for the zero output here:
    if (output==0){
        *zr = 1;
    }
    else{
        *zr = 0;  
    }
    
    return output;
}

uint16_t ALU_old(uint16_t A_reg, uint16_t B_reg, uint16_t control_bits){
    
    //uint16_t A_reg, B_reg, result;       //declaring two registers that the ALU can use
    
    //Here load corresponding values uint16_to the registers
    
    //ALU operations are calculated next and then passed uint16_to a 16-way mux gate
    //logical operations
    uint16_t ALU_AND = AND(A_reg,B_reg);             //selected by 0000
    uint16_t ALU_OR = OR(A_reg, B_reg);
    uint16_t ALU_NOT = NOT(A_reg);
    uint16_t ALU_XOR = XOR(A_reg, B_reg);
    uint16_t ALU_ZERO = 0;
    uint16_t ALU_EQUAL_THAN = 0;
    uint16_t ALU_LESS_THAN = 0;
    uint16_t ALU_GREATER_THAN = 0;
    
    //Arithmetic operations
    uint16_t ALU_ADD = A_reg + B_reg;
    uint16_t ALU_SUB = 0;
    uint16_t UND = 0;
    uint16_t UND2 = 0;
    uint16_t UND3 = 0;
    uint16_t UND4 = 0;
    uint16_t UND5 = 0;
    uint16_t UND6 = 0;
    
    uint16_t result = MUX16way(ALU_ADD,ALU_OR,ALU_NOT,ALU_XOR,ALU_ZERO,ALU_EQUAL_THAN,ALU_LESS_THAN,ALU_GREATER_THAN,ALU_ADD,ALU_SUB,UND,UND2,UND3,UND4,UND5,UND6,control_bits);
    
    return result;
}