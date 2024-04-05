.global _start
		.equ      TIMER_BASE, 0xFF202000
		.equ      COUNTER_DELAY, 25000000 #25 million for 0.25s
		.equ	  KEY_BASE, 0xff200050
		.equ 	  EDGE_REG, 0xff20005C
		.equ	  LEDs, 0xFF200000

_start: 	
	movia      r20, TIMER_BASE	# r20 = address of timer
	stwio      r0, (r20)	# set TO bit to 0

	movia      r8, COUNTER_DELAY    # r8 = delay value 
	srli       r9, r8, 16           # r9 stores upper 16 bits 
	andi       r8, r8, 0xFFFF       # r8 stores lower 16 bits
	stwio      r8, 0x8(r20)         # write to the timer period register (low)
	stwio      r9, 0xc(r20)         # write to the timer period register (high)

	movi       r8, 0b0110          
	stwio      r8, 0x4(r20)         # first 4 bits of control reg = 0110, enables cont and start

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
	stwio r10, (r19)		 
	br Timer
	resetCounter: 
	movi r10, 0
	br Timer
	
Timer: 
	#check if button pressed first
	ldwio r23, (r22) 
	beq r23, r0, continue1
	br buttonPressed 
	
	continue1:
	ldwio      r8, (r20)         # read T0 bit
	andi       r8, r8, 0b1		#if T0 1, r8 = 1. else r8 = 0
	beq        r8, r0, Timer     # if r8 = 1, 25 million cycles passed (0.25s)
								 # if r8 = 0, keep checking T0 until T0 = 1
	stwio      r0, (r20)         # clear the TO bit
	
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
	loop1: 
	ldwio r23, (r22)
	beq r23, r0, loop1
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
	
	