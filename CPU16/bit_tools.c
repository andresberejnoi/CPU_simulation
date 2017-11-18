
uint16_t set_bit_on(uint16_t reg, uint16_t pos){
    uint16_t mask, output;
    
    mask = 1 << pos;
    output = reg | mask;
    
    return output;
}


uint16_t set_bit_off(uint16_t reg, uint16_t pos){
    uint16_t mask, output;
    
    mask = ~(1 << pos);
    output = reg & mask;
    
    return output;
}

uint16_t get_bit(uint16_t reg, uint16_t pos){
    uint16_t mask, output;
    
    mask = 1;
    output = (reg >> pos) & mask;
    
    return output;
}

uint16_t flip_one_bit(uint16_t reg, uint16_t pos){
    uint16_t mask, bit, output;
    
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

int16_t twos_complement(uint16_t A){
    uint16_t output;
    
    output = ~(A) + 1;
    
    return output;
}

/*
 *Returns a register filled with bits equal to bit val.
 *For example, if val == 1, then the function will return
 * a 32-bit int where all the bits are turned on
 */
 
uint16_t fill_register (uint16_t val){
    uint16_t output, val_bit;
    
    val_bit = get_bit(val,0);       //just to make sure that the argument passed is treated as a single bit
    output = twos_complement(val_bit);
    
    return output;
}


//returns most significant bit
uint16_t get_msb(uint16_t reg){
    uint16_t output;
    
    output = get_bit(reg,31);
    return output;
}

uint16_t get_lsb(uint16_t reg){
    uint16_t output;
    
    output = get_bit(reg,0);
    return output;
}