#Parse assembly code and generate the appropriate machine language for the program

import sys

#===============================================================================
DIC_COMMANDS = {#First, deal with normal instructions
                'load':  0x44000000, 
                'loadi': 0x48000000, 
                'save':  0x4c000000, 
                'incr':  0x50000000, 
                'output':0x70000000,
                'jump':  0x74000000,
                'halt':  0x7c000000,
                
                #conditional branching instructions
                'jgt':   0x84000000,
                
                #Here are operation codes for the ALU. 
                #This arrangement is temporary
                'and':   0x00000000,
                'or' :   0x04000000,
                'add':   0x08000000,
                'sub':   0x18000000,
                'slt':   0x1c000000}
                
#===============================================================================

RAM_OFFSET = 32

def clean_up_empties(array):
    new_list = [element for element in array if (element!='' and element!=None and element != [])]
    return new_list

def replace_jump_labels(labels_and_loc,code_line):
    """Extremely inefficient. It takes a list of labels declared in assembly and
    replaces that string in the code with the address to jump to."""
    new_code = []
    #labels = [item[0] for item in labels_and_loc]
    #locations = [item[1] for item in labels_and_loc]
    
    for label,PC in labels_and_loc:
        item_index = 0
        for item in code_line:
            if label == item:
                code_line[code_line.index(item)] = '@'+str(PC)
                
    

def main():
    ''''''
    source_code_file = sys.argv[1]          #file containing assembly code for the CPU I am simulating
    
    with open(source_code_file,'r') as f:
        split_lines = []
        for line in f:
            split = []
            for word in line.rstrip().split():
                if word.startswith('#'):
                    break
                if word!='':
                    split.append(word)
                
                
            #split = [word for word in line.rstrip().split() if (not word.startswith("#"))]      #creating a list per line and ignoring comments '#'
            
            #The first item in split should be a commnand
            #print (split)
            split_lines.append(split)
    split_lines = clean_up_empties(split_lines)
    print(split_lines)
    
    
    
    
    #Here we should convert instructions to numbers
    
    #First dealing with the case that the line has only one word or element
    #this will most likely mean that we have a label, if it ends with ':'. i.e. 'LOOP:'
    #Also, write the values to a file:
    try:
        output_file = sys.argv[2]
    except IndexError:
        output_file = source_code_file.split('.')[0] + ".hex"
        
    
    program_counter = 0
    labels = []
    new_lines = []
    for line in split_lines:
        if line[0].endswith(":"):
            #Create appropriate code for when we have a label to jump back to 
            labels.append((line[0][:-1],program_counter))      
            continue
        
        #replace_jump_labels(line)
        new_lines.append(line)
        program_counter += 1
            
    #Save hex values into fill
    with open(output_file, 'w') as handler:    
        #Now do the preprocessor step to put jump address into code
        for line in new_lines:
            replace_jump_labels(labels,line)
            #print(line)
            #print("")
            
            hex_command = 0
            if len(line)<3:         #if the command has only two words, then the first 6 bits are for instruction and the rest are an address
                #Now we create the hex value command or machine code for the given instruction
                for word in line:
                    word = word.lower()
                    if word.startswith('@'):        #if we have an address, we don't need to look up the value
                        hex_val = int(word[1:])
                    else:
                        try:
                            hex_val = int(word)     #this clause is important for when dealing with inmediate values
                        except ValueError:
                            hex_val = DIC_COMMANDS[word]    #if the word cannot be cast into an integer, then it must be a word
                        
                    #User bitwise OR to accumulate commands per line into a single instruction 
                    hex_command = hex_command | hex_val
            else:           #this clause deals with instructions that specify more than one register
                word_index = 0
                for word in line:
                    word = word.lower()
                    if word.startswith('@'):
                        #calculate value and shift
                        shift_ammount = 0
                        if word_index == 1:
                            shift_ammount = 21
                        elif word_index == 2:
                            shift_ammount = 16
                        elif word_index == 3:
                            shift_ammount = 0           #this elif is not necessary, but it makes the code's intent clearer and easier to follow
                            
                        hex_val = int(word[1:])
                        hex_val = hex_val << shift_ammount
                    else:
                        try:
                            hex_val = int(word)     #this clause is important for when dealing with inmediate values
                        except ValueError:
                            hex_val = DIC_COMMANDS[word]    #if the word cannot be cast into an integer, then it must be a word
                            
                    hex_command = hex_command | hex_val
                    word_index += 1
                    
                    
            #Write binary code to file (but as decimal)
            print(line,hex(hex_command))
            handler.write(str(hex_command)+'\n')
        
        print(new_lines)
    
            
            
if __name__=='__main__':
    main()