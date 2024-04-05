int main(void){
	volatile int* AUDIO_ptr = 0xff203040;
	volatile int* SWITCHES_ptr = 0xff200040;
	
	while(1){
		int sw = *SWITCHES_ptr; //sw tells us which switch is used 
		
		if(sw == 1){ //100 hz
			for(int i = 0; i < 40; i++){ //(8000 hz/ 100hz)/2 = 40 samples 
				*(AUDIO_ptr + 2) =  0xfffffff; //store 1 into left output 
				*(AUDIO_ptr + 3) =  0xfffffff; //store 1 into right output
			}
			for(int i = 0; i < 40; i++){ 
				*(AUDIO_ptr + 2) = 0; //store 0 into left output
				*(AUDIO_ptr + 3) = 0; //store 0 into right output
			}
		}
		
		if(sw == 2){ //111 hz
			for(int i = 0; i < 36; i++){
				*(AUDIO_ptr + 2) =  0xfffffff; 
				*(AUDIO_ptr + 3) =  0xfffffff;
			}
			for(int i = 0; i < 36; i++){
				*(AUDIO_ptr + 2) = 0; 
				*(AUDIO_ptr + 3) = 0;
			}
		}
		
		if(sw == 4){ //143 hz
			for(int i = 0; i < 28; i++){
				*(AUDIO_ptr + 2) =  0xfffffff; 
				*(AUDIO_ptr + 3) =  0xfffffff;
			}
			for(int i = 0; i < 28; i++){
				*(AUDIO_ptr + 2) = 0; 
				*(AUDIO_ptr + 3) = 0;
			}
		}
		
		if(sw == 8){ //167 hz
			for(int i = 0; i < 24; i++){
				*(AUDIO_ptr + 2) =  0xfffffff; 
				*(AUDIO_ptr + 3) =  0xfffffff;
			}
			for(int i = 0; i < 24; i++){
				*(AUDIO_ptr + 2) = 0; 
				*(AUDIO_ptr + 3) = 0;
			}
		}
		
		if(sw == 16){ //200 hz
			for(int i = 0; i < 20; i++){
				*(AUDIO_ptr + 2) =  0xfffffff; 
				*(AUDIO_ptr + 3) =  0xfffffff;
			}
			for(int i = 0; i < 20; i++){
				*(AUDIO_ptr + 2) = 0; 
				*(AUDIO_ptr + 3) = 0;
			}
		}
		
		if(sw == 32){ //250 hz
			for(int i = 0; i < 16; i++){
				*(AUDIO_ptr + 2) =  0xfffffff; 
				*(AUDIO_ptr + 3) =  0xfffffff;
				
			}
			for(int i = 0; i < 16; i++){
				*(AUDIO_ptr + 2) = 0; 
				*(AUDIO_ptr + 3) = 0;
				
			}
		}
		
		if(sw == 64){ //333 hz
			for(int i = 0; i < 12; i++){
				*(AUDIO_ptr + 2) =  0xfffffff; 
				*(AUDIO_ptr + 3) =  0xfffffff;
				
			}
			for(int i = 0; i < 12; i++){
				*(AUDIO_ptr + 2) = 0; 
				*(AUDIO_ptr + 3) = 0;
				
			}
		}
		
		if(sw == 128){ //500 hz
			for(int i = 0; i < 8; i++){
				*(AUDIO_ptr + 2) =  0xfffffff; 
				*(AUDIO_ptr + 3) =  0xfffffff;
			}
			for(int i = 0; i < 8; i++){
				*(AUDIO_ptr + 2) = 0; 
				*(AUDIO_ptr + 3) = 0;
			}
		}
		
		if(sw == 256){ //1000 hz
			for(int i = 0; i < 4; i++){
				*(AUDIO_ptr + 2) =  0xfffffff; 
				*(AUDIO_ptr + 3) =  0xfffffff;
				
			}
			for(int i = 0; i < 4; i++){
				*(AUDIO_ptr + 2) = 0; 
				*(AUDIO_ptr + 3) = 0;
			}
		}
		
		if(sw == 512){ //2000 hz
			for(int i = 0; i < 2; i++){ // (8000 hz/ 2000 hz)/2 = 2 samples
				*(AUDIO_ptr + 2) =  0xfffffff; 
				*(AUDIO_ptr + 3) =  0xfffffff;
			}
			for(int i = 0; i < 2; i++){ // (8000 hz/ 2000 hz)/2 = 2 samples
				*(AUDIO_ptr + 2) = 0; 
				*(AUDIO_ptr + 3) = 0;
			}
		}
	}
}
	