#include <stdint.h>
#include <stdbool.h>

#include "uart.h"

#define PRINT(s)

#define PRINT_HEX(c)

static const uint32_t test_vals[] = {
	0x000000ff, 
	0x0000ff00,
	0x00ff0000, 
	0xff000000,
	0xffffffff,
	0xaaaaaaaa, 
	0x55555555, 
	0xdeadbeef};

#define SRAM_EXT_START_ADDRESS	(0x20000000)

#define SRAM_EXT_MEMADDR		((uint32_t *)SRAM_EXT_START_ADDRESS)
#define SRAM_EXT_MAX_SIZE    	((64 * 1024) / sizeof(uint32_t)) // 32bit access



#define TEST_NB (sizeof(test_vals)/sizeof(uint32_t))


uint32_t get_mem_size(void) {

	uint32_t *mem64_ptr = SRAM_EXT_MEMADDR;
	uint32_t adr_offset;
	uint32_t val_read;
	unsigned char bank;


	for (int bank = 0;bank < 8; bank++) {
		adr_offset = (8192>>2) * bank;
		*(mem64_ptr + adr_offset) = 0x55AA6699 ^ adr_offset;
	}

	for (bank = 0;bank < 8; bank++) {
		adr_offset = (8192>>2) * bank;
		val_read = *(mem64_ptr + adr_offset);
		if ( val_read !=  (0x55AA6699 ^ adr_offset) ) {
			break;
		}
	}

	return bank * 8192;
}


int mem_test_sram_dword(unsigned int memsize) {
    unsigned int test, errors=0;
    unsigned int adr_offset;
    unsigned int val_read;    
    unsigned int *mem64_ptr = SRAM_EXT_MEMADDR;
	unsigned int mem_step = 1<<2;	// 32bit access
	memsize >>= 2;					// 32bit access
    for (test = 0; test < TEST_NB; test++) {
        //uart_puts("Write");
        adr_offset=0;
		while (adr_offset<=memsize-mem_step) {
			*(mem64_ptr + adr_offset) = test_vals[test];
			adr_offset+=mem_step;
        }

        PRINT("W");

        //uart_puts("\r\n");  
        //uart_puts("Read & Verify"); 

		adr_offset=0;
		while (adr_offset<=memsize-mem_step) {
            val_read = *(mem64_ptr + adr_offset);
            if (val_read != test_vals[test]) {
                errors += 1;  
                PRINT("Failed at [0x");
                PRINT_HEX(SRAM_EXT_START_ADDRESS + adr_offset);
                PRINT("] = 0x");
                PRINT_HEX(val_read);
				PRINT("\r\n");
                break;
            }
			adr_offset+=mem_step;
		}
		PRINT("R");
    }
    PRINT("\r\n");

    return(errors);
}


