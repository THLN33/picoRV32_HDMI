/*
 * main.c
 *
 *  Created on: 25 févr. 2026
 *      Author: thierry
 */

# include <stdint.h>
# include <stdbool.h>

#include "leds.h"
#include "uart.h"
#include "timer.h"
#include "video_text.h"


#include "sram_ext_test.h"

#include "video_text_demo.h"






/* The picorv32 core implements several counters and
   instructions to access them.  These are part of the
   risc-v specification.  Function readtime uses one
   of them.
*/

static inline unsigned int readtime(void) {
	unsigned int val;
    asm volatile("rdtime %0" : "=r" (val));
    return val;
}


void video_text_demo(void) {
	uint8_t v = 0;

	uint32_t cpu_freq = system_config_get_cpu_frequency();
	test_video_text();
	while(1) {
		uart_puts("Test ...\r\n");

		scroll_line(40);

	    uart_puts("time is ");
	    uart_print_hex(readtime());
	    uart_puts("\r\n");

	    v = get_leds();
	    set_leds(v+1);

	    delay_ticks(cpu_freq / 10);
	}
}


#include "bin2bcd.h"

uint16_t _write(uint16_t fd, char *buff, uint16_t len) {

	for (int i=0;i<len;i++) {
		display_char(buff[i]);
	}
	return 0;
}



int main(void) {

	uint8_t v = get_leds();

	set_leds(~v);

	//video_text_demo();

	uint32_t cpu_freq = system_config_get_cpu_frequency();
	uart_set_div(cpu_freq / 115200);

	clear_video_memory();


	uint8_t line = 0;
	while(1) {
/*
		for (int i=0;i<40;i++) {
			display_string("This is a test for Video_Text_96x42 module line = 0x");
			display_hex(line++, 4);
			display_string("\r\n");
			display_string("\r\n");
			display_string("********************************************************************************************************************************");
			display_string("\r\n");
		}
*/
		display_string("Led = ");
		display_hex(v, 2);
		display_string("\r\n");

		display_string("time is ");
		//print_bcd()
		display_hex(readtime(), 8);
		display_string("\r\n");

	    v = get_leds();
	    set_leds(v+1);

	    delay_ticks(cpu_freq>>2);
	}
}
