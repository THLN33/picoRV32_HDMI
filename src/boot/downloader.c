/*
 * downloader.c
 *
 *  Created on: 25 févr. 2026
 *      Author: thierry
 */
#include <stdint.h>
#include <stdbool.h>
#include "video_text.h"
#include "uart.h"
#include "bin2bcd.h"


#define RAM_START 					0x20000000

#define APP_ADDR					((uint8_t *)RAM_START)

#define MAGIC_NUMBER				0x61706766
#define REVERSED_MAGIC_NUMBER		0x66677061

#define MAGIC_NUMBER_ADDR			((uint32_t *)RAM_START+0)
#define APP_CRC						((uint32_t *)RAM_START+1)
#define APP_TEXT_SIZE				((uint32_t *)RAM_START+2)
//#define APP_SIZE					((uint32_t *)RAM_START+2)
#define RAM_SIZE					((uint32_t *)RAM_START+3)
#define JMP_ADDR					((uint32_t *)RAM_START+4)

void start_application(uint32_t *entry_point) {
    // 1. Déclarer le pointeur de fonction
    void (*app_main)(void) = (void (*)(void))entry_point;

    // 2. (Optionnel mais recommandé) Désactiver les interruptions du bootloader
    // disable_interrupts();

    // 3. Sauter vers la RAM
    app_main();
}


#define SOH (0x01)  // Start of Header
#define ACK (0x06)  // Acknowledge
#define NAK (0x15)  // Negative Ack
#define EOT (0x04)  // End of Transmission
#define CAN (0x18)  // Cancel

#define _USE_CRC

#ifdef _USE_CRC
#define CRC_READY 'C'

uint16_t crc16_update(uint16_t crc, uint8_t data) {
    crc = crc ^ ((uint16_t)data << 8);
    for (int i = 0; i < 8; i++) {
        if (crc & 0x8000)
            crc = (crc << 1) ^ 0x1021; // Polynôme CCITT
        else
            crc <<= 1;
    }
    return crc;
}


#endif




uint8_t get_char_print_hex(void) {
	uint8_t ch = uart_getchar();
	//display_hex(ch, 2);
	//display_char(' ');
	return ch;
}

//__attribute__((optimize("no-tree-loop-distribute-patterns")))
uint32_t xmodem_receive(uint8_t *dest_addr) {
	uint8_t packet[2+128+2];
    uint8_t current_blk = 1;
    uint8_t *ptr = dest_addr;
    uint8_t data, ok;

    display_string("Waiting for downloader ...\r\n");
#ifdef _USE_CRC
    uart_putchar(CRC_READY); // Demande de transfert
#else
    uart_putchar(NAK); // Envoie NAK pour forcer le mode Checksum 8-bit
#endif

    while (1) {
        uint8_t first_char = uart_getchar();

        if (first_char == EOT) {
        	uart_putchar(ACK);
            return (uint32_t)(ptr - dest_addr);
        }

        if (first_char == SOH) {
        	ok = false;
        	display_string("\rBlk:");
        	display_hex(current_blk, 2);
        	//print_bcd(current_blk);
        	//display_string("\r\nRx:");

#ifdef _USE_CRC
        	uint16_t ctl = 0;
#else
        	uint8_t ctl = 0;
#endif
        	for (int i=0;i<2+128+2;i++) {
        		data = get_char_print_hex();
                packet[i] = data;
                if ( (i>=2) && (i<2+128) ) {
#ifdef _USE_CRC
                    	ctl = crc16_update(ctl, data);
#else
                    	ctl += data;
#endif
                }
        	}

        	if (packet[0] == current_blk) {

        		if (packet[1] == (current_blk^0xFF)) {

                    //display_string("\r\n");
                    display_string(", Ctl=");
                    display_hex(ctl, 4);

                    uint16_t received_crc = (packet[2+128+0] << 8) | packet[2+128+1];
                    if (received_crc == ctl) {
// @TODO check max size
                    	for (int i=0;i<128;i++) {
                    		*ptr++ = packet[2+i];
                    	}
                        current_blk++;
                        ok = true;
                        display_string(" Ok");
                    } else {
                    	display_string(" Ko");
                    }
                    //display_string("\r");

        		} else {
        			display_string("W~b\r\n");
        		}
        	} else {
    			display_string("W b\r\n");
    		}

            if (ok) {
            	// acknowledge block
            	//display_string("ACK\r\n");
                uart_putchar(ACK);
            } else {
            	// block # mismatch
            	//display_string("NAK\r\n");
            	uart_putchar(NAK);
            }
        }
    }

    return 0;
}

uint8_t check_magic_number(void) {
	return (*MAGIC_NUMBER_ADDR == MAGIC_NUMBER);
}


uint16_t process_app_crc(uint32_t memsize) {
	uint16_t crc=0;
	for (uint32_t i=16;i<memsize;i++) {
		uint8_t data = *(APP_ADDR + i);
		crc = crc16_update(crc, data);
	}
	return crc;
}

uint8_t check_app(void) {
	if (check_magic_number()) {

		uint32_t memsize = *RAM_SIZE;
		if (memsize>65536) {
			return 2;
		}

		uint32_t appcrc = *APP_CRC;
		//uint32_t appsize = *APP_SIZE;
		uint32_t apptextsize = *APP_TEXT_SIZE;

		if ((uint32_t)process_app_crc(apptextsize) != appcrc) {
			return 3;
		}

	} else {
		return 1;
	}




	return 0;
}

void init_app(uint32_t memsize, uint32_t appsize) {
	// APP_TEXT_SIZE set by app linker

	*RAM_SIZE = memsize;
	//*APP_SIZE = appsize;

	*APP_CRC = (uint32_t)process_app_crc(appsize);
}



uint8_t downloader_run(uint32_t memsize) {
	uint32_t rx_byte = xmodem_receive(APP_ADDR);

	if (rx_byte>0) {
		display_string("\r\nEnd of transfers.\r\n");
		print_bcd(rx_byte);
		display_string(" bytes downloaded\r\n");
		// check Magic Number
		if (check_magic_number()) {
			display_string("Start App\r\n");
			init_app(memsize, rx_byte);
			start_application(JMP_ADDR);
			return 0;	// never go here!
		} else {
			display_string("\r\nWrong Magic Number : 0x");
			display_hex(*MAGIC_NUMBER_ADDR, 8);
			display_string("\r\n");
			return 1;
		}
	} else {
		display_string("\r\nDownload failed!\r\n");
		return 1;
	}
}


//uint32_t get_mem_size(void);

uint8_t launch_app(void) {
	uint8_t error = check_app();
	if (error==0) {
		start_application(JMP_ADDR);
	} else {
		// 1, 2, 3
	}

	return error;
}



