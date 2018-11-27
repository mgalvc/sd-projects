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
	for (i = 0; i < size; i++) {
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

void sendATCommand(char* command, int size) {
	int i = 0;
	while (i < size) {
		if (IORD_ALTERA_AVALON_UART_STATUS(UART_BASE) & ALTERA_AVALON_UART_STATUS_TRDY_MSK) {
			IOWR_ALTERA_AVALON_UART_TXDATA(UART_BASE, command[i]);
			i++;
		}
	}
}

unsigned int uart_ok() {
	char a;

	while (1) {
		a = IORD_ALTERA_AVALON_UART_RXDATA(UART_BASE);
		if (a == 'K') {
			return 1;
		}
	}
}
void init_esp() {
	write_text("WAITING...", 10);

	while (1) {
		if (IORD_ALTERA_AVALON_PIO_DATA(BUTTONS_BASE) == 7) {
			break;
		}
		usleep(100000);
	}

	alt_putstr("AT+CWMODE_CUR=3\r\n");
	uart_ok();

	write_text("WIFI...", 7);
	alt_putstr("AT+CWJAP_CUR=\"WLessLEDS\",\"HelloWorldMP31\"\r\n");
	uart_ok();

	write_text("BROKER...", 9);
	alt_putstr("AT+CIPSTART=\"TCP\",\"192.168.1.103\",1883,7200\r\n");
	uart_ok();

	alt_putstr("AT+CIPSEND=15\r\n");
	uart_ok();
	char connect[] = { 0x10, 0x0d, 0x00, 0x04, 0x4d, 0x51, 0x54, 0x54, 0x04, 0x02, 0x00, 0x3c, 0x00, 0x01, 0x78 };
	sendATCommand(connect, 15);
	alt_putstr("\r\n");
	uart_ok();

	write_text("CONNECTED BROKER", 16);
	usleep(2000000);
}

void publish(int index) {
	char publish_A[] = {
			  0x30, 0x0f, 0x00, 0x0c, 0x74, 0x65, 0x73, 0x74,
			  0x65, 0x2f, 0x74, 0x65, 0x73, 0x74, 0x65, 0x31,
			  0x41
			};
	char publish_B[] = {
			  0x30, 0x0f, 0x00, 0x0c, 0x74, 0x65, 0x73, 0x74,
			  0x65, 0x2f, 0x74, 0x65, 0x73, 0x74, 0x65, 0x31,
			  0x42
			};
	char publish_C[] = {
			  0x30, 0x0f, 0x00, 0x0c, 0x74, 0x65, 0x73, 0x74,
			  0x65, 0x2f, 0x74, 0x65, 0x73, 0x74, 0x65, 0x31,
			  0x43
			};
	char publish_D[] = {
			  0x30, 0x0f, 0x00, 0x0c, 0x74, 0x65, 0x73, 0x74,
			  0x65, 0x2f, 0x74, 0x65, 0x73, 0x74, 0x65, 0x31,
			  0x44
			};
	char publish_E[] = {
			  0x30, 0x0f, 0x00, 0x0c, 0x74, 0x65, 0x73, 0x74,
			  0x65, 0x2f, 0x74, 0x65, 0x73, 0x74, 0x65, 0x31,
			  0x45
			};

	alt_putstr("AT+CIPSEND=17\r\n");
	uart_ok();

	switch(index) {
		case 0:
			sendATCommand(publish_A, 17);
			break;
		case 1:
			sendATCommand(publish_B, 17);
			break;
		case 2:
			sendATCommand(publish_C, 17);
			break;
		case 3:
			sendATCommand(publish_D, 17);
			break;
		case 4:
			sendATCommand(publish_E, 17);
			break;
	}

	alt_putstr("\r\n");
	uart_ok();
}

int main() {
	int outputs[] = {15, 23, 27, 29, 30};

	char lcd_options[][9] = {
			"1 - LED A",
			"2 - LED B",
			"3 - LED C",
			"4 - LED D",
			"5 - LED E"
	};

	char lcd_option_selected[][8] = {
			"LED A ON",
			"LED B ON",
			"LED C ON",
			"LED D ON",
			"LED E ON",
	};

	int i = 0;
	int previous_i;
	int selected = 0;

	IOWR_ALTERA_AVALON_PIO_DATA(LEDS_BASE, 31);
	init_lcd();
	init_esp();

	write_text(lcd_options[0], 9);

	while(1) {
		int in = IORD_ALTERA_AVALON_PIO_DATA(BUTTONS_BASE);

		previous_i = i;

		if (in == 13 && !selected) {
			i++;
		} else if (in == 14 && !selected) {
			i--;
		} else if (in == 7 && !selected) {
			// seleciona
			IOWR_ALTERA_AVALON_PIO_DATA(LEDS_BASE, outputs[i]);
			write_text(lcd_option_selected[i], 8);
			selected = 1;

			publish(i);
		} else if (in == 11) {
			selected = 0;
			//apaga todos os leds
			IOWR_ALTERA_AVALON_PIO_DATA(LEDS_BASE, 31);
			write_text(lcd_options[i], 9);
		} else if (in == 12 ) {
			init_esp();
			IOWR_ALTERA_AVALON_PIO_DATA(LEDS_BASE, 31);
			write_text(lcd_options[i], 9);
		}

		if (i > 4) {
			i = 0;
		}

		if (i < 0) {
			i = 4;
		}

		if (previous_i != i) {
			write_text(lcd_options[i], 9);
		}

		usleep(100000);
	}

	return 0;
}
