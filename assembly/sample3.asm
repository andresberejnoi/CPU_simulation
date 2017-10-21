
#Setting the number of times we want the program to loop
#load some data into memory. I will implement a better way later
#To check that the program jumped correctly, at the end of the program the state 
# of RAM at locations RAM[25] should be 60. If it went wrong, it will be 0


loadi 10    #0 load 10 into A
save @22    #1 save 10 into RAM[22]


loadi 20    #2 load 20 into A
add @22     #3 add A=20 + RAM[22]=10 : 20 + 10 = 30 = A


save @22    #4 save 30 into RAM[25]

add @22     #5 add A=30 + RAM[22]=30 : 30 + 30 = 60 = A
incr        #6 increment value in A by 1, so A = 61
save @25    #7 store 61 in RAM[25]

jump END    #8 Jump to END
loadi 0     #9 A = 0
save @25    #10 RAM[25] = A = 0        ; since we are jumping, we should never execute this line

END:
    halt    #11 stop the program



