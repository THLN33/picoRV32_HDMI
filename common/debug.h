/*
 * debug.h
 *
 *  Created on: 18 mars 2026
 *      Author: thierry
 */

#ifndef DEBUG_H_
#define DEBUG_H_


void view_reg(unsigned int);

void view_system_config_regs(void);
void view_timer_regs(void);

void dump_memory(uint32_t addr, uint32_t len);

#endif /* DEBUG_H_ */
