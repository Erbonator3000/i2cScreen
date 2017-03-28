

#include "i2cscreen.h"
#include "graphics.h"
#include "bitmaps.h"


int main(void){
	
	char display_buffer[1024];
	memset(display_buffer, 0x00, 1024);
	char img[512];
	memset(img,0xFF, 512);
	
	init_display();
	clear_buffer(display_buffer);

	draw_pixel(display_buffer, 2, 2);
	draw_line(display_buffer, 0,20,100,20);

	draw_box(display_buffer, 10, 10, 20, 20);	

	draw_box(display_buffer, 15, 20, 3, 3);	
	draw_box(display_buffer, 45, 20, 3, 3);
	draw_box(display_buffer, 20, 40, 30, 5);
	
	draw_circle(display_buffer, 70, 40, 14);

	
	//draw_bmp(display_buffer, img, 64,64,0,0);	
	
	send_buffer(display_buffer);
	
	return 0;
}
