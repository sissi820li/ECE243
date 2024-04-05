/* Program to Count the number of 1's in a 32-bit word,
located at InputWord */

.global _start
_start:
main: 
	movia r8, InputWord 
	ldw r4, (r8) 
	movi r2, 0 #store output here
	call countOnes
	
endiloop: br endiloop

countOnes:
	movi r10, 0 #counter
	movi r11, 32 #biggest number for counter
	movi r12, 0 #store bit 0 or bit 1 
	
	loop:
		bge r10, r11, finished
		
		andi r12, r4, 1
		srli r4, r4, 1
		
		add r2, r2, r12
		addi r10, r10, 1
		br loop 
		
	finished: ret

InputWord: .word 19

Answer: .word 0
	
	