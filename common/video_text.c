/*
 * video_text.c
 *
 *  Created on: 25 févr. 2026
 *      Author: thierry
 */
#include <stdint.h>

#include "video_text.h"

#define WRITE_VIDEO_TEXT(addr_offset, val) \
	*(VIDEO_TEXT_RAM + ((addr_offset) & 0x0FFF)) = val

#define READ_VIDEO_TEXT(addr_offset) \
	*(VIDEO_TEXT_RAM + ((addr_offset) & 0x0FFF))





//static
uint16_t cursor_pos = 0;

static uint8_t c_text = COLOR_WHITE;
static uint8_t c_bgnd = COLOR_BLACK;
static uint8_t c_mode = MODE_NORMAL;


void clear_video_memory(void) {
	uint32_t addr_offset;
    cursor_pos = 0;
    c_text = COLOR_WHITE;
    c_bgnd = COLOR_BLACK;
    c_mode = MODE_NORMAL;

    for (addr_offset=0;addr_offset<SCREEN_DX*SCREEN_DY;addr_offset++) {
    	WRITE_VIDEO_TEXT(addr_offset, SET_CHAR(c_text, c_bgnd, MODE_NORMAL, ' '));
    }
}

void display_clear_line(uint16_t y) {
	uint32_t addr_offset;

    for (addr_offset=0;addr_offset<SCREEN_DX;addr_offset++) {
    	WRITE_VIDEO_TEXT(y*SCREEN_DX + addr_offset, SET_CHAR(c_text, c_bgnd, MODE_NORMAL, ' '));
    }
}

void display_clear(void) {
	clear_video_memory();
}

//__attribute__((optimize("no-tree-loop-distribute-patterns")))
void display_scroll_up(void) {
    uint32_t end = SCREEN_DX*(SCREEN_DY-1);
    for (uint32_t i=0;i<end;i++) {
    	WRITE_VIDEO_TEXT(i, READ_VIDEO_TEXT(SCREEN_DX+i));
    }
    for (uint32_t i=0;i<SCREEN_DX;i++) {
    	WRITE_VIDEO_TEXT((SCREEN_DY-1)*SCREEN_DX + i, SET_CHAR(c_text, c_bgnd, MODE_NORMAL, ' '));
    }
}


void display_cursor_off(void) {
	//WRITE_VIDEO_TEXT(cursor_pos, READ_VIDEO_TEXT(cursor_pos) & ~(7<<8) )
    *(VIDEO_TEXT_RAM + (cursor_pos & 0x0FFF)) &= ~(7<<8);
}

void display_cursor_on(void) {
    *(VIDEO_TEXT_RAM + (cursor_pos & 0x0FFF)) |= C_TEXT(COLOR_WHITE) | C_BGND(COLOR_BLACK) | MODE(MODE_CURSOR);
}

void display_set_cursor_position_x_y(uint16_t x, uint16_t y) {
    cursor_pos = (y * SCREEN_DX + x); // & 0x0FFF;
}

void display_cursor_move(uint16_t x, uint16_t y) {
    display_cursor_off();
    display_set_cursor_position_x_y(x, y);
    display_cursor_on();
}


void display_set_text_color(uint8_t color) {
    c_text = color;
}

void display_set_bgnd_color(uint8_t color) {
    c_bgnd = color;
}

void display_set_mode(uint8_t mode) {
    c_mode = mode;
}



void display_char(char c) {
	if (cursor_pos>=SCREEN_DY*SCREEN_DX) {
		display_scroll_up();
		cursor_pos -= SCREEN_DX;
	}
	WRITE_VIDEO_TEXT(cursor_pos++,  SET_CHAR(c_text, c_bgnd, c_mode, c));
}


void display_char_x_y(uint16_t x, uint16_t y, char c) {
	display_set_cursor_position_x_y(x, y);
    display_char(c);
}


void display_set_mode_x_y(uint16_t x, uint16_t y, uint8_t mode) {
    unsigned int tmp;
    display_set_cursor_position_x_y(x, y);

    tmp = READ_VIDEO_TEXT(cursor_pos) & ~(7 << 8);
    tmp |= mode<<8;
    WRITE_VIDEO_TEXT(cursor_pos, tmp);
}



void display_string(char *str) {
	uint8_t x, y;
	char ch;
    while(*str) {
    	ch = *str++;
    	if (ch<32) {
        	switch (ch) {
        		case '\n':
        			x = cursor_pos % SCREEN_DX;
        			y = cursor_pos / SCREEN_DX;

        			if (y==SCREEN_DY-1) {
        				display_scroll_up();

        			} else {
        				y++;
        			}

        			cursor_pos = (y * SCREEN_DX + x);
        			break;
        		case '\r':
        			y = cursor_pos / SCREEN_DX;
        			cursor_pos = (y * SCREEN_DX + 0);
        			break;
        		case '\t':
        			break;

        		default:
        	}
    	} else {
    		 display_char(ch);
    	}
    }
}

void display_string_xy(uint16_t x, uint16_t y, char *str) {

	display_set_cursor_position_x_y(x, y);
    display_string(str);
}


void display_hex(uint32_t val, uint8_t n) {
    unsigned int msk, sft;
	unsigned char ch;
    int i;

    sft = ((n-1)*4);
    msk = 0xf<<sft;
    for (i = 0; i < n; i++) {
        ch = (val & msk) >> sft;
        display_char( "0123456789ABCDEF"[ch] );
        val = val << 4;
    }
}


void display_pattern(uint32_t x, uint32_t y, uint32_t dx, uint32_t dy, const uint32_t *pattern) {
    uint32_t *mem_video_ptr = (uint32_t *)VIDEO_TEXT_RAM;

    mem_video_ptr += (y * SCREEN_DX + x) & 0x0FFF;
    for (y=0;y<dy;y++) {
        for (x=0;x<dx;x++) {
            *(mem_video_ptr++) = *pattern++;
        }
        mem_video_ptr += SCREEN_DX - dx;
    }
}




void display_picoRV32(uint32_t x, uint32_t y) {

	display_set_cursor_position_x_y(x, y);

    WRITE_VIDEO_TEXT(cursor_pos++, SET_CHAR(COLOR_YELLOW, COLOR_BLACK, MODE_NORMAL, 'p'));
    WRITE_VIDEO_TEXT(cursor_pos++, SET_CHAR(COLOR_LIME, COLOR_BLACK, MODE_NORMAL, 'i'));
    WRITE_VIDEO_TEXT(cursor_pos++, SET_CHAR(COLOR_PURPLE, COLOR_BLACK, MODE_NORMAL, 'c'));
    WRITE_VIDEO_TEXT(cursor_pos++, SET_CHAR(COLOR_FUCHSIA, COLOR_BLACK, MODE_NORMAL, 'o'));
    WRITE_VIDEO_TEXT(cursor_pos++, SET_CHAR(COLOR_SILVER, COLOR_GRAY, MODE_NORMAL, 'R'));
    WRITE_VIDEO_TEXT(cursor_pos++, SET_CHAR(COLOR_SILVER, COLOR_GRAY, MODE_NORMAL, 'V'));
    WRITE_VIDEO_TEXT(cursor_pos++, SET_CHAR(COLOR_BLUE, COLOR_GRAY, MODE_NORMAL, '3'));
    WRITE_VIDEO_TEXT(cursor_pos++, SET_CHAR(COLOR_BLUE, COLOR_GRAY, MODE_NORMAL, '2'));
}
