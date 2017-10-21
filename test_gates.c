#include <stdio.h>
#include "gates.h"
#include "bases.h"
#include "bit_tools.h"
#include "components.h"
#include "print_tools.h"


int main(){
    int a,b,res, carrybit;
    a = 255;
    b = 0x00000001;
    
    res = OR(a,b);
    printf("ORing the following:\n");
    hex32(a);
    hex32(b);
    printf("--------\n");
    hex32(res);
    printf("int val: %d\n",res);
    
    
    res = NOT(a);
    printf("NOT the following:\n");
    hex32(a);
    printf("--------\n");
    hex32(res);
    printf("int val: %d\n",res);
    
    
    res = OR(a,b);
    printf("ORing the following:\n");
    bin32(a);
    bin32(b);
    printf("------------------------------------------\n");
    bin32(res);
    printf("int val: %d\n",res);
    
    
    res = NOT(a);
    printf("NOT the following:\n");
    bin32(a);
    printf("------------------------------------------\n");
    bin32(res);
    printf("int val: %d\n",res);
    
    printf("------------------------------------------\n");
    printf("Testing Bit tools\n");
    a = 8;
    printf("a=%d\n",a);
    a = set_bit_on(a,31);
    bin32(a);
    
    printf("Flipping bits:\n");
    a = 0xffffffff;
    res = flip_one_bit(a,31);
    printf("a before: %d\n",a);
    //bin32(a);
    printf("a after: %d\n",res);
    //bin32(res);
    
    //Half adder test
    header_print("Test Half Adder");
    a = 0; b = 0;
    bin32(a); bin32(b);
    line_print();
    res = halfAdder(a,b);
    bin32(res);
    
    //Half adder test
    header_print("Test Half Adder");
    a = 1; b = 0;
    bin32(a); bin32(b);
    line_print();
    res = halfAdder(a,b);
    bin32(res);
    
    //Half adder test
    header_print("Test Half Adder");
    a = 0; b = 1;
    bin32(a); bin32(b);
    line_print();
    res = halfAdder(a,b);
    bin32(res);
    
    //Half adder test
    header_print("Test Half Adder");
    a = 1; b = 1;
    bin32(a); bin32(b);
    line_print();
    res = halfAdder(a,b);
    bin32(res);
    
    //========FULL ADDER=======================
    //Full Adder
    header_print("Test Full Adder");
    a = 0; b = 0; carrybit=0;
    bin32(a); bin32(b);
    line_print();
    res = fullAdder(a,b,carrybit);
    bin32(res);
    
    header_print("Test Full Adder");
    a = 1; b = 0, carrybit=1;
    bin32(a); bin32(b);
    line_print();
    res = fullAdder(a,b,carrybit);
    bin32(res);
    
    header_print("Test Full Adder");
    a = 0; b = 1, carrybit=0;
    bin32(a); bin32(b);
    line_print();
    res = fullAdder(a,b,carrybit);
    bin32(res);
    
    header_print("Test Full Adder");
    a = 3; b = 1, carrybit=0;
    bin32(a); bin32(b);
    line_print();
    res = fullAdder(a,b,carrybit);
    bin32(res);
    
    header_print("Test Full Adder");
    a = 3; b = 1, carrybit=1;
    bin32(a); bin32(b);
    line_print();
    res = fullAdder(a,b,carrybit);
    bin32(res);
    
    
    //=======================FULL ADDER 32-bit================================================
    //Full Adder
    header_print("Test Full Adder 32-BITS");
    a = 15; b = 1;
    bin32(a); bin32(b);
    line_print();
    res = fullAdder32(a,b);
    bin32(res);
    
    header_print("Test Full Adder 32-BITS");
    a = 5; b = 3;
    bin32(a); bin32(b);
    line_print();
    res = fullAdder32(a,b);
    bin32(res);
    
    header_print("Test Full Adder 32-BITS");
    a = 17; b = 2;
    bin32(a); bin32(b);
    line_print();
    res = fullAdder32(a,b);
    bin32(res);
    
    header_print("Test Full Adder 32-BITS");
    a = 8; b = 0;
    bin32(a); bin32(b);
    line_print();
    res = fullAdder32(a,b);
    bin32(res);
    
    header_print("Test Full Adder 32-BITS");
    a = -3; b = 3;
    bin32(a); bin32(b);
    line_print();
    res = fullAdder32(a,b);
    bin32(res);
    
    header_print("Shift Testing");
    printf("1 << 0 = %d: ", 1<<0); bin32(1 << 0);
    printf("1 << 1 = %d: ", 1<<1); bin32(1 << 1);
    printf("1 << 2 = %d: ", 1<<2); bin32(1 << 2);
    printf("1 << 3 = %d: ", 1<<3); bin32(1 << 3);
    
    return 0;
}
