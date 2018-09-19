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

#include <stdio.h>
#include "system.h"
#include "altera_avalon_pio_regs.h"

int main() {
	int count = 0;
	int current_led = LEDS_BASE;

	while (1) {
		if (IORD_ALTERA_AVALON_PIO_DATA(BUTTONS_BASE) == 0x01) {
			count++;
			if (count >= LEDS_DATA_WIDTH) {
				count = 0;
			}
		} else if (IORD_ALTERA_AVALON_PIO_DATA(BUTTONS_BASE) == 0x02) {
			count--;
			if (count < 0) {
				count = LEDS_DATA_WIDTH - 1;
			}
		}
		IOWR_ALTERA_AVALON_PIO_DATA(current_led, 0);
		current_led = LEDS_BASE + count;
		IOWR_ALTERA_AVALON_PIO_DATA(current_led, 1);
	}

	return 0;
}
