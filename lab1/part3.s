.global _start
_start:
	
	movi r10, 1 #start with 1 since it is the smallest number to add 
	movi r11, 0
	movi r12, 30 #this is the biggest number to add 
	
	loop: add r11, r11, r10 #equivalent to r11 = r11 + r10 
	addi r10, r10, 1 #r10 = r10 + 1, add one to r10 to add the next number 
	ble r10, r12, loop #ends loop once r10 is equal to r12 (30) 
	
	DONE: br DONE
	
	