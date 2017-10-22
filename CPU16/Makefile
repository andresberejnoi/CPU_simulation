# http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
CC=gcc
CFLAGS=-std=gnu99 -I. 
DEPENDENCIES=ram.h gates.h bit_tools.h print_tools.h bases.h cpu.h alu.h components.h
OBJS=ram.o gates.o bit_tools.o print_tools.o bases.o cpu.o components.o alu.o computer.o
OBJSTEST=ram.o gates.o bit_tools.o print_tools.o bases.o cpu.o components.o alu.o

%.o: %.c $(DEPENDENCIES)
	$(CC) -c -o $@ $< $(CFLAGS)

computer: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o computer
	@echo "computer compiled correctly"
	#@echo "Removing *.o files created during compilation..."
	#@make clean
	#@echo "Files removed"

test_adders: $(OBJSTEST) test_adders.c
	$(CC) $(CFLAGS) test_adders.c $(OBJSTEST) -o test_adders

clean:
	\rm *.o

#all: computer
#	echo "Done"