
#define AUDIO_ptr			0xFF203040

int main(void){
	struct audio_t {
	volatile unsigned int control;  // The control/status register
	volatile unsigned char rarc;	// the 8 bit RARC register
	volatile unsigned char ralc;	// the 8 bit RALC register
	volatile unsigned char wsrc;	// the 8 bit WSRC register
	volatile unsigned char wslc;	// the 8 bit WSLC register
    volatile unsigned int ldata;	// the 32 bit (really 24) left data register
	volatile unsigned int rdata;	// the 32 bit (really 24) right data register
	};

	struct audio_t *const audiop = ((struct audio_t *) AUDIO_ptr);
	
	int left, right, echol, echor; 
	double damping_constant = 0.5; //damping constant is between 0 and 1
	
	int samplesl[3200] = {0}; //size of array is 8000 hz * 0.4s
	int samplesr[3200] = {0}; 
	int i = 0; 
	
	while(1){
		if(audiop -> rarc > 0){ //check RARC if there is data to read 
			//if there is data that needs to be read: 

			//load input microphone channels, get 1 sample each 
			left = audiop -> ldata; 
			right = audiop -> rdata;

			echol = left + (int)(damping_constant*(float)samplesl[i]);
			echor = right + (int)(damping_constant*(float)samplesr[i]); 

			audiop -> ldata = echol; 
			audiop -> rdata = echor; 
			

			samplesl[i] = echol; 
			samplesr[i] = echor;

			if(i < 3199){
				i = i + 1;
			} else{
				i = 0; 
			}
		}
	}
}
	