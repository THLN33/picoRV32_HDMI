/*
 * video_text.h
 *
 *  Created on: 25 févr. 2026
 *      Author: thierry
 */

#ifndef VIDEO_TEXT_H_
#define VIDEO_TEXT_H_

#include "system_config.h"

#define VIDEO_TEXT_BASE			0x30000000

#define VIDEO_TEXT_RAM			((volatile uint32_t *)VIDEO_TEXT_BASE)


#define COLOR_BLACK 	0
#define COLOR_MAROON 	1
#define COLOR_GREEN 	2
#define COLOR_OLIVE 	3
#define COLOR_NAVY 		4
#define COLOR_PURPLE 	5
#define COLOR_TEAL 		6
#define COLOR_SILVER 	7
#define COLOR_GRAY 		8
#define COLOR_RED 		9
#define COLOR_LIME 		10
#define COLOR_YELLOW 	11
#define COLOR_BLUE 		12
#define COLOR_FUCHSIA 	13
#define COLOR_AQUA 		14
#define COLOR_WHITE 	15

/*
#define BLACK 	0x00000000
#define MAROON 	0x00800000
#define GREEN 	0x00008000
#define OLIVE 	0x00808000
#define NAVY 	0x00000080
#define PURPLE 	0x00800080
#define TEAL 	0x00008080
#define SILVER 	0x00C0C0C0
#define GRAY 	0x00808080
#define RED 	0x00FF0000
#define LIME 	0x0000FF00
#define YELLOW 	0x00FFFF00
#define BLUE 	0x000000FF
#define FUCHSIA 0x00FF00FF
#define AQUA 	0x0000FFFF
#define WHITE 	0x00FFFFFF
*/

#define C_TEXT(c)       ((c)<<24)
#define C_BGND(c)       ((c)<<16)
#define MODE(m)         ((m)<<8)

#define SET_CHAR(c_text, c_bbnd, mode, c) ( C_TEXT(c_text) | C_BGND(c_bbnd) | MODE(mode) | (unsigned char)(c) )

#ifdef _TWO_SPEED_
#define MODE_NORMAL         0
#define MODE_REVERSED       1
#define MODE_UNDERLINE      2
#define MODE_BLINK_SPEED0   4
#define MODE_BLINK_SPEED1   5
#else
#define MODE_NORMAL             0
#define MODE_REVERSED           1
#define MODE_UNDERLINE          2
#define MODE_REVERSED_UNDERLINE 3

#define MODE_BLINK              4
#define MODE_CURSOR             5
#define MODE_BLINK_CURSOR       6
#define MODE_REVERSED_CURSOR    7
#endif



extern uint16_t cursor_pos;

void clear_video_memory(void);
void display_clear(void);
void display_scroll_up(void);

void display_cursor_off(void);
void display_cursor_on(void);
void display_set_cursor_position_x_y(uint16_t x, uint16_t y);
void display_cursor_move(uint16_t x, uint16_t y);

void display_set_text_color(uint8_t color);
void display_set_bgnd_color(uint8_t color);
void display_set_mode(uint8_t mode);

void display_set_char_position_x_y(uint16_t x, uint16_t y);
void display_char(char c);
void display_color_char(uint8_t color_text, uint8_t color_bgnd, char c);
void display_char_x_y(uint16_t x, uint16_t y, char c);
void display_color_char_x_y(uint16_t x, uint16_t y,
			uint8_t color_text,
			uint8_t color_bgnd,
            char c);
void display_set_color_x_y(uint16_t x, uint16_t y,
				uint8_t color_text,
				uint8_t color_bgnd);
void display_set_mode_x_y(uint16_t x, uint16_t y,
			uint8_t mode);
void display_string(char *str);
void display_string_xy(uint16_t x, uint16_t y, char *str);
void display_hex(uint32_t val, uint8_t n);

void display_pattern(uint32_t x, uint32_t y, uint32_t dx, uint32_t dy, const uint32_t *pattern);

void display_picoRV32(uint32_t x, uint32_t y);

#endif /* VIDEO_TEXT_H_ */
