.text  # The numbers that turn into executable instructions
.global _start
_start:

/* r13 should contain the grade of the person with the student number, -1 if not found */
/* r10 has the student number being searched */


	movia r10, 423195		# r10 is where you put the student number being searched for
	
	movia r8, result
	ldw r11, 4(r8) #r11 contains the value n (r11 = 19)
	ldw r14, 4(r8)
	
	movia r12, Snumbers #load address of numbers array into r12
	ldw r13, (r12) #load first student ID into r13 
	
	movia r15, Grades
	ldb r16, (r15)
	
loop: subi r11, r11, 1
		ble r11, r0, finished
		ble r13, r0, finished
		beq r10, r13, finished 
		
		addi r12, r12, 4
		ldw r13, (r12) 
		br loop
		
finished: 
loop2:
		addi r11, r11, 1
		bge r11, r14, finished2
		
		addi r15, r15, 1
		ldb r16, (r15) 
		br loop2
		
finished2: 

iloop: br iloop


.data  	# the numbers that are the data 

/* result should hold the grade of the student number put into r10, or
-1 if the student number isn't found */ 

result: .word 0
n: .word 19
		
/* Snumbers is the "array," terminated by a zero of the student numbers  */
Snumbers: .word 10392584, 423195, 644370, 496059, 296800
        .word 265133, 68943, 718293, 315950, 785519
        .word 982966, 345018, 220809, 369328, 935042
        .word 467872, 887795, 681936, 0

/* Grades is the corresponding "array" with the grades, in the same order*/
Grades: .byte 99, 68, 90, 85, 91, 67, 80
        .byte 66, 95, 91, 91, 99, 76, 68  
        .byte 69, 93, 90, 72
	
	
	
	