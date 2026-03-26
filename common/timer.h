/*
 * timer.h
 *
 *  Created on: 18 mars 2026
 *      Author: thierry
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>

// Définition de l'adresse de base et des offsets des registres
#define TIMER_BASE   	0x80000010
#define TIMER_COUNT  	(volatile uint32_t *)(TIMER_BASE + 0x00)
#define TIMER_RELOAD 	(volatile uint32_t *)(TIMER_BASE + 0x04)
#define TIMER_CTRL   	(volatile uint32_t *)(TIMER_BASE + 0x08)
#define TIMER_STAT   	(volatile uint32_t *)(TIMER_BASE + 0x0C)

// Masques de contrôle
#define TIMER_EN        (1 << 0)
#define TIMER_UP        (1 << 1)
#define TIMER_DOWN      (0 << 1)
#define TIMER_IRQ_EN    (1 << 2)

#define TIMER_IRQ_FLAG  (1 << 31)


void delay_ticks(uint32_t ticks);

#endif /* TIMER_H_ */
