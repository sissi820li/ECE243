#include <stdlib.h>
int pixel_buffer_start; // global variable
short int Buffer1[240][512]; // 240 rows, 512 (320 + padding) columns
short int Buffer2[240][512];

void wait_for_vsync();
void plot_pixel(int x, int y, short int line_color); 
void clear_screen(); 
void draw_line(double x1, double y1, double x2, double y2, short int line_color);
void draw_box(int start_x, int start_y, short int line_color);
int custom_round(double num);
void clear_frame(); 

int x_box_temp[8], y_box_temp[8]; 
int dx_temp[8], dy_temp[8];
volatile int * pixel_ctrl_ptr = (int *)0xFF203020;

int main(void) {
	int x_box[8], y_box[8];
	int dx[8], dy[8];
	int colour_box [8];
	int colour[10] = { 0xffff, 0xf800, 0x07e0, 0x001f, 0x07FF, 0xF81F, 0xFFE0, 
	0xFB80, 0xFDDD, 0xBFE0};
	
	for(int i = 0; i< 8; i++){
		dx[i] = (( rand() %2) *2) - 1;
		dx_temp[i] = dx[i];
		dy[i] = (( rand() %2) *2) - 1;
		dy_temp[i] = dy[i]; 
		x_box[i] = rand()%320;
		x_box_temp[i] = x_box[i]; 
		y_box[i] = rand()%240;
		y_box_temp[i] = y_box[i]; 
		colour_box[i] = colour[rand()%10];
	}
	
	 /* set front pixel buffer to Buffer 1 */
	 *(pixel_ctrl_ptr) = (int) &Buffer1; // first store the address in the back buffer
	 /* now, swap the front/back buffers, to set the front buffer location */
	 wait_for_vsync();
	 /* initialize a pointer to the pixel buffer, used by drawing functions */
	 pixel_buffer_start = *pixel_ctrl_ptr;
	 clear_screen(); // pixel_buffer_start points to the pixel buffer
	 /* set back pixel buffer to Buffer 2 */
	 *(pixel_ctrl_ptr + 1) = (int) &Buffer2;
	 pixel_buffer_start = *(pixel_ctrl_ptr + 1); // we draw on the back buffer
	 clear_screen(); // pixel_buffer_start points to the pixel buffer
	
	 while (1){
		for(int i = 0; i< 8; i++){ //loop and draw 8 boxes 
			draw_box(x_box[i], y_box[i], colour_box[i]);
		}
		for(int i = 0; i< 8; i++){ //loop and draw lines connection boxes 
			if(i == 7){ //connect last box to first box with line
				draw_line((double)x_box[i], (double)y_box[i], (double)x_box[0], (double)y_box[0],
			colour_box[i]); 
			} else{ //connect box to next box with line
				draw_line((double)x_box[i], (double)y_box[i], (double)x_box[i + 1], (double)y_box[i + 1],
			colour_box[i]);
			}
		}
			
		for(int i = 0; i <8; i++){ //loop through and change positions of boxes 
			x_box[i] += dx[i];
			y_box[i] += dy[i];
			if (x_box[i] == 0 || x_box[i] == 319){ //if box hits x edge  
			 	dx[i] *= -1; //change direction 
			 }
			if (y_box[i] == 0 || y_box[i] == 239){ //if box hits y edge 
			 	dy[i] *= -1; //change direction 
			 }
		}
 		wait_for_vsync(); // swap front and back buffers on VGA vertical sync
 		pixel_buffer_start = *(pixel_ctrl_ptr + 1); // new back buffer
		clear_screen();
 	}
}

// code for subroutines (not shown)
void wait_for_vsync() {
	volatile int * pixel_ctrl_ptr = (int *) 0xff203020; 
	int status;
	*pixel_ctrl_ptr = 1; //start double buffer 
	// write 1 into front buffer address register
	status = *(pixel_ctrl_ptr + 3); // stats = S bit
	while ((status & 0x01) != 0) { // poll until bit 0 (S bit) = 0 
		status = *(pixel_ctrl_ptr + 3);
	} 
}

void plot_pixel(int x, int y, short int line_color){
	volatile short int *one_pixel_address;
 
	one_pixel_address = pixel_buffer_start + (y << 10) + (x << 1);
 
	*one_pixel_address = line_color;
}

void clear_screen(){
	int y, x;
	for (x = 0; x < 320; x++)
		for (y = 0; y < 240; y++)
			plot_pixel (x, y, 0);
}

void draw_line(double x1, double y1, double x2, double y2, short int line_color){
	double slope = (y2 - y1)/(x2 - x1); 
	//check if line is too steep 
	if(abs(y2 - y1) > abs(x2 - x1)){ //slope is steep
		while(y1 != y2){ 
			x1 = x2 + slope*(y1 - y2); 
			x1 = custom_round(x1); 
			plot_pixel(x1, y1, line_color);
			if(y1 < y2){y1 ++;} 
			else{y1 --;}
			
		}
	} else{ //slope not steep 
		while(x1 != x2){
			y1 = y2 + slope*(x1 - x2); 
			y1 = custom_round(y1);
			plot_pixel(x1, y1, line_color); 
			if(x1 < x2){x1 ++;}
			else{x1 --;}
		}
	}
}

int custom_round(double num) { 
    if (num - (int)num >= 0.5){ //if decimal part >= .5 round up
        return (int)num + 1; 
	}
    else{ //round down
        return (int)num; 
	}
}

void draw_box(int x0, int y0, short int line_color){
	plot_pixel(x0, y0, line_color); 
	plot_pixel(x0 + 1, y0, line_color); 
	plot_pixel(x0, y0 + 1, line_color); 
	plot_pixel(x0 + 1, y0 + 1, line_color);  //plot 2x2 box 
}

void clear_frame(){
		for(int i = 0; i< 8; i++){ //loop and draw 8 boxes 
			draw_box(x_box_temp[i], y_box_temp[i], 0);
		}
		for(int i = 0; i< 8; i++){ //loop and draw lines connection boxes 
			if(i == 7){ //connect last box to first box with line
				draw_line((double)x_box_temp[i], (double)y_box_temp[i], (double)x_box_temp[0], (double)y_box_temp[0],
			0); 
			} else{ //connect box to next box with line
				draw_line((double)x_box_temp[i], (double)y_box_temp[i], (double)x_box_temp[i + 1], (double)y_box_temp[i + 1],
			0);
			}
		}
			
		for(int i = 0; i <8; i++){ //loop through and change positions of boxes 
			x_box_temp[i] += dx_temp[i];
			y_box_temp[i] += dy_temp[i];
			if (x_box_temp[i] == 0 || x_box_temp[i] == 319){ //if box hits x edge  
			 	dx_temp[i] *= -1; //change direction 
			 }
			if (y_box_temp[i] == 0 || y_box_temp[i] == 239){ //if box hits y edge 
			 	dy_temp[i] *= -1; //change direction 
			 }
		}
 		wait_for_vsync(); // swap front and back buffers on VGA vertical sync
 		pixel_buffer_start = *(pixel_ctrl_ptr + 1); // new back buffer
}

	
	