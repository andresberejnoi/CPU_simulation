int AND(int, int);

int OR(int, int);

int XOR(int, int);

int NOT(int);

int NAND(int, int);

int NOR(int, int);

int MUX2way(int, int, int); //multiplexer for two 32-bit inputs and 1-bit select line
int MUX4way(int, int, int, int, int);
int MUX8way(int, int, int, int, int, int, int, int, int);
int MUX16way(int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int);

int DeMUX2way(int, int); //demultiplexer

int left_bitshifter(int,int);
int right_bitshifter(int, int);