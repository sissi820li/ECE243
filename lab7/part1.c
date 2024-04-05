int pixel_buffer_start; // global variable

void draw_line(double x1, double y1, double x2, double y2, short int line_color);
void plot_pixel(int x, int y, short int line_color);
void clear_screen();
int custom_round(double num);

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    volatile int * pixel_ctrl_ptr = (int *)0xFF203020;
    /* Read location of the pixel buffer from the pixel buffer controller */
    pixel_buffer_start = *pixel_ctrl_ptr;

    clear_screen();
    draw_line(0, 0, 150, 150, 0x001F);   // this line is blue
    draw_line(150, 150, 319, 0, 0x07E0); // this line is green
    draw_line(0, 239, 319, 239, 0xF800); // this line is red
    draw_line(319, 0, 0, 239, 0xF81F);   // this line is a pink color
}

// code not shown for clear_screen() and draw_line() subroutines
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

void plot_pixel(int x, int y, short int line_color)
{		
    volatile short int *one_pixel_address;

    one_pixel_address = pixel_buffer_start + (y << 10) + (x << 1);

    *one_pixel_address = line_color;
}

void clear_screen(){
	int y, x;
	
	for(x = 0; x < 320; x++){
		for(y = 0; y < 240; y++){
			plot_pixel (x, y, 0); //make all pixels black 
		}
	}
}
