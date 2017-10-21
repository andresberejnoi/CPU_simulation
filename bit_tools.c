
unsigned int set_bit_on(int reg, int pos){
    int mask, output;
    
    mask = 1 << pos;
    output = reg | mask;
    
    return output;
}


unsigned int set_bit_off(int reg, int pos){
    unsigned int mask, output;
    
    mask = ~(1 << pos);
    output = reg & mask;
    
    return output;
}

unsigned int get_bit(int reg, int pos){
    unsigned int mask, output;
    
    mask = 1;
    output = (reg >> pos) & mask;
    
    return output;
}

unsigned int flip_one_bit(int reg, int pos){
    int mask, bit, output;
    
    bit = get_bit(reg,pos);
    if (bit == 0){
        //Set bit to one
        output = set_bit_on(reg,pos);
    }
    else{
        //set bit to 0
        output = set_bit_off(reg,pos);
    }
    return output;
}

int twos_complement(int A){
    int output;
    
    output = ~(A) + 1;
    
    return output;
}

/*
 *Returns a register filled with bits equal to bit val.
 *For example, if val == 1, then the function will return
 * a 32-bit int where all the bits are turned on
 */
 
unsigned int fill_register (int val){
    int output, val_bit;
    
    val_bit = get_bit(val,0);       //just to make sure that the argument passed is treated as a single bit
    output = twos_complement(val_bit);
    
    return output;
}


//returns most significant bit
unsigned int get_msb(int reg){
    unsigned int output;
    
    output = get_bit(reg,31);
    return output;
}

unsigned int get_lsb(int reg){
    unsigned int output;
    
    output = get_bit(reg,0);
    return output;
}