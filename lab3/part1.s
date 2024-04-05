/* Program to Count the number of 1's in a 32-bit word,
located at InputWord */

.global _start
_start:
	movia r8, InputWord #stores address of InputWord
	ldw r9, (r8) #r9 stores value of InputWord 
	ldw r13, 4(r8) #r13 stores value of Answer 
	
	movi r10, 0 #counter
	movi r11, 32 #biggest number for counter
	movi r12, 0 #store bit 0 or bit 1 
	
loop:
	bge r10, r11, finished #if counter = 32, all digits accounted for and program is done 
	
	andi r12, r9, 1 #store value of last digit in r12 
	srli r9, r9, 1 #shift program so second last digit becomes last digit 
	
	add r13, r13, r12 
	
	addi r10, r10, 1 #add to counter 
	br loop

finished: 

endiloop: br endiloop

InputWord: .word 0x4a01fead

Answer: .word 0
	
	