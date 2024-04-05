.global _start
	.equ KEY_BASE, 0xFF200050
	.equ LEDs, 0xFF200000
	.equ DATA_REG, 0xFF200050
	
_start:
	
	movia r8, KEY_BASE
	movia r9, LEDs
	movia r10, KEY_LIST
	movi r12, 0 #counter for the number, cannot exceed 15
	movia r14, DATA_REG
	
copyloop:
	
	ldwio r13, (r14)
	
	ldw r11, (r10)
	beq r13, r11, key0_ON #if r12 = 1, key 0 is pressed
	
	ldw r11, 4(r10) 
	beq r13, r11, key1_ON
	
	ldw r11, 8(r10) 
	beq r13, r11, key2_ON
	
	ldw r11, 12(r10) 
	beq r13, r11, key3_ON
	
	continue: 
	stwio r12, (r9) 
	br copyloop
	

key0_ON:
	beq r13, r0, Counter1
	ldwio r13, (r8)
	br key0_ON
	Counter1:
	movi r12, 1 #counter = 1 
	br continue
	
key1_ON:
	beq r13, r0, check_max
	ldwio r13, (r8)
	br key1_ON
	check_max: 
	ldw r11, 16(r10) 
	bge r12, r11, continue
	Counter2: 
	addi r12, r12, 1 #increment counter 
	br continue
	
key2_ON:
	beq r13, r0, check_min
	ldwio r13, (r8)
	br key2_ON
	check_min: 
	ldw r11, (r10) 
	beq r12, r11, continue
	Counter3: 
	subi r12, r12, 1 #decrement counter 
	br continue
	
key3_ON:
	beq r13, r0, Counter4
	ldwio r13, (r8)
	br key3_ON
	Counter4: 
	movi r12, 0 #counter = 0
	br continue
	
KEY_LIST: .word 1, 2, 4, 8, 15
	
	