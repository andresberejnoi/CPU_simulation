uint16_t AND(uint16_t, uint16_t);

uint16_t OR(uint16_t, uint16_t);

uint16_t XOR(uint16_t, uint16_t);

uint16_t NOT(uint16_t);

uint16_t NAND(uint16_t, uint16_t);

uint16_t NOR(uint16_t, uint16_t);

uint16_t MUX2way(uint16_t, uint16_t, uint16_t); //multiplexer for two 32-bit inputs and 1-bit select line
uint16_t MUX4way(uint16_t, uint16_t, uint16_t, uint16_t, uint16_t);
uint16_t MUX8way(uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t);
uint16_t MUX16way(uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t);

uint16_t DeMUX2way(uint16_t, uint16_t); //demultiplexer

uint16_t left_bitshifter(uint16_t,uint16_t);
uint16_t right_bitshifter(uint16_t, uint16_t);