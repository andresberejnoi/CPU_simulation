#file to test if assignment preprocessor in version v0.4 is working correctly

ptr_to_buffer = @10
moving_prt = @11

idx = @9

loadi 10
save ptr_to_buffer

ptr_to_buffer = 20

jgt idx moving_prt ptr_to_buffer


x = @10