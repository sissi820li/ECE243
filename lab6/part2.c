int main(void){
	volatile int* AUDIO_ptr = 0xff203040;
	
	int left, right, RARC; 
	while(1){
		RARC = *(AUDIO_ptr + 1); //read audio port of fifo reg 
		if((RARC & 0x000000ff) > 0){ //check RARC to see if there are samples to read 
			//if there is data that needs to be read: 
			
			//load input microphone channels, get 1 sample each 
			int left = *(AUDIO_ptr + 2); 
			int right = *(AUDIO_ptr + 3);
			
			//store both samples to output channels
			*(AUDIO_ptr + 2) = left; 
			*(AUDIO_ptr + 3) = right; 
		}
	}
}
	