#include "io.h"

#define FB_COMMAND_PORT			0x3D4
#define FB_DATA_PORT			0x3D5

#define FB_HIGH_BYTE_COMMAND	14
#define FB_LOW_BYTE_COMMAND		15

void fb_move_cursor(unsigned short pos);
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg);

void kmain() {
	
	fb_move_cursor(1);
	fb_write_cell(0, 'A', 2, 8);
	fb_move_cursor(2);
	fb_write_cell(1, 'A', 2, 8);
	fb_move_cursor(3);
	fb_write_cell(2, 'A', 2, 8);
	fb_move_cursor(4);
	fb_write_cell(4, 'A', 2, 8);
}

void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg) {

	char *fb = (char *) 0x000B8010;	
	fb[i] = c;
	fb[i + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}

void fb_move_cursor(unsigned short pos) {
	
	outb(FB_COMMAND_PORT, 	FB_HIGH_BYTE_COMMAND);
	outb(FB_DATA_PORT, 		((pos >> 8) & 0x00FF));
	outb(FB_COMMAND_PORT, 	FB_LOW_BYTE_COMMAND);
	outb(FB_DATA_PORT, 		pos & 0x00FF);
}
