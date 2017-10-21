#include <stdio.h>
#include "gates.h"
#include "print_tools.h"



int main(){
    int A,B,selec,i;
    int output;
    
    A = 31; B = 20;
    bin32(A);bin32(B);
    header_print("TESTING 2-way Multiplexer");
    for (i=0; i<2; i++){      //calling the multiplexer with several values]
        printf("---------------------------\nSelect bit: %d\n",i);
        output = MUX2way(A,B,i);
        printf("OUT=%d ; ",output); bin32(output);
    }
    
    //Testing more complex multiplexers
    header_print("Testing 16-way Multiplexer");
    for (i=0;i<16;i++){
        printf("---------------------------\nSelect command: %d\n",i);
        output = MUX16way(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,i);
        printf("OUT=%d\n ; ",output); bin32(output);
    }
    
    /*
    header_print("TEST GET_BIT");
    A = 7; B = get_bit(A,2);
    printf("Getting bit at index %d from A:",1);
    printf("A: "); bin32(A);
    printf("Bit val: %d\n",B);
    */
    
    return 0;
}