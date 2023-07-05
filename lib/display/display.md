# Low-level display hardware vd 'High-level' graphics API

display.h / .cpp : 
* driving the displays electrical signals
* writing commands and raw data bytes to the display
* manipulating pixels on the display buffer
* flushing the display buffer towards the display hardware

graphics.h / .cpp
* translate higher level graphics commands into raw pixel commands : drawing objects
    * line
    * rectangle
    * text
    * image / icon


# Coordinate System
* 0,0 is left-bottom (OpenGL convenstion)
* x is running from left to right
* y is running from bottom to top