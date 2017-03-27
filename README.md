This repository is for code connected to i2c controlled displays.

the display I used might not have been the SSD1306since it cas been ordered from some not so informative retailer so the code might not work directly on other displays.

I'm planning to implement a version for arduino use.(if I have time/interest)

graphics.h

This is a very basic library for drawing basic shapes and bitmaps to char buffer in common oled screen page/column byte order.

	  column 1	 column 2
		LSB		   LSB
		 |			|
		 |			|
PAGE 1   |			|	...
		 |			|
		 |			|
		 |			|
		MSB		   MSB

	  column 1	 column 2
		LSB		   LSB
		 |			|
		 |			|
PAGE 2   |			|	...
		 |			|
		 |			|
		 |			|
		MSB		   MSB


i2cscreen.h

This is a library that provides functions to use internal i2c busses on a linux system. The one I used for testing was the Display Data Channel found on my laptops vga port.


Some of the code like display init sequence and command addresses have been cound and slightly modified from https://www.ccsinfo.com/forum/viewtopic.php?t=52836
