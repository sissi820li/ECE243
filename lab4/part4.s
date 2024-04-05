.global _start
		.equ      TIMER_BASE, 0xFF202000
		.equ      COUNTER_DELAY, 1000000 #1 million for 0.01s 
		.equ	  KEY_BASE, 0xff200050
		.equ 	  EDGE_REG, 0xff20005C
		.equ 	  LEDs, 0xFF200000

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
	
	movi r10, 0 #counter for hundredths 
	movi r11, 99 #max number for hundredths 

	movi r12, 0 #if r12 = 0, button press will pause counter
	
	movia r13, KEY_LIST
	
	movi r14, 0 #counter for seconds 
	movi r15, 7
	
	movia r16, LEDs
			
CountUp:
	ldwio r23, (r22) #edge reg
	beq r23, r0, continue 
	br buttonPressed #pause or continue counter
	#else
	continue: 
	call checkMax 
	mov r17, r14
	slli r17, r17, 7
	add r17, r17, r10 
	stwio r17, (r16) 
	br Timer
	resetCounter: 
	movi r10, 0
	movi r14, 0
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
	movi r12, 0 #next time will be continue 
	call whichKey
	loop:
	ldwio r24, (r21) 
	beq r24, r0, resetEdge2
	br loop
	
	pause:
	movi r12, 1 #next time will be unpause 
	ldwio r24, (r21)
	beq r24, r0, resetEdge
	br pause
	
	resetEdge: #reset but stay paused 
	stwio r14, (r22) #write into Edge_reg to reset
	loop1: 
	ldwio r23, (r22) #load edge reg into r23
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
	
checkMax: bne r10, r11, incrementHundreds #if r10 doesnt equal 99, max number not hit so increment 
	beq r14, r15, resetCounter #if both are max, reset counter 
	
	#at this point, hundreds is max but seconds is not (ex 6.99s) 
	changeValues:
	movi r10, 0 # (ex 6.00) 
	addi r14, r14, 1 # (ex 7.00)
	ret
	
	incrementHundreds: 
	addi r10, r10, 1
return: ret

	
KEY_LIST: .word 0b001, 0b0010, 0b0100, 0b1000
	
	