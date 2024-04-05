int main(void){
	volatile int* AUDIO_ptr = 0xff203040;
	
	int left, right, RARC, WSRC, echol, echor; 
	int damping_constant = 0.5; //damping constant is between 0 and 1
	
	int samplesl[3200]; //size of array is 8000 hz * 0.4s
	int samplesr[3200]; 
	int i = 0; 
	
	while(1){
		RARC = *(AUDIO_ptr + 1);
		if((RARC & 0x000000ff) > 0){ //check RARC if there is data to read 
			//if there is data that needs to be read: 

			//load input microphone channels, get 1 sample each 
			left = *(AUDIO_ptr + 2); 
			right = *(AUDIO_ptr + 3);

			echol = left + damping_constant*samplesl[i];
			echor = right + damping_constant*samplesr[i]; 
		}
		WSRC = *(AUDIO_ptr + 3);
		if(WSRC > 0){ //check WSRC if there is space to write data
			//store both samples to output channels
			*(AUDIO_ptr + 2) = echol; 
			*(AUDIO_ptr + 3) = echor; 
		}

		samplesl[i] = left; 
		samplesr[i] = right;

		if(i < 3200){i = i + 1;
		} else{
			i = 0; 
		}
	}
}
	