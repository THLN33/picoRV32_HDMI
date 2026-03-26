/*
 * system_config.h
 *
 *  Created on: 18 mars 2026
 *      Author: thierry
 */

#ifndef SYSTEM_CONFIG_H_
#define SYSTEM_CONFIG_H_

#include <stdint.h>

// Définition de l'adresse de base et des offsets des registres
#define SYSTEM_CONFIG_BASE		0xE0000000

#define CONFIG_REG0	 			(const uint32_t *)(SYSTEM_CONFIG_BASE + 0)
#define CONFIG_REG1	 			(const uint32_t *)(SYSTEM_CONFIG_BASE + 4)
#define CONFIG_REG2	 			(uint32_t *)(SYSTEM_CONFIG_BASE + 8)

#define	CPU_FREQUENCY_60		(uint32_t)60E6
#define	CPU_FREQUENCY_48		(uint32_t)48E6
#define	CPU_FREQUENCY_24		(uint32_t)24E6


#define SCREEN_DX              	*((uint8_t *)CONFIG_REG0 + 0)
#define SCREEN_DY              	*((uint8_t *)CONFIG_REG0 + 1)
#define SCREEN_REFRESH			*((uint8_t *)CONFIG_REG0 + 2)


void system_config_init(void);
uint32_t system_config_get_cpu_frequency(void);
uint8_t system_config_boost_cpu_frequency(void);


#endif /* SYSTEM_CONFIG_H_ */
