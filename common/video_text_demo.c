#include "bin2bcd.h"
#include "video_text.h"
#include "video_text_demo.h"





const unsigned short QR_CODE_Pattern[QR_CODE_DY][QR_CODE_DX] = {
	{ 0x117, 0xc, 0x113, 0x115, 0xe, 0x9, 0x13, 0x105, 0x3, 0x8, 0x100, 0x117, 0xc, 0x113, 0x115 },
	{ 0x115, 0x10f, 0x105, 0x115, 0x11a, 0x19, 0x16, 0x101, 0x5, 0x10a, 0x100, 0x115, 0x10f, 0x105, 0x115 },
	{ 0x113, 0x113, 0x103, 0xe, 0x109, 0x101, 0x1e, 0x101, 0x111, 0x115, 0x111, 0x1c, 0x103, 0x113, 0x111 },
	{ 0x103, 0x18, 0x11b, 0x11, 0x116, 0x1a, 0x104, 0x10b, 0x105, 0x11d, 0x8, 0x10f, 0x3, 0x106, 0x105 },
	{ 0x12, 0x10e, 0x6, 0xe, 0xf, 0x10e, 0x115, 0x0, 0x10c, 0x1c, 0x1b, 0x0, 0x110, 0x108, 0x115 },
	{ 0x17, 0x109, 0x110, 0x106, 0x1f, 0xa, 0x115, 0x117, 0x119, 0xc, 0x10d, 0x8, 0x100, 0xf, 0x114 },
	{ 0xc, 0x11, 0x10b, 0xc, 0xb, 0x19, 0x1e, 0x113, 0x114, 0x107, 0xb, 0xb, 0x8, 0x1f, 0x101 },
	{ 0x11c, 0x10c, 0x10c, 0x114, 0x10d, 0x12, 0x19, 0x10a, 0x11b, 0xa, 0x115, 0x104, 0x117, 0x1e, 0x105 },
	{ 0x115, 0x0, 0x115, 0x115, 0xf, 0x1a, 0x103, 0x15, 0x115, 0x11e, 0x10, 0x103, 0x11f, 0x19, 0x114 },
	{ 0x10d, 0x10c, 0x10c, 0x105, 0x104, 0x100, 0x105, 0x10c, 0x101, 0x101, 0x105, 0x102, 0x10f, 0x100, 0x104 }
};

void display_qrcode(uint32_t x, uint32_t y) {
    uint8_t color_text = COLOR_WHITE;
    uint8_t color_bgnd = COLOR_BLACK;
    uint32_t *mem_video_ptr;

    for (int iy=0;iy<QR_CODE_DY;iy++) {
        mem_video_ptr = (uint32_t *)VIDEO_TEXT_RAM;
        mem_video_ptr += ((iy+y) * SCREEN_DX + x);
        for (int ix=0;ix<QR_CODE_DX;ix++) {
            *(mem_video_ptr++) = C_TEXT(color_text) | C_BGND(color_bgnd) | QR_CODE_Pattern[iy][ix];
        }
    }
}




const uint32_t LOGO_pico_Pattern[LOGO_PICO_DY][LOGO_PICO_DX] = {
    {
        SET_CHAR(COLOR_YELLOW, COLOR_BLACK, MODE_NORMAL, 21),
        SET_CHAR(COLOR_YELLOW, COLOR_BLACK, MODE_NORMAL, 4),
        SET_CHAR(COLOR_LIME, COLOR_BLACK, MODE_REVERSED, 0),
        SET_CHAR(COLOR_LIME, COLOR_BLACK, MODE_REVERSED, 17),
        SET_CHAR(COLOR_PURPLE, COLOR_BLACK, MODE_NORMAL, 23),
        SET_CHAR(COLOR_PURPLE, COLOR_BLACK, MODE_REVERSED, 3),
        SET_CHAR(COLOR_GRAY, COLOR_BLACK, MODE_REVERSED, 0),
        SET_CHAR(COLOR_FUCHSIA, COLOR_BLACK, MODE_REVERSED, 22),
        SET_CHAR(COLOR_FUCHSIA, COLOR_BLACK, MODE_NORMAL, 22),
    }, {
        SET_CHAR(COLOR_YELLOW, COLOR_BLACK, MODE_REVERSED, 10),
        SET_CHAR(COLOR_YELLOW, COLOR_BLACK, MODE_REVERSED, 0),
        SET_CHAR(COLOR_LIME, COLOR_BLACK, MODE_REVERSED, 0),
        SET_CHAR(COLOR_LIME, COLOR_BLACK, MODE_REVERSED, 5),
        SET_CHAR(COLOR_PURPLE, COLOR_BLACK, MODE_REVERSED, 2),
        SET_CHAR(COLOR_PURPLE, COLOR_BLACK, MODE_REVERSED, 12),
        SET_CHAR(COLOR_GRAY, COLOR_BLACK, MODE_REVERSED, 0),
        SET_CHAR(COLOR_FUCHSIA, COLOR_BLACK, MODE_REVERSED, 9),
        SET_CHAR(COLOR_FUCHSIA, COLOR_BLACK, MODE_REVERSED, 6)
    }
};




const uint32_t LOGO_RV32_Pattern[LOGO_RV32_DY][LOGO_RV32_DX] = {
    {
        SET_CHAR(COLOR_GRAY, COLOR_BLACK, MODE_NORMAL, 21),     //
        SET_CHAR(COLOR_SILVER, COLOR_GRAY, MODE_REVERSED, 28),
        SET_CHAR(COLOR_SILVER, COLOR_GRAY, MODE_REVERSED, 12),
        SET_CHAR(COLOR_SILVER, COLOR_GRAY, MODE_REVERSED, 16),
        SET_CHAR(COLOR_SILVER, COLOR_GRAY, MODE_REVERSED, 20),
        SET_CHAR(COLOR_SILVER, COLOR_GRAY, MODE_REVERSED, 0),
        SET_CHAR(COLOR_PURPLE, COLOR_GRAY, MODE_REVERSED, 0),
        SET_CHAR(COLOR_SILVER, COLOR_GRAY, MODE_REVERSED, 20),
        SET_CHAR(COLOR_BLUE, COLOR_GRAY, MODE_REVERSED, 12),
        SET_CHAR(COLOR_BLUE, COLOR_GRAY, MODE_NORMAL, 27),
        SET_CHAR(COLOR_BLUE, COLOR_GRAY, MODE_REVERSED, 8),
        SET_CHAR(COLOR_BLUE, COLOR_GRAY, MODE_REVERSED, 12),
        SET_CHAR(COLOR_BLUE, COLOR_GRAY, MODE_REVERSED, 16)
    }, {
        SET_CHAR(COLOR_GRAY, COLOR_BLACK, MODE_NORMAL, 21),     //
        SET_CHAR(COLOR_SILVER, COLOR_GRAY, MODE_REVERSED, 29),
        SET_CHAR(COLOR_SILVER, COLOR_GRAY, MODE_NORMAL, 19),
        SET_CHAR(COLOR_SILVER, COLOR_GRAY, MODE_REVERSED, 1),
        SET_CHAR(COLOR_SILVER, COLOR_GRAY, MODE_REVERSED, 10),
        SET_CHAR(COLOR_SILVER, COLOR_GRAY, MODE_REVERSED, 16),
        SET_CHAR(COLOR_SILVER, COLOR_GRAY, MODE_REVERSED, 26),
        SET_CHAR(COLOR_SILVER, COLOR_GRAY, MODE_REVERSED, 0),
        SET_CHAR(COLOR_BLUE, COLOR_GRAY, MODE_REVERSED, 8),
        SET_CHAR(COLOR_BLUE, COLOR_GRAY, MODE_NORMAL, 25),
        SET_CHAR(COLOR_BLUE, COLOR_GRAY, MODE_NORMAL, 31),
        SET_CHAR(COLOR_BLUE, COLOR_GRAY, MODE_REVERSED, 12),
        SET_CHAR(COLOR_BLUE, COLOR_GRAY, MODE_REVERSED, 1)
    }, {
        SET_CHAR(COLOR_GRAY, COLOR_BLACK, MODE_NORMAL, 21),     //
        SET_CHAR(COLOR_SILVER, COLOR_GRAY, MODE_REVERSED, 5),
        SET_CHAR(COLOR_SILVER, COLOR_GRAY, MODE_REVERSED, 0),
        SET_CHAR(COLOR_SILVER, COLOR_GRAY, MODE_REVERSED, 9),
        SET_CHAR(COLOR_SILVER, COLOR_GRAY, MODE_REVERSED, 0),
        SET_CHAR(COLOR_SILVER, COLOR_GRAY, MODE_REVERSED, 13-4),
        SET_CHAR(COLOR_SILVER, COLOR_GRAY, MODE_REVERSED, 5-4),
        SET_CHAR(COLOR_SILVER, COLOR_GRAY, MODE_REVERSED, 0),
        SET_CHAR(COLOR_BLUE, COLOR_GRAY, MODE_REVERSED, 12),
        SET_CHAR(COLOR_BLUE, COLOR_GRAY, MODE_REVERSED, 6),
        SET_CHAR(COLOR_BLUE, COLOR_GRAY, MODE_REVERSED, 10),
        SET_CHAR(COLOR_BLUE, COLOR_GRAY, MODE_REVERSED, 12),
        SET_CHAR(COLOR_BLUE, COLOR_GRAY, MODE_REVERSED, 4)
    }
};

void display_pico_logo(uint32_t x, uint32_t y) {
    display_pattern(x, y, LOGO_PICO_DX, LOGO_PICO_DY, &LOGO_pico_Pattern[0][0]);
}


void display_RV32_logo(uint32_t x, uint32_t y) {
    display_pattern(x, y, LOGO_RV32_DX, LOGO_RV32_DY, &LOGO_RV32_Pattern[0][0]);
}





void test_video_text(void) {
    unsigned int i, line;

    clear_video_memory();

    uint8_t x = (SCREEN_DX - (LOGO_PICO_DX + LOGO_RV32_DX)) >> 1;
    display_pico_logo(x+0, 0+1);
    display_RV32_logo(x+10, 0);

    display_qrcode(SCREEN_DX - QR_CODE_DX, SCREEN_DY - QR_CODE_DY -1);

    line = 3;
    display_set_text_color(COLOR_WHITE);
    display_string_xy(0, line, "Video Text module for ");
    display_picoRV32(22, line);
    display_cursor_move(22+8, line);

    line = 5;
    display_set_text_color(COLOR_WHITE);
    display_string_xy(0, line, 
            "       This demonstration showcases a text-mode HDMI video display solution driven by a PicoRV32"
            "  softcore processor. The design is characterized by its efficiency: it requires no external RAM"
            "  and utilizes only 10 internal BSRAMs.");
    line += 4;
    display_set_text_color(COLOR_SILVER);
    display_string_xy(5, line++, "* Resolution             : ");
    print_bcd(SCREEN_DX * 16);
    display_string_xy(5, line++, " x ");
    print_bcd(SCREEN_DY * 24);
    display_string_xy(5, line++, " pixels.");
    display_string_xy(5, line++, "* Refresh Rate           : ");
    print_bcd(SCREEN_REFRESH);
    display_string_xy(5, line++, " Hz.");
    display_string_xy(5, line++, "* Display                : ");
    print_bcd(SCREEN_DX);
    display_string_xy(5, line++, " x ");
    print_bcd(SCREEN_DY);
    display_string_xy(5, line++, " characters in 16 colors.");
    display_string_xy(5, line++, "* Characters Resolution  : 16 x 24 pixels.");
    line++;
    display_set_text_color(COLOR_WHITE);
    display_string_xy(10, line++, "16-color palette        ");
    for (i=0;i<16;i++) {
        *(VIDEO_TEXT_RAM+cursor_pos++) = SET_CHAR((i==7)?COLOR_BLACK:COLOR_SILVER, i , 5, 32);
    }
    line++;
    display_set_text_color(COLOR_WHITE);
    display_string_xy(0, line++, "The controller handles visual effects natively to save CPU cycles:");
    line++;
    display_set_text_color(COLOR_SILVER);
    display_string_xy(5, line++, "* Auto-Blink : Character or background can flash at a fixed hardware frequency.");    
    display_string_xy(5, line++, "* Color Swap : Instant inversion of foreground and background.");
    display_string_xy(5, line++, "* Underline  : Hardware-rendered underline per character.");
    line++;
    display_set_text_color(COLOR_GRAY);
	display_string_xy(10, line++, "Normal             ");
	*(VIDEO_TEXT_RAM+cursor_pos) = SET_CHAR(COLOR_WHITE, COLOR_BLACK, 0, '0');
	display_string_xy(10, line++, "Reversed           ");
	*(VIDEO_TEXT_RAM+cursor_pos) = SET_CHAR(COLOR_WHITE, COLOR_BLACK, 1, '1');
	display_string_xy(10, line++, "Underline          ");
	*(VIDEO_TEXT_RAM+cursor_pos) = SET_CHAR(COLOR_WHITE, COLOR_BLACK, 2, '2');
	display_string_xy(10, line++, "Underline Reversed ");
	*(VIDEO_TEXT_RAM+cursor_pos) = SET_CHAR(COLOR_WHITE, COLOR_BLACK, 3, '3');
	display_string_xy(10, line++, "Blinked            ");
	*(VIDEO_TEXT_RAM+cursor_pos) = SET_CHAR(COLOR_WHITE, COLOR_BLACK, 4, '4');
	display_string_xy(10, line++, "Cursor             ");
	*(VIDEO_TEXT_RAM+cursor_pos) = SET_CHAR(COLOR_WHITE, COLOR_BLACK, 5, '5');
	display_string_xy(10, line++, "Blinked Underline  ");
	*(VIDEO_TEXT_RAM+cursor_pos) = SET_CHAR(COLOR_WHITE, COLOR_BLACK, 6, '6');
	display_string_xy(10, line++, "Reversed Cursor    ");
	*(VIDEO_TEXT_RAM+cursor_pos) = SET_CHAR(COLOR_WHITE, COLOR_BLACK, 7, '7');



    display_set_text_color(COLOR_YELLOW);
    display_set_bgnd_color(COLOR_MAROON);
    for (i=0;i<96;i++) {
        display_char_x_y(i, 40, 0x20 + i);
    }
    display_set_mode(MODE_REVERSED);
    for (i=0;i<96;i++) {
        display_char_x_y(i, 41, 0x20 + 95 - i);
    }

}


//__attribute__((optimize("no-tree-loop-distribute-patterns")))
void scroll_line(uint8_t line) {
    uint32_t *mem_video_ptr = (uint32_t *)VIDEO_TEXT_RAM + line*SCREEN_DX;
    uint32_t tmp, i;

    tmp = *(mem_video_ptr+0);  
    for (i=0;i<SCREEN_DX-1;i++) {
        *(mem_video_ptr+i) = *(mem_video_ptr+i+1);
    }
    *(mem_video_ptr+SCREEN_DX-1) = tmp;
}
