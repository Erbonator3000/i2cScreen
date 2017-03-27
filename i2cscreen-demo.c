

#include "i2cscreen.h"
#include "graphics.h"


int main(void){
	
	char display_buffer[1024];
	memset(display_buffer, 0x00, 1024);
	
	init_display();
	clear_buffer(display_buffer);

	draw_pixel(display_buffer, 2, 2);
	draw_line(display_buffer, 0,0,10,60);

	draw_box(display_buffer, 10, 10, 20, 20);	

	draw_box(display_buffer, 15, 20, 3, 3);	
	draw_box(display_buffer, 45, 20, 3, 3);
	draw_box(display_buffer, 20, 40, 30, 5);
	
	draw_circle(display_buffer, 70, 40, 14);

	send_buffer(display_buffer);
	
	return 0;
}
