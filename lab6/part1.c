
int main(void){
	volatile int* LED_ptr = 0xff200000;
	volatile int* KEY_ptr = 0xff200050;
	volatile int* EDGE_reg = 0xff20005C; 
	
	int check_edge; 
	
	while(1){
		//check edge reg
		check_edge = *EDGE_reg; 
		if(check_edge == 1){ //key0 has been pressed
			*LED_ptr = 1023; //turn on LEDs
			//reset edge reg
			*EDGE_reg = 1; 
			
		} else if(check_edge == 2){ //key1 has been pressed
			*LED_ptr = 0; // turn off LEDs
			//reset edge reg
			*EDGE_reg = 2; 
		}
		
	}
	
}