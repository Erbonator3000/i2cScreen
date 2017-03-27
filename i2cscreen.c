
#include "i2cscreen.h"



/*open i2c connection file*/
int i2c_open(void){

int file;
char *filename = I2C_PORT;
	if ((file = open(filename, O_RDWR))<0) {
		printf("Failed to open the i2c bus\n");
		return -1;
	}
	return file;
}


/*close i2c connection file*/
void i2c_close(int file){
	close(file);
}


/*write n bytes to i2c slave*/
int i2c_write_buf(int file, char* buf, int n){
	if (ioctl(file, I2C_SLAVE, ADDRESS) < 0) {
		printf("Failed to reach the i2c screen\n");
		return -1;
	}
	if (write(file,buf,n) != n) {
		printf("Failed to write to the i2c screen\n");
		return -1;
	}
	return 1;
}


/*send a single command to i2c display*/
void send_command(char c){
	int file;
	if((file = i2c_open()) >= 0){
		char buf[]={0x00, c};
		i2c_write_buf(file, buf, 2);
		i2c_close(file);
	}
}

/*init display, found from https://www.ccsinfo.com/forum/viewtopic.php?t=52836*/
void  init_display(void){  
    // Init sequence for 128x64 OLED module
    send_command(SSD1306_DISPLAYOFF);                    // 0xAE

    send_command(SSD1306_SETDISPLAYCLOCKDIV);            // 0xD5
    send_command(0x80);                 // the suggested ratio 0x80
   
    send_command(SSD1306_SETMULTIPLEX);                  // 0xA8
    send_command(0x3F);
   
    send_command(SSD1306_SETDISPLAYOFFSET);              // 0xD3
    send_command(0x01);                                   // offset of 1
   
    send_command(SSD1306_SETSTARTLINE);// | 0x40);        // line #0
   
    send_command(SSD1306_CHARGEPUMP);                    // 0x8D
    send_command(0x14);  // using internal VCC
   
    send_command(SSD1306_MEMORYMODE);                    // 0x20
    send_command(0x00);          // 0x00 horizontal addressing
   
    send_command(SSD1306_SEGREMAP | 0x1); // rotate screen 180
   
    send_command(SSD1306_COMSCANDEC); // 0xC8 rotate screen 180
   
    send_command(SSD1306_SETCOMPINS);                    // 0xDA
    send_command(0x12);
   
    send_command(SSD1306_SETCONTRAST);                   // 0x81
    send_command(0xCF);
   
    send_command(SSD1306_SETPRECHARGE);                  // 0xd9
    send_command(0xF1);
   
    send_command(SSD1306_SETVCOMDETECT);                 // 0xDB
    send_command(0x40);

    send_command(SSD1306_DISPLAYALLON_RESUME);           // 0xA4
   
    send_command(SSD1306_NORMALDISPLAY);                 // 0xA6

    send_command(SSD1306_DISPLAYON);                     //switch on OLED 
}



void send_buffer(char* buffer){

int file;

	send_command(SSD1306_COLUMNADDR); //0x21
	send_command(0); //start column address
	send_command(SSD1306_LCDWIDTH-1); // Column end address

	send_command(SSD1306_PAGEADDR); //0x22
	send_command(0); //start page address
	send_command((SSD1306_LCDHEIGHT/8)-1);// End Page address

	if((file = i2c_open()) >= 0){
		if (ioctl(file, I2C_SLAVE, ADDRESS) < 0) {
		   printf("Failed to reach the i2c scree\n");
		}else{
			for(int i=0; i<8; i++){
				//page address command or something (just seen on i2c bus with working library) find out and fix your ignorance
				char buf[]={0x00, 0x10};
				if (write(file,buf,2) != 2)
        			printf("Failed setting page address\n");

				char buf2[]={0x00, 0x02};
				if (write(file,buf2,2) != 2)
        			printf("Failed setting page address\n");
				
				char buf3[]={0x00, 0xB0+i};
				if (write(file,buf3,2) != 2)
        			printf("Failed setting page address\n");

				
				char data[129];
				data[0]=0x40; //indicate upcoming data
				memcpy(data+1, buffer+i*128,128);
								
				if (write(file,data, 129) != 129)
        			printf("Failed to write to the i2c bus.\n");
				
			}
		}
		i2c_close(file);
	}
}




