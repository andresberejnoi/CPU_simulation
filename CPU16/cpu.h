#include "stdint.h"

//Define space for general purpose registers:
#define NUM_REGISTERS 8


uint16_t fetch_instruction(uint16_t *);

uint16_t get_controlBits(uint16_t);

uint16_t get_jumpBits(uint16_t);

void CPU();

