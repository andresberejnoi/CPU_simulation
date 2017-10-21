#include "gates.h"
//#include <stdio.h>    //for debugging
#include "bit_tools.h"


int AND(int a, int b){
    int output = a & b;     //*bitwise  AND on a and b integers
    return output; 
} 

int OR(int a, int b){
    int output = a | b;
    return output;
}

int NOT(int a){
    int output = ~a;
    return output;
}

int NAND(int a, int b){
    int output = AND(a,b);
    output = NOT(output);
    
    return output;
}

int NOR(int a, int b){
    int output;
    
    output = ~(a|b);
    return output;
}
int XOR(int a, int b){
    int output = a^b;
    return output;
}


int MUX2way(int A, int B, int bit_select){
    int output;
    bit_select = fill_register(bit_select);         //make all the bits in the register equal
    //printf("Register B: ");
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
    int partA,partB;
    int inverted_select = ~twos_complement(bit_select);
    partA = (A & inverted_select);
    printf("AND for first input A:\n");
    bin32(A); bin32(inverted_select); line_print();bin32(partA);
    printf("\n");
    partB = (B & bit_select);
    printf("AND for Second input B:\n");
    bin32(B); bin32(bit_select); line_print();bin32(partB);
    printf("\n");
    output = partA | partB;
    printf("OR between inputs:\n");
    bin32(partA); bin32(partB); line_print(); bin32(output);
    */
    
    
    //printf("Output reg: ");
    //bin32(output);
    return output;
} 

int MUX4way(int A, int B, int C, int D, int select){
    int output;
    int Atemp,Btemp,sel;
    
    //First MUX layer
    sel = get_bit(select,0);
    Atemp = MUX2way(A,B,sel);
    Btemp = MUX2way(C,D,sel);
    
    //Second MUX layer
    sel = get_bit(select,1);
    output = MUX2way(Atemp, Btemp, sel);
    
    
    return output;
}

int MUX8way(int A,int B,int C,int D,int E,int F,int G,int H, int select){
    //control: for now, it contains 8 inputs and 4 selection bits
    int output,sel;
    int Atemp,Btemp,Ctemp,Dtemp;    //re-usable temporary registers
    
    
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

int MUX16way(int A,int B,int C,int D,int E,int F,int G,int H,int L,int M,int N,int O,int P,int Q,int R,int S, int select){
    int output,final_select;
    int Atemp, Btemp;
    
    //printf("Bit select: "); bin4(select);
    Atemp = MUX8way(A,B,C,D,E,F,G,H,select);
    Btemp = MUX8way(L,M,N,O,P,Q,R,S,select);
    
    final_select = get_bit(select,3);
    output = MUX2way(Atemp,Btemp,final_select);
    
    return output;
}


int DeMUX2way(int A, int select_bit){
    
    return 0;
}