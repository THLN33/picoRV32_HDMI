/*
 * ansi.c
 *
 *  Created on: 25 févr. 2026
 *      Author: thierry
 */

#include "video_text.h"


static unsigned char term_x = 0;
static unsigned char term_y = 0;
static unsigned char term_fg = COLOR_SILVER;
static unsigned char term_bg = COLOR_BLACK;
static unsigned char term_mode = MODE_NORMAL;

#define MAX_ANSI_PARAMS 5

typedef enum {
    STATE_NORMAL,
    STATE_ESC,
    STATE_CSI
} ansi_state_t;

static ansi_state_t current_state = STATE_NORMAL;
static int params[MAX_ANSI_PARAMS];
static int param_idx = 0;


static void check_scroll(void) {
    if (term_y >= SCREEN_DY) {
        display_scroll_up();
        term_y = SCREEN_DY - 1;
        // Optionnel : effacer la nouvelle ligne vide en bas
        // clear_line(term_y, 0);
    }
}


void term_write_char(char c) {
    switch (current_state) {

        case STATE_NORMAL:
            if (c == 0x1B) { // Code ASCII pour ESC
                current_state = STATE_ESC;
            } else if (c == '\n') {
                term_x = 0;
                term_y++;
                check_scroll();
            } else if (c == '\r') {
                term_x = 0;
            } else if (c >= 32) { // Caractères imprimables
                display_char_x_y(term_x, term_y, c);
                term_x++;
                if (term_x >= SCREEN_DX) {
                    term_x = 0;
                    term_y++;
                    check_scroll();
                }
            }
            display_set_cursor_position_x_y(term_x, term_y);
            break;

        case STATE_ESC:
            if (c == '[') {
                current_state = STATE_CSI;
                // Réinitialisation des paramètres pour la nouvelle séquence
                for (int i = 0; i < MAX_ANSI_PARAMS; i++) params[i] = 0;
                param_idx = 0;
            } else {
                // Si ce n'est pas un '[', ce n'est pas une séquence CSI, on abandonne
                current_state = STATE_NORMAL;
            }
            break;

        case STATE_CSI:
            if (c >= '0' && c <= '9') {
                // Accumulation du nombre (ex: "31")
                params[param_idx] = params[param_idx] * 10 + (c - '0');
            } else if (c == ';') {
                // Séparateur de paramètres, on passe au suivant
                if (param_idx < MAX_ANSI_PARAMS - 1) {
                    param_idx++;
                }
            } else {
                // C'est une lettre (m, H, J, etc.) : fin de la séquence
                handle_ansi_command(c);
                current_state = STATE_NORMAL;
                display_set_cursor_position_x_y(term_x, term_y);
            }
            break;
    }
}

void term_print_char(char c) {

    if (current_state == STATE_NORMAL) {
        if (c == '\n') {
            term_x = 0;
            term_y++;
        } else if (c == '\r') {
            term_x = 0;
        } else if (c >= 32) {
            display_char_x_y(term_x, term_y, c);
            term_x++;
            if (term_x >= SCREEN_DX) {
                term_x = 0;
                term_y++;
            }
        }

        if (term_y >= SCREEN_DY) {
            display_scroll_up();
            term_y = SCREEN_DY - 1;
        }

        display_set_cursor_position_x_y(term_x, term_y);
    }
}


void handle_ansi_command(char cmd) {
    switch (cmd) {
        case 'm': // Couleurs et Modes
            for (int i = 0; i <= param_idx; i++) {
                int p = params[i];
                if (p == 0) { // Reset
                    term_fg = COLOR_SILVER; term_bg = COLOR_BLACK; term_mode = MODE_NORMAL;
                    display_set_text_color(term_fg);
                    display_set_bgnd_color(term_bg);
                    display_set_mode(term_mode);
                }
                else if (p >= 30 && p <= 37) { term_fg = (p - 30); display_set_text_color(term_fg); }
                else if (p >= 90 && p <= 97) { term_fg = (p - 90 + 8); display_set_text_color(term_fg); }
                else if (p >= 40 && p <= 47) { term_bg = (p - 40); display_set_bgnd_color(term_bg); }
                else if (p >= 100 && p <= 107) { term_bg = (p - 100 + 8); display_set_bgnd_color(term_bg); }
                else if (p == 4) { term_mode = MODE_UNDERLINE; display_set_mode(term_mode); }
                else if (p == 7) { term_mode = MODE_REVERSED; display_set_mode(term_mode); }
            }
            break;

        case 'H': // Positionnement : ESC[line;colH
        case 'f':
            term_y = (params[0] > 0) ? params[0] - 1 : 0;
            term_x = (param_idx >= 1 && params[1] > 0) ? params[1] - 1 : 0;
            display_set_cursor_position_x_y(term_x, term_y);
            break;

        case 'J': // Effacement écran : ESC[2J
            if (params[0] == 2) {
                clear_video_memory();
                term_x = 0; term_y = 0;
                display_set_cursor_position_x_y(0, 0);
            }
            break;
    }
}



void ansi_demo(void) {
	display_string("Normal ");
	display_string("\x1B[31mRouge "); // 31 = Red
	display_string("\x1B[32mVert ");  // 32 = Green
	display_string("\x1B[0mRetour au Gris"); // 0 = Reset
}

