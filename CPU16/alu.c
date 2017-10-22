#include <stdio.h>
#include "gates.h"
#include "bases.h"
#include "components.h"
#include "alu.h"
#include "bit_tools.h"

int ALU(int A_reg, int B_reg, int opcode, int Binvert, int *carryOut, int *zr, int *overflow_bit){
    int output, sum_result, ng_full, xor_b,set_less_than;
    int ANDed,ORed;
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
    int i,cur_bit,next_bit,neg_AND_result;
    
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

int ALU_old(int A_reg, int B_reg, int control_bits){
    
    //int A_reg, B_reg, result;       //declaring two registers that the ALU can use
    
    //Here load corresponding values into the registers
    
    //ALU operations are calculated next and then passed into a 16-way mux gate
    //logical operations
    int ALU_AND = AND(A_reg,B_reg);             //selected by 0000
    int ALU_OR = OR(A_reg, B_reg);
    int ALU_NOT = NOT(A_reg);
    int ALU_XOR = XOR(A_reg, B_reg);
    int ALU_ZERO = 0;
    int ALU_EQUAL_THAN = 0;
    int ALU_LESS_THAN = 0;
    int ALU_GREATER_THAN = 0;
    
    //Arithmetic operations
    int ALU_ADD = A_reg + B_reg;
    int ALU_SUB = 0;
    int UND = 0;
    int UND2 = 0;
    int UND3 = 0;
    int UND4 = 0;
    int UND5 = 0;
    int UND6 = 0;
    
    int result = MUX16way(ALU_ADD,ALU_OR,ALU_NOT,ALU_XOR,ALU_ZERO,ALU_EQUAL_THAN,ALU_LESS_THAN,ALU_GREATER_THAN,ALU_ADD,ALU_SUB,UND,UND2,UND3,UND4,UND5,UND6,control_bits);
    
    return result;
}