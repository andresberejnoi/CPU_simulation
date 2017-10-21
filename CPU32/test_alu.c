#include <stdio.h>
#include "alu.h"
#include "bases.h"

int main(){
    int A,B,carryOut,overflow_bit,opcode,ng,zr;
    int alu_out;
    
    printf("Enter values A and B to ALU: ");
    scanf("%d %d",&A,&B);
    
    printf("Enter opcode: ");
    scanf("%d",&opcode);
    
    printf("Negate flag: ");
    scanf("%d",&ng);
    
    //Use the ALU and check its answers
    alu_out = alu_temp(A,B,opcode,ng,&carryOut,&zr,&overflow_bit);
    
    //Print output from ALU:
    printf("%u + %u = %u\n", A,B,alu_out);
    printf("%#08x + %#08x = %#08x\n", A,B,alu_out);
    printf("ALU output: %d\n",alu_out);
    
    //Here, if we performed an arithmetic operation, we should check the
    //overflow, zero, and carryOut bits
    printf("|Co|Zr|Ov|\n");
    printf("|% 2d|% 2d|% 2d|\n",carryOut,zr,overflow_bit);
    
    
    /**************************************************************************/
    //Separate tests for overflow logic
    line_print();
    header_print("Overflow Testing");
    int a,b,result,over_test;
    a = 2147483647; //biggest number possible in 32-bit signed format
    b = 1;
    
    result = a+b;
    
    //overflow logic
    over_test = get_msb((~a & ~b)&result | (a & b & (~result)));
    
    bin32(a); bin32(b); printf("   ---------------------------------------\n"); bin32(result);
    printf("Overflow: %d\n",over_test);//; bin32(over_test);
    
    return 0;
}