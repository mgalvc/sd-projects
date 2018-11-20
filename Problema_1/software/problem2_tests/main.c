#include "altera_avalon_pio_regs.h"
#include "system.h"
#include "sys/alt_stdio.h";
#include "altera_avalon_uart_regs.h"

void enable() {
	IOWR_ALTERA_AVALON_PIO_DATA(LCD_EN_BASE, 1);
	usleep(200);
	IOWR_ALTERA_AVALON_PIO_DATA(LCD_EN_BASE, 0);
}

void clear_display() {
	// clear display - 00000001
	IOWR_ALTERA_AVALON_PIO_DATA(LCD_RS_BASE, 0);
	IOWR_ALTERA_AVALON_PIO_DATA(LCD_DATA_BASE, 0x1);
	enable();
	usleep(3000);
}

void write_text(char* text, int size) {
	clear_display();
	IOWR_ALTERA_AVALON_PIO_DATA(LCD_RS_BASE, 1);

	int i;
	for (i = 0; i < size && text[i] != 'x'; i++) {
		IOWR_ALTERA_AVALON_PIO_DATA(LCD_DATA_BASE, text[i]);
		enable();
		usleep(100);
	}
}

void init_lcd() {
	IOWR_ALTERA_AVALON_PIO_DATA(LCD_RS_BASE, 0);

	// function set 3x - 00110000
	IOWR_ALTERA_AVALON_PIO_DATA(LCD_DATA_BASE, 0x30);
	enable();
	usleep(4100);
	IOWR_ALTERA_AVALON_PIO_DATA(LCD_DATA_BASE, 0x30);
	enable();
	usleep(100);
	IOWR_ALTERA_AVALON_PIO_DATA(LCD_DATA_BASE, 0x30);
	enable();
	usleep(100);

	// real function set - 00111000
	IOWR_ALTERA_AVALON_PIO_DATA(LCD_DATA_BASE, 0x38);
	enable();
	usleep(100);

	// display on/off - 00001000
	IOWR_ALTERA_AVALON_PIO_DATA(LCD_DATA_BASE, 0x8);
	enable();
	usleep(100);

	clear_display();

	// entry mode - 00000110
	IOWR_ALTERA_AVALON_PIO_DATA(LCD_DATA_BASE, 0x6);
	enable();
	usleep(100);

	// display on/off - 00001110 - cursor appears and doesn't blinks
	IOWR_ALTERA_AVALON_PIO_DATA(LCD_DATA_BASE, 0xE);
	enable();
	usleep(100);

	// send some data to test - 00110000
	IOWR_ALTERA_AVALON_PIO_DATA(LCD_RS_BASE, 1);
	IOWR_ALTERA_AVALON_PIO_DATA(LCD_DATA_BASE, '0');
	enable();
	usleep(100);
}

void sendAT(int i) {
	switch(i) {
		case 0:
			alt_putstr("AT\r\n");
			break;
		case 1:
			alt_putstr("AT+RST\r\n");
			break;
		case 2:
			alt_putstr("AT+GMR\r\n");
			break;
		case 3:
			alt_putstr("AT+CWMODE_CUR=3\r\n");
			break;
		case 4:
			alt_putstr("AT+CWLAP\r\n");
	}
}

int main() {
	int outputs[] = {15, 23, 27, 29, 30};

	char lcd_options[][15] = {
			"ATxxxxxxxxxxxxx",
			"AT+RSTxxxxxxxxx",
			"AT+GMRxxxxxxxxx",
			"AT+CWMODE_CUR=3",
			"AT+CWLAPxxxxxxx"
	};

	int i = 0;
	int previous_i;

	init_lcd();

	write_text(lcd_options[0], 15);

	while(1) {
		int in = IORD_ALTERA_AVALON_PIO_DATA(BUTTONS_BASE);

		previous_i = i;

		if (in == 13) {
			i++;
		} else if (in == 14) {
			i--;
		} else if (in == 7) {
			sendAT(i);
		}

		if (i > 4) {
			i = 0;
		}

		if (i < 0) {
			i = 4;
		}

		if (previous_i != i) {
			write_text(lcd_options[i], 15);
		}

		usleep(100000);
	}

	return 0;
}
