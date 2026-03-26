/*
 * system_config.c
 *
 *  Created on: 18 mars 2026
 *      Author: thierry
 */
#include "system_config.h"

static uint32_t cpu_freq;


void system_config_init(void) {
	*CONFIG_REG2 = 0x00;
	cpu_freq = CPU_FREQUENCY_24;
}

uint32_t system_config_get_cpu_frequency(void) {
	switch(*CONFIG_REG2 & 0x03) {

	case 0:
		cpu_freq = CPU_FREQUENCY_24;
		break;
	case 1:
		cpu_freq = CPU_FREQUENCY_48;
		break;
	case 2:
		cpu_freq = CPU_FREQUENCY_60;
		break;
	}
	return cpu_freq;
}


uint8_t system_config_boost_cpu_frequency(void) {
	uint32_t config_reg1 = *CONFIG_REG1;
	uint8_t clk_available = config_reg1 & 0x03;
	uint8_t freq_change;

	//unsigned char nb_leds =
	//unsigned char nb_buttons =

	switch (clk_available) {
	case 0:
		// 24MHz
		cpu_freq = CPU_FREQUENCY_24;
		break;
	case 1:
		// 48MHz
		cpu_freq = CPU_FREQUENCY_48;
		break;
	case 2:
		// 60MHz
		cpu_freq = CPU_FREQUENCY_60;
		break;
	}

	freq_change = (clk_available |= *CONFIG_REG2);
	*CONFIG_REG2 = clk_available;
	return freq_change;
}



