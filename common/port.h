/*
 * port.h
 *
 *  Created on: 21 mars 2026
 *      Author: thierry
 */

#ifndef PORT_H_
#define PORT_H_

#include <stdint.h>

// Définition de l'adresse de base et des offsets des registres
#define PORT_BASE		0x80000000

#define PORT_OUT  		(volatile uint8_t *)(PORT_BASE + 0x00)
#define PORT_IN  		(volatile uint8_t *)(PORT_BASE + 0x04)

void set_output(uint8_t val);
uint8_t get_output(void);
uint8_t get_input(void);

#endif /* PORT_H_ */
