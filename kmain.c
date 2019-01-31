void fp_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg);

void kmain() {
	fp_write_cell(0, 'A', 2, 8);
}

void fp_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg) {

	char *fb = (char *) 0x000B8010;	
	fb[i] = c;
	fb[i + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}
