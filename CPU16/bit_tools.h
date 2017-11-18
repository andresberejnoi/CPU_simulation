#include "stdint.h"
//setter functions
uint16_t set_bit_on(uint16_t, uint16_t);
uint16_t set_bit_off(uint16_t, uint16_t);
uint16_t flip_one_bit(uint16_t, uint16_t);

//getter functions
uint16_t get_bit(uint16_t, uint16_t);
uint16_t get_msb(uint16_t);  //output most significant bit from register
uint16_t get_lsb(uint16_t);  //output least significant bit from register

//Others
int16_t twos_complement(uint16_t);
uint16_t fill_register (uint16_t);

