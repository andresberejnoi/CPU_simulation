#include <stdio.h>

/*
 * The following table of conversion values was taken from Matt Jadud's code from a Computer Organization class at Berea College
 */
const char *bin_conv[16] = {
    [ 0] = "0000", [ 1]  = "0001", [ 2] = "0010", [ 3] = "0011",
    [ 4] = "0100", [ 5]  = "0101", [ 6] = "0110", [ 7] = "0111",
    [ 8] = "1000", [ 9]  = "1001", [10] = "1010", [11] = "1011",
    [12] = "1100", [13]  = "1101", [14] = "1110", [15] = "1111",
};

const char *hex_conv[16] = {
    [ 0] = "0", [ 1] = "1", [ 2] = "2", [ 3] = "3",
    [ 4] = "4", [ 5] = "5",  [6] = "6", [ 7] = "7",
    [ 8] = "8", [ 9] = "9", [10] = "A", [11] = "B",
    [12] = "C", [13] = "D", [14] = "E", [15] = "F",
};

/*
 * Print the hex representation of int 'a' in 32 bits.
 * A 32 bit number in hex needs 8 digits
 */
void hex32(uint16_t a){
    uint16_t dig1,dig2,dig3,dig4,dig5,dig6,dig7,dig8;
    
    dig1 = (a & 0x0000000f) >>  0;
    dig2 = (a & 0x000000f0) >>  4;
    dig3 = (a & 0x00000f00) >>  8;
    dig4 = (a & 0x0000f000) >> 12;
    dig5 = (a & 0x000f0000) >> 16;
    dig6 = (a & 0x00f00000) >> 20;
    dig7 = (a & 0x0f000000) >> 24;
    dig8 = (a & 0xf0000000) >> 28;
    
    printf("0x%s%s%s%s%s%s%s%s\n",hex_conv[dig8],hex_conv[dig7],hex_conv[dig6],hex_conv[dig5],hex_conv[dig4],hex_conv[dig3],hex_conv[dig2],hex_conv[dig1]);
    
}

void hex16(uint16_t a){
    uint16_t dig1, dig2, dig3, dig4;
    
    dig1 = (a & 0x000f) >>  0;
    dig2 = (a & 0x00f0) >>  4;
    dig3 = (a & 0x0f00) >>  8;
    dig4 = (a & 0xf000) >> 12;
    
    printf("0x%s%s%s%s\n",hex_conv[dig4],hex_conv[dig3],hex_conv[dig2],hex_conv[dig1]);
}

void bin32(uint16_t a){
    uint16_t dig1,dig2,dig3,dig4,dig5,dig6,dig7,dig8;
    
    dig1 = (a & 0x0000000f) >>  0;
    dig2 = (a & 0x000000f0) >>  4;
    dig3 = (a & 0x00000f00) >>  8;
    dig4 = (a & 0x0000f000) >> 12;
    dig5 = (a & 0x000f0000) >> 16;
    dig6 = (a & 0x00f00000) >> 20;
    dig7 = (a & 0x0f000000) >> 24;
    dig8 = (a & 0xf0000000) >> 28;
    
    printf("0b %s %s %s %s %s %s %s %s\n",bin_conv[dig8],bin_conv[dig7],bin_conv[dig6],bin_conv[dig5],bin_conv[dig4],bin_conv[dig3],bin_conv[dig2],bin_conv[dig1]);

}

void bin16(uint16_t a){
    uint16_t dig1, dig2, dig3, dig4;
    
    dig1 = (a & 0x000f) >>  0;
    dig2 = (a & 0x00f0) >>  4;
    dig3 = (a & 0x0f00) >>  8;
    dig4 = (a & 0xf000) >> 12;
    
    printf("0x%s %s %s %s\n",bin_conv[dig4],bin_conv[dig3],bin_conv[dig2],bin_conv[dig1]);

}


void bin8(uint16_t a){
    uint16_t dig1, dig2;
    
    dig1 = (a & 0x000f) >> 0;
    dig2 = (a & 0x00f0) >> 4;
    
    printf("0x%s %s\n",bin_conv[dig2],bin_conv[dig1]);

}

void bin4(uint16_t a){
    uint16_t dig1;
    
    dig1 = (a & 0x000f) >> 0;

    printf("0b %s\n",bin_conv[dig1]);

}