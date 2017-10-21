#This program implements a simple loop. It assumes that there is a halt instruction 
#at memory location 99 (RAM[99]) but there are probably better ways to set this up (yeah, I just
# added a halt instruction).
#I am also making the assumption that the first 100 memory locations are for instructions (0-99)
# data starts at memory location 100

#Setting the number of times we want the program to loop
loadi 10    #load inmediate value 10 into register A. This is the control loop constant
save @21    #save value of 10 into memory location 21: RAM[21]

loadi 1     #load 1 into A
save @1     #save into RAM[1] to use as constant

loadi 0
save @20    #variable i in a for loop starts with 0 

LOOP:          #stores the address memory that points to the next line of code
    load @20     #reads memory address 0 and loads value into register A
    Add @20      #gets value in memory address 101 in RAM and adds it to whatever is in register A
    save @2     #saves contents of register A into memory address 100
    
    #Next, we are basically defining a loop control variable as in (for(i=0;...))
    load @20     #load RAM[110] into A
    incr          #increment the value in register A by 1 and store back in A
    save @20     #save value in A in RAM[110]
    
    #Set conditonal to break the loop
    jgt @20 @21 END_LOOP    #set PC to address 99 if value in register A is greater than value at memory location 111                
    
    jump LOOP  #sets the Program Counter (PC) to memory address that START points to (or refers to)

END_LOOP:
    halt
