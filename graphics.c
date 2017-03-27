
#include "graphics.h"

/*set all pixels off*/
void clear_buffer(char* buffer){
	memset(buffer, 0, SSD1306_LCDWIDTH*SSD1306_LCDHEIGHT/8);
}


/*draw a single pixel*/
void draw_pixel(char* buffer, int x, int y){
	buffer[x+(y/8)*SSD1306_LCDWIDTH]|=0b00000001<<y%8;
}



/*draw line*/
//TODO check for vertical and horizontal lines
void draw_line(char* buffer, int x1, int y1, int x2, int y2){
	int w = x2-x1+1;
	int h = y2-y1+1;	
	if(w > h){
		for(int i=0; i<w; i++){
			draw_pixel(buffer, (x1+i) % SSD1306_LCDWIDTH, (i/(w/h))%SSD1306_LCDHEIGHT);
		}
	}else{
		for(int i=0; i<h; i++)
			draw_pixel(buffer, (i/(h/w)) % SSD1306_LCDWIDTH, (y1+i)%SSD1306_LCDHEIGHT);
	}
}


/*draw box*/
void draw_box(char* buffer, int x, int y, int width, int height){
	
	for(int i=x; i<=x+width; i++){
		draw_pixel(buffer, i, y);
		draw_pixel(buffer, i, y+height);
	}
		for(int i=y; i<=y+height; i++){
		draw_pixel(buffer, x, i);
		draw_pixel(buffer, x+width, i);
	}
}


/*draw circle using midpoint circle algorithm*/
void draw_circle(char* buffer, int x0, int y0, int radius){
	int x=radius;
	int y=0;
	int err=0;
	while(x>=y){
		draw_pixel(buffer, x0 + x, y0 + y);
        draw_pixel(buffer, x0 + y, y0 + x);
        draw_pixel(buffer, x0 - y, y0 + x);
        draw_pixel(buffer, x0 - x, y0 + y);
        draw_pixel(buffer, x0 - x, y0 - y);
        draw_pixel(buffer, x0 - y, y0 - x);
        draw_pixel(buffer, x0 + y, y0 - x);
        draw_pixel(buffer, x0 + x, y0 - y);
		
		if (err <= 0)
        {
            y += 1;
            err += 2*y + 1;
        }
        if (err > 0)
        {
            x -= 1;
            err -= 2*x + 1;
        }
	}
}


/*draw bitmap mapped in left to right top tp bottom MSB to LSB format*/
void draw_bmp(char* buffer, char* bmp, int width, int height, int x){
	
	for(int i=0; i<height/8; i++){
		for(int j=0; j<width; j++){
			for(int k=0; k<8; k++){
				int bufferIndex=(j+i*SSD1306_LCDWIDTH+x)%(SSD1306_LCDWIDTH*SSD1306_LCDHEIGHT/8);
				buffer[bufferIndex ]|= ((bmp[j/8+k*width/8+i*width] & (0b10000000>>(j%8))) << j%8 >> (7-k));
			}
		}
	}
}



