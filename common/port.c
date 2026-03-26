/*
 * port.c
 *
 *  Created on: 21 mars 2026
 *      Author: thierry
 */
#include "port.h"

void set_output(uint8_t val) {
	*PORT_OUT = val;
}

uint8_t get_output(void) {
	return *PORT_OUT;
}

uint8_t get_input(void) {
	return *PORT_IN;
}
