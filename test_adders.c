#include "bases.h"
#include "components.h"
#include "print_tools.h"
#include <stdio.h>


int main(){
    unsigned int A,B,res,target,overflow_bit; //registers
    int * carryOut;
    printf("Enter values for register A and B: ");
    scanf("%d %d",&A,&B);
    //A = 0x7fffffff; B = 1;
    target = A + B;
    
    overflow_bit = 0;
    int carryIn=0;
    carryOut = &overflow_bit;
    
    header_print("Testing FULL ADDER 32-BITS");
    res = fullAdder32(A,B,carryIn,carryOut);
    if (res == target){
        printf("SUCCESS!!\n");
        printf("Overflow bit: %d\n",overflow_bit);
        printf("%u + %u = %u; should be: %u\n", A,B,res,target);
        printf("%#08x + %#08x = %#08x; should be: %#08x\n", A,B,res,target);
        bin32(A); bin32(B); line_print(); bin32(res);
    }
    else{
        printf("FAILED\n");
        printf("CarryOut: %d\n",*carryOut);
        printf("%u + %u = %u; should be: %u\n", A,B,res,target);
        //printf("%x + %x = %x; should be: %x\n", A,B,res,target);
        printf("%#08x + %#08x = %#08x; should be: %#08x\n", A,B,res,target);
        bin32(res); printf("                  %s\n","=/="); bin32(target);
    }
    
    return 0;
}