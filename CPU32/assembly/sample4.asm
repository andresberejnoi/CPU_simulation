#Subtract 1 from number until it becomes zero
loadi 10
save @30                #store 10 in RAM[30]

loadi 1
save @1                 #store 1 in RAM[0]

loadi 0
save @0                 #store 0 in RAM[0]


MAIN:
    #Check if the value we are decreasing is greater than zero to jump
    #into the subtraction sub-routine:
    
    jgt @30 @0 SUB      #if the value in RAM[30] still greater than 0 (in RAM[0]) then keep subtracting 1
    
    halt                #end program if we get to this point

SUB:
    #Load value at RAM[30] and subtract 1 from it. Store result back into RAM[30]
    load @30            #Load into register A the value to subtract from
    sub @1              #subtract value at RAM[1] (hardcoded to 1) from value at register A
    output              #display to stdout the contents in the A register
    save @30            #save result back into RAM[30]
    
    jump MAIN           #go back to the main operation to keep looping