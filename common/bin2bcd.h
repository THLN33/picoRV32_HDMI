/*
 * bin2bcd.h
 *
 *  Created on: 2 mars 2026
 *      Author: thierry
 */

#ifndef BIN2BCD_H_
#define BIN2BCD_H_

#include <stdint.h>

uint8_t bin2bcd(uint32_t bin, uint8_t *bcd, uint8_t nb_digit);
uint8_t bin2bcd_signed(int32_t bin, uint8_t *bcd, uint8_t nb_digit);
void print_bcd(int32_t val);

#endif /* BIN2BCD_H_ */
