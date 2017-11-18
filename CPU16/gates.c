#include "gates.h"
//#include <stdio.h>    //for debugging
#include "bit_tools.h"


uint16_t AND(uint16_t a, uint16_t b){
    uint16_t output = a & b;     //*bitwise  AND on a and b uint16_tegers
    return output; 
} 

uint16_t OR(uint16_t a, uint16_t b){
    uint16_t output = a | b;
    return output;
}

uint16_t NOT(uint16_t a){
    uint16_t output = ~a;
    return output;
}

uint16_t NAND(uint16_t a, uint16_t b){
    uint16_t output = AND(a,b);
    output = NOT(output);
    
    return output;
}

uint16_t NOR(uint16_t a, uint16_t b){
    uint16_t output;
    
    output = ~(a|b);
    return output;
}
uint16_t XOR(uint16_t a, uint16_t b){
    uint16_t output = a^b;
    return output;
}


uint16_t MUX2way(uint16_t A, uint16_t B, uint16_t bit_select){
    uint16_t output;
    bit_select = fill_register(bit_select);         //make all the bits in the register equal
    //pruint16_tf("Register B: ");
    //bin32(B);
    output = (A & ~bit_select) | (B & bit_select);    //error when flipping bits (sign extension on the selector bit should fix it, I think)
    //output = OR( AND(A,NOT(bit_select)), AND(B,bit_select));  //using homemade gates
    
    /*
    //Using if statements, but I want to make it work with logic gates
    if (bit_select == 0){
        output = A;
    }
    else{
        output = B;
    }
    */
    
    /*
    //DEBUGGING
    uint16_t partA,partB;
    uint16_t inverted_select = ~twos_complement(bit_select);
    partA = (A & inverted_select);
    pruint16_tf("AND for first input A:\n");
    bin32(A); bin32(inverted_select); line_pruint16_t();bin32(partA);
    pruint16_tf("\n");
    partB = (B & bit_select);
    pruint16_tf("AND for Second input B:\n");
    bin32(B); bin32(bit_select); line_pruint16_t();bin32(partB);
    pruint16_tf("\n");
    output = partA | partB;
    pruint16_tf("OR between inputs:\n");
    bin32(partA); bin32(partB); line_pruint16_t(); bin32(output);
    */
    
    
    //pruint16_tf("Output reg: ");
    //bin32(output);
    return output;
} 

uint16_t MUX4way(uint16_t A, uint16_t B, uint16_t C, uint16_t D, uint16_t select){
    uint16_t output;
    uint16_t Atemp,Btemp,sel;
    
    //First MUX layer
    sel = get_bit(select,0);
    Atemp = MUX2way(A,B,sel);
    Btemp = MUX2way(C,D,sel);
    
    //Second MUX layer
    sel = get_bit(select,1);
    output = MUX2way(Atemp, Btemp, sel);
    
    
    return output;
}

uint16_t MUX8way(uint16_t A,uint16_t B,uint16_t C,uint16_t D,uint16_t E,uint16_t F,uint16_t G,uint16_t H, uint16_t select){
    //control: for now, it contains 8 inputs and 4 selection bits
    uint16_t output,sel;
    uint16_t Atemp,Btemp,Ctemp,Dtemp;    //re-usable temporary registers
    
    
    //First layer of 2-way multiplexers
    sel = get_bit(select,0);
    Atemp = MUX2way(A,B,sel);
    Btemp = MUX2way(C,D,sel);
    Ctemp = MUX2way(E,F,sel);
    Dtemp = MUX2way(G,H,sel);
    
    //Second layer of Multiplexers
    sel = get_bit(select,1);
    Atemp = MUX2way(Atemp,Btemp,sel);
    Btemp = MUX2way(Ctemp,Dtemp,sel);
    
    //Third layer
    sel = get_bit(select,2);
    output = MUX2way(Atemp,Btemp,sel);

    return output;
}

uint16_t MUX16way(uint16_t A,uint16_t B,uint16_t C,uint16_t D,uint16_t E,uint16_t F,uint16_t G,uint16_t H,uint16_t L,uint16_t M,uint16_t N,uint16_t O,uint16_t P,uint16_t Q,uint16_t R,uint16_t S, uint16_t select){
    uint16_t output,final_select;
    uint16_t Atemp, Btemp;
    
    //pruint16_tf("Bit select: "); bin4(select);
    Atemp = MUX8way(A,B,C,D,E,F,G,H,select);
    Btemp = MUX8way(L,M,N,O,P,Q,R,S,select);
    
    final_select = get_bit(select,3);
    output = MUX2way(Atemp,Btemp,final_select);
    
    return output;
}


uint16_t DeMUX2way(uint16_t A, uint16_t select_bit){
    
    return 0;
}