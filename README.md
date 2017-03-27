graphics.h

This is a very basic library for drawing basic shapes and bitmaps to char buffer in common oled screen page/column byte order.

	  column 1	 column 2
		LSB		   LSB
		 |			|
		 |			|
PAGE 1   |			|
		 |			|
		 |			|
		 |			|
		MSB		   MSB




i2cScreen.h

This is a library that provides functions to use internal i2c busses on a linux system. The one I used for testing was the Display Data Channel found on my laptops vga port.
