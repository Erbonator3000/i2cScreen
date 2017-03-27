#ifndef I2CGRAPHICS
#define I2CGRAPHICS

#include <string.h>

#define SSD1306_LCDWIDTH      128
#define SSD1306_LCDHEIGHT      64


void clear_buffer(char* buffer);

void draw_pixel(char* buffer, int x, int y);

void draw_line(char* buffer, int x1, int y1, int x2, int y2);

void draw_box(char* buffer, int x, int y, int width, int height);

void draw_circle(char* buffer, int x0, int y0, int radius);


#endif
