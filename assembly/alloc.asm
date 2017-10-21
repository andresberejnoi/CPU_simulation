#allocate ram for a specified length. This will be very primitive as I have not
#yet decided how functions will be defined. This will be more about me practicing, 
# a proof of concept.


#How should the program decide the amount of memory to allocate?
#I think I will use one of the 32 general registers. In that case,
# I have to define a constant register for parameters.

#I decided to set registers 4,5,6,and 7 for parameters RAM[4 or 5 or 6 or 7]
#how do I define a null terminator? maybe as 0xfc000000 (i.e. 0b1111 1100 0000 0000 ....)

#load constants (no addi instruction yet)
laodi 1
save @1

loadi 0
save @0

#First read value register to determine how much memory to allocate
load @4             #read number of spaces to allocate
save @50            #copy the number to another location to work with it.

#it should start at some address and find a stretch of memory that is empty
#I will set it to a fixed value for now Lets say that it starts allocating space at RAM[100]
loadi 100           #starting address
save @51            #save the starting address in location RAM[51]


#initialize a pointer to beginning of buffer. By default it will start with the 
#location saved above:
load @51            #load beginning of ram
save @10            #save it at location RAM[10]. This is the pointer we will be modifying

#Initialize a moving pointer that we will use to write to memory
load @10
save @11            #save the moving pointer at RAM[11]


MAIN:
    #the program will return the address to the beginning of the empty space and
    #it will also place a null terminator at the end of the array
    
    #-------------------------------------------------------------
    #- Variables to use:
    #       @4  -> amount of RAM registers to allocate
    #       @10 -> pointer to beginning of buffer
    #       @11 -> working pointer to move along the buffer
    #-------------------------------------------------------------
    
    load @11            #load pointer to current location
    jump IS_EMPTY       #jump to sub-routine to check if it is empty
    
    
IS_EMPTY:
    #In this section we check if the memory location we currently want is not
    #currently in use. Also, we check if it is not a NULL or terminating character
    
    