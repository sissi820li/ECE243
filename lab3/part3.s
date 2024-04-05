.text
/* Program to Count the number of 1's and Zeroes in a sequence of 32-bit words,
and determines the largest of each */

.global _start
_start:

#GreatestOnes is stored in r5, which should be 1f (decimal 32) since value with most 1s in TEST_NUM is 0x7FFFFFFF
#GreatestZeroes is stored in r15, which should be 1f as well since the value with most 0s is 0x00000001

main:
	movia r8, TEST_NUM
	ldw r4, (r8) #stores value of first value in TEST_NUM
	
	movia r9, LargestOnes
	ldw r5, (r9)
	
	movia r14, LargestZeroes
    ldw r15, (r14)
	
loop1: 
	beq r4, r0, finished1
	movi r2, 0 #store output for number of 1s here
	movi r3, 0 #store output for number of 0s here
	
	call countOnes
	
	addi r8, r8, 4 #move to next address in TEST_NUM
	ldw r4, (r8) 
	
	bge r2, r5, GreatestOne
checknext:  
	bge r3, r15, GreatestZero
	br loop1

GreatestOne: 
	stw r2, (r9)
	ldw r5, (r9)
	br checknext  

GreatestZero: 
	stw r3, (r14)
	ldw r15, (r14) 
	br loop1 
	
finished1:
	
endiloop: br endiloop

countOnes:
	movi r10, 0 #counter
	movi r11, 32 #biggest number for counter
	movi r12, 0 #store bit 1
	movi r13, 0 #store bit 0 
	
	loop:
		bge r10, r11, finished
		
		andi r12, r4, 1 #stores 1 in r12 if last bit in r4 is 1
		
		xori r4, r4, 1 #changes last bit in r4 to 0 if it is 1
		andi r13, r4, 1 #stores 1 in r13 if last bit in r4 is 1
		
		srli r4, r4, 1
		
		add r2, r2, r12
		add r3, r3, r13
		
		addi r10, r10, 1
		br loop 
		
	finished: ret

.data
TEST_NUM:  .word 0x4a01fead, 0x7FFFFFFF, 0xF677D671,0xDC9758D5,0xEBBD45D2,0x8059519D
            .word 0x76D8F0D2, 0xB98C9BB5, 0xD7EC3A9E, 0xD9BADC01, 0x89B377CD
            .word 0x00000001, 0  # end of list 

LargestOnes: .word 0
LargestZeroes: .word 0