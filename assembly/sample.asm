#This program implements a simple loop. It assumes that there is a halt instruction 
#at memory location 99 (RAM[99]) but there are probably better ways to set this up.
#I am also making the assumption that the first 100 memory locations are for instructions (0-99)
# data starts at memory location 100

START:          #stores the address memory that points to the next line of code
    
    #Setting the number of times we want the program to loop
    loadi 10    #load inmediate value 10 into register A
    save @111    #save value of 10 into memory location 111: RAM[111]
    
    load @100     #reads memory address 100 and loads value into register A
    Add @101      #gets value in memory address 101 in RAM and adds it to whatever is in register A
    save @100    #saves contents of register A into memory address 100
    
    #Next, we are basically defining a loop control variable as in (for(i=0;...))
    load @110    #load RAM[110] into A
    incr        #increment the value in register A by 1 and store back in A
    save @110    #save value in A in RAM[110]
    
    #Set conditonal to break the loop
    jgt @111 @99    #set PC to address 99 if value in register A is greater than value at memory location 111                
    
    jump START  #sets the Program Counter (PC) to memory address that START points to (or refers to)

