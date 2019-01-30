#   Custom CPU Simulation

This project simulates a processor (16 and 32 bit) and it is a work in progress. The main goal of the project is to learn more
about computer architecture. There are some sample assembly language programs as well as their assembled versions.

## Generate CPU executable
Run make inside the CPU32 directory to generate the executable 'computer'

## How to Assemble Code

To turn assembly into machine language, use the script asm_parser_vxxx.py (The x's represent versions):

```sh 
python asm_parser_v0.4.py <source code> <output file>
```

## How to run the CPU:

To run the simulation, simply do:

```sh
./computer <input assembled program>
```

