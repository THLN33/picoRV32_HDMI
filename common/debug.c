/*
 * debug.c
 *
 *  Created on: 18 mars 2026
 *      Author: thierry
 */
#include "video_text.h"
#include "system_config.h"
#include "timer.h"
#include "uart.h"

void view_reg(uint32_t addr) {
	display_string("Reg 0x");
	display_hex(addr, 8);
    display_string(" : 0x");
    display_hex(*(uint32_t *)(addr), 8);
    display_string("\r\n");
}


void view_regs(uint32_t addr, uint32_t reg_nb) {
  for (uint32_t i=0;i<reg_nb;i++) {
    view_reg(addr+i*4);
  }
}

void view_system_config_regs(void) {
  view_regs(SYSTEM_CONFIG_BASE, 3);
}

void view_timer_regs(void) {
  view_regs(TIMER_BASE, 3);
}



void test_cpu_freq(void) {
	if (system_config_boost_cpu_frequency()) {
		uint32_t cpu_freq = system_config_get_cpu_frequency();
		uart_set_div(cpu_freq / 115200);
	}
	view_reg((uint32_t)CONFIG_REG2);
}



void dump_memory(uint32_t addr, uint32_t len) {
	for (uint32_t i=0;i<len;i+=4) {
		if (i%16 == 0) {
			display_string("\r\n0x");
			display_hex(addr+i, 8);
			display_string(" : ");
		}


		uint32_t data = *(uint32_t *)(addr + i);
		display_string("0x");
		display_hex(data, 8);
		display_string(" ");


	}
	display_string("\r\n");
}
