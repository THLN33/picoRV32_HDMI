/*
 * main.c
 *
 *  Created on: 24 jan. 2026
 *      Author: thierry
 */

# include <stdint.h>
# include <stdbool.h>

#include "system_config.h"
#include "leds.h"
#include "uart.h"
#include "timer.h"
//#include "countdown_timer.h"

#include "sram_ext_test.h"
#include "video_text.h"
#include "video_text_demo.h"



#ifdef _Z
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
#endif



#include "bin2bcd.h"

uint16_t _write(uint16_t fd, char *buff, uint16_t len) {

	for (int i=0;i<len;i++) {
		display_char(buff[i]);
	}
	return 0;
}

uint8_t downloader_run(uint32_t memsize);
uint8_t launch_app(void);

int main(void) {
	set_leds(0x55);

	system_config_init();

	system_config_boost_cpu_frequency();

	uint32_t cpu_freq = system_config_get_cpu_frequency();
	uart_set_div(cpu_freq / 115200);

	display_clear();

	//...
    uint8_t x = (SCREEN_DX - (LOGO_PICO_DX + LOGO_RV32_DX)) >> 1;
    display_pico_logo(x+0, 0+1);
    display_RV32_logo(x+10, 0);

    display_qrcode(SCREEN_DX - QR_CODE_DX -1, SCREEN_DY - QR_CODE_DY);

    display_picoRV32(0, 4);
    display_string("@");
    print_bcd(cpu_freq / 1000000UL);
    display_string(" MHz\r\n");
    display_string("\r\n");

	uint8_t error = launch_app();

	display_set_cursor_position_x_y(0, 5);
	display_string("Launch error     = ");
	print_bcd(error);
	display_string("\r\n");

	dump_memory(0x20000000, 32);



    display_string("HDMI Video Text ");
    print_bcd(SCREEN_DX);
    display_string("x");
    print_bcd(SCREEN_DY);
    display_string(" ");
    print_bcd(SCREEN_REFRESH);
    display_string(" Hz\r\n");

    display_string("SRAM memory size = ");
	uint32_t memsize = get_mem_size();
	print_bcd(memsize);
	//display_hex(memsize, 8);
	display_string(" bytes\r\n");
	// Run the mem_test
	if (mem_test_sram_dword(memsize))
		display_string("SRAM memory test FAILED.\r\n");
	else
		display_string("SRAM memory test PASSED.\r\n");


	downloader_run(memsize);

	while(1) {

	}

#ifdef _Z
	test_video();

	unsigned char v = 0;
	while(1) {

		scroll_line(40);

	    uart_puts("time is ");
	    uart_print_hex(readtime());
	    uart_puts("\r\n");

	    v = get_leds();
	    set_leds(v+1);

		cdt_delay(cpu_freq / 10);

	}
#endif

}
