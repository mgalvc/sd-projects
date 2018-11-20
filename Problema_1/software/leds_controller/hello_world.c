/*
 * "Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It runs with or without the MicroC/OS-II RTOS and requires a STDOUT
 * device in your system's hardware.
 * The memory footprint of this hosted application is ~69 kbytes by default
 * using the standard reference design.
 *
 * For a reduced footprint version of this template, and an explanation of how
 * to reduce the memory footprint for a given application, see the
 * "small_hello_world" template.
 *
 */

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
	alt_putstr("AT+CIPSTART=\"TCP\",\"192.168.1.102\",1883,7200\r\n");
	uart_ok();


	alt_putstr("AT+CIPSEND=14\r\n");
	uart_ok();
	alt_putchar(0x10);
	alt_putchar(0x0D);
	alt_putchar(0x00);
	alt_putchar(0x04);
	//MQTT
	alt_putchar(0x4D);
	alt_putchar(0x51);
	alt_putchar(0x54);
	alt_putchar(0x54);
	alt_putchar(0x04);
	alt_putchar(0x02);
	alt_putchar(0xFF00);
	//es
	alt_putchar(0x65);
	alt_putchar(0x73);
	alt_putstr("\r\n");
	uart_ok();

	write_text("CONNECTED BROKER", 16);
	usleep(2000000);
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
		} else if (in == 7) {
			// seleciona
			IOWR_ALTERA_AVALON_PIO_DATA(LEDS_BASE, outputs[i]);
			write_text(lcd_option_selected[i], 8);
			selected = 1;
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
