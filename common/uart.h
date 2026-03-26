#ifndef _UART_H
#define UART_H

#include "stdint.h"

// Définition de l'adresse de base et des offsets des registres
#define UART_BASE   	0x80000008

#define UART_DIVIDER	((volatile uint32_t *)0x80000008)
#define UART_DATA_CTL	((volatile uint32_t *)0x8000000c)

#define UART_DATA		((volatile uint8_t *)0x8000000c)



extern void uart_set_div(unsigned int div);
extern void uart_print_hex(unsigned int val);
extern char uart_getchar(void);
extern void uart_putchar(char ch);
extern void uart_puts(char *s);

#endif
