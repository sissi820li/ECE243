.global _start
		.equ      COUNTER_DELAY, 500000 #change to 10000000 when using DEI_soc #25 million for 0.25s
		.equ	  KEY_BASE, 0xff200050
		.equ 	  EDGE_REG, 0xff20005C
		.equ      LEDs, 0xFF200000

_start: 	
	movia      r8, COUNTER_DELAY    # r8 = delay value 

	movia 		r21, KEY_BASE
	movia		r22, EDGE_REG
	
	movi r10, 0 #counter
	movi r11, 255 #max number

	movi r12, 0 #if r12 = 0, button press will pause counter
	
	movia r13, KEY_LIST
	movia r19, LEDs
			
CountUp:
	ldwio r23, (r22) #edge reg
	beq r23, r0, continue #pause or continue counter
	br buttonPressed
	#else
	continue: 
	bge r10, r11, resetCounter
	addi r10, r10, 1 #increment counter 
	stwio r10, (r19)		# write into LED0
	br Timer
	resetCounter: 
	movi r10, 0
	br Timer
	
Timer: 
	#check if button pressed first
	ldwio r23, (r22) 
	beq r23, r0, continue1
	br buttonPressed 
	
	continue1: #delay loop
	movia r8, COUNTER_DELAY
	loop1: subi r8, r8, 1
	bne r8, r0, loop1
	br CountUp
			
buttonPressed: 
	call whichKey 
	beq r12, r0, pause
	unpause:
	movi r12, 0
	call whichKey
	loop:
	ldwio r24, (r21) 
	beq r24, r0, resetEdge2
	br loop
	
	pause:
	movi r12, 1
	ldwio r24, (r21)
	beq r24, r0, resetEdge
	br pause
	
	resetEdge: 
	stwio r14, (r22)
	loop2: 
	ldwio r23, (r22)
	beq r23, r0, loop2
	br unpause
		
	resetEdge2: 
	stwio r14, (r22) 
	ldwio r23, (r22) 
	br continue

whichKey: #saves the bit that will be writen in EDGE_REG in r14
	ldwio r23, (r22)
	ldw r14, (r13) 
	beq r23, r14, return1
	
	ldw r14, 4(r13) 
	beq r23, r14, return1
	
	ldw r14, 8(r13)
	beq r23, r14, return1
	
	ldw r14, 12(r13) 
	beq r23, r14, return1 
	return1: ret
	
KEY_LIST: .word 0b001, 0b0010, 0b0100, 0b1000
	
	
	
	