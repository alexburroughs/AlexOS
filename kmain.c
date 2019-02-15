#include "io.h"
#include "kernel.h"

#define FB_COMMAND_PORT			0x3D4
#define FB_DATA_PORT			0x3D5

#define FB_HIGH_BYTE_COMMAND	14
#define FB_LOW_BYTE_COMMAND		15

#define SERIAL_COM1_BASE				0x3F8

#define SERIAL_DATA_PORT(base)			(base)
#define SERIAL_FIFO_COMMAND_PORT(base)	(base + 2)
#define SERIAL_LINE_COMMAND_PORT(base)	(base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base)	(base + 4)
#define SERIAL_LINE_STATUS_PORT(base)	(base + 5)

void fb_move_cursor(unsigned short pos);
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg);
void serial_configure_baud_rate(unsigned short com, unsigned short divisor);
void serial_configure_line(unsigned short com);
int serial_is_transmit_fifo_empty(unsigned int com);

static UINT16 VGA_DefaultEntry(unsigned char to_print) {
	return (UINT16) to_print | (UINT16)WHITE_COLOUR << 8;
}

void kmain() {
	TERMINAL_BUFFER = (UINT16*) VGA_ADDRESS;

	TERMINAL_BUFFER[0] = VGA_DefaultEntry('H');
	TERMINAL_BUFFER[1] = VGA_DefaultEntry('E');
	TERMINAL_BUFFER[2] = VGA_DefaultEntry('l');
	TERMINAL_BUFFER[3] = VGA_DefaultEntry('l');
	TERMINAL_BUFFER[4] = VGA_DefaultEntry('o');
    TERMINAL_BUFFER[5] = VGA_DefaultEntry(' ');
    TERMINAL_BUFFER[6] = VGA_DefaultEntry('W');
    TERMINAL_BUFFER[7] = VGA_DefaultEntry('o');
    TERMINAL_BUFFER[8] = VGA_DefaultEntry('r');
    TERMINAL_BUFFER[9] = VGA_DefaultEntry('l');
    TERMINAL_BUFFER[10] = VGA_DefaultEntry('d');
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

#define SERIAL_LINE_ENABLE_DLAB 		0x80

void serial_configure_baud_rate(unsigned short com, unsigned short divisor) {

	outb(SERIAL_LINE_COMMAND_PORT(com),
		SERIAL_LINE_ENABLE_DLAB);
	outb(SERIAL_DATA_PORT(com),
		(divisor >> 8) & 0x00FF);
	outb(SERIAL_DATA_PORT(com),
		divisor & 0x00FF);
}

void serial_configure_line(unsigned short com) {

	outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);
}

int serial_is_transmit_fifo_empty(unsigned int com) {

	return inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
}
