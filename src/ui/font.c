#include "ui/font.h"
#include <avr/pgmspace.h>

const uint8_t numbers_32px[][80] PROGMEM = {
    { 0xF8, 0xF0, 0xE2, 0xC6, 0x0E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x0E, 0xC6, 0xE2, 0xF0, 0xF8, 0x3F, 0x3F, 0x1F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x1F, 0x3F, 0x3F, 0xFF, 0xFF, 0xFE, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xFE, 0xFF, 0xFF, 0x1F, 0x0F, 0x47, 0x63, 0x70, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x70, 0x63, 0x47, 0x0F, 0x1F },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x1F, 0x3F, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xFE, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x0F, 0x1F },
    { 0x00, 0x00, 0x02, 0x06, 0x0E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x0E, 0xC6, 0xE2, 0xF0, 0xF8, 0x00, 0x00, 0x00, 0xC0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xCF, 0x1F, 0x3F, 0x3F, 0xFF, 0xFF, 0xFE, 0xFC, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x0F, 0x47, 0x63, 0x70, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x70, 0x60, 0x40, 0x00, 0x00 },
    { 0x00, 0x00, 0x02, 0x06, 0x0E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x0E, 0xC6, 0xE2, 0xF0, 0xF8, 0x00, 0x00, 0x00, 0xC0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xCF, 0x1F, 0x3F, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xFC, 0xFE, 0xFF, 0xFF, 0x00, 0x00, 0x40, 0x60, 0x70, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x70, 0x63, 0x47, 0x0F, 0x1F },
    { 0xF8, 0xF0, 0xE0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0x3F, 0x3F, 0x1F, 0xCF, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xCF, 0x1F, 0x3F, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xFC, 0xFE, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x0F, 0x1F },
    { 0xF8, 0xF0, 0xE2, 0xC6, 0x0E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x0E, 0x06, 0x02, 0x00, 0x00, 0x3F, 0x3F, 0x1F, 0xCF, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xFC, 0xFE, 0xFF, 0xFF, 0x00, 0x00, 0x40, 0x60, 0x70, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x70, 0x63, 0x47, 0x0F, 0x1F },
    { 0xF8, 0xF0, 0xE2, 0xC6, 0x0E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x0E, 0x06, 0x02, 0x00, 0x00, 0x3F, 0x3F, 0x1F, 0xCF, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFE, 0xFC, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xFC, 0xFE, 0xFF, 0xFF, 0x1F, 0x0F, 0x47, 0x63, 0x70, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x70, 0x63, 0x47, 0x0F, 0x1F },
    { 0x00, 0x00, 0x02, 0x06, 0x0E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x0E, 0xC6, 0xE2, 0xF0, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x1F, 0x3F, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xFE, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x0F, 0x1F },
    { 0xF8, 0xF0, 0xE2, 0xC6, 0x0E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x0E, 0xC6, 0xE2, 0xF0, 0xF8, 0x3F, 0x3F, 0x1F, 0xCF, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xCF, 0x1F, 0x3F, 0x3F, 0xFF, 0xFF, 0xFE, 0xFC, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xFC, 0xFE, 0xFF, 0xFF, 0x1F, 0x0F, 0x47, 0x63, 0x70, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x70, 0x63, 0x47, 0x0F, 0x1F },
    { 0xF8, 0xF0, 0xE2, 0xC6, 0x0E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x0E, 0xC6, 0xE2, 0xF0, 0xF8, 0x3F, 0x3F, 0x1F, 0xCF, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xCF, 0x1F, 0x3F, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xFC, 0xFE, 0xFF, 0xFF, 0x00, 0x00, 0x40, 0x60, 0x70, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x70, 0x63, 0x47, 0x0F, 0x1F }
};

const uint8_t timer_dot[10] = { 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0x03, 0x03, 0x03, 0x03, 0x03 };

/* Numbers 6x8 */

const uint8_t number_0_6x8[6] = { 0x7E, 0xFF, 0xC3, 0xC3, 0xFF, 0x7E };
const uint8_t number_1_6x8[6] = { 0x06, 0x06, 0xFF, 0xFF, 0x00, 0x00 };
const uint8_t number_2_6x8[6] = { 0xE3, 0xF3, 0xFB, 0xDF, 0xCF, 0xC7 };
const uint8_t number_3_6x8[6] = { 0xC3, 0xC3, 0xDB, 0xDB, 0xFF, 0xFF };
const uint8_t number_4_6x8[6] = { 0x3F, 0x3F, 0x30, 0x30, 0xFF, 0xFF };
const uint8_t number_5_6x8[6] = { 0xDF, 0xDF, 0xDB, 0xDB, 0xFB, 0x73 };
const uint8_t number_6_6x8[6] = { 0xFF, 0xFF, 0xDB, 0xDB, 0xFB, 0xF3 };
const uint8_t number_7_6x8[6] = { 0x03, 0x03, 0x03, 0x03, 0xFF, 0xFF };
const uint8_t number_8_6x8[6] = { 0x7E, 0xFF, 0xDB, 0xDB, 0xFF, 0x7E };
const uint8_t number_9_6x8[6] = { 0x0E, 0x1F, 0x1B, 0x1B, 0xFF, 0xFF };

const uint8_t* numbers_8px[] = {
    [0] = number_0_6x8,
    [1] = number_1_6x8,
    [2] = number_2_6x8,
    [3] = number_3_6x8,
    [4] = number_4_6x8,
    [5] = number_5_6x8,
    [6] = number_6_6x8,
    [7] = number_7_6x8,
    [8] = number_8_6x8,
    [9] = number_9_6x8
};

/* Letters 8 pixel height */

const uint8_t graphic_A_6x8[6] = { 0xFE, 0xFF, 0x33, 0x33, 0xFF, 0xFE };
const uint8_t graphic_E_5x8[5] = { 0xFF, 0xFF, 0xDB, 0xDB, 0xC3 };
const uint8_t graphic_I_2x8[2] = { 0xFF, 0xFF };
const uint8_t graphic_K_5x8[5] = { 0xFF, 0xFF, 0x18, 0xFF, 0xE7 };
const uint8_t graphic_M_8x8[8] = { 0xFF, 0xFF, 0x07, 0x0E, 0x0E, 0x07, 0xFF, 0xFF };
const uint8_t graphic_O_6x8[6] = { 0x7E, 0xFF, 0xC3, 0xC3, 0xFF, 0x7E };
const uint8_t graphic_P_5x8[5] = { 0xFF, 0xFF, 0x33, 0x3F, 0x1E };
const uint8_t graphic_R_5x8[5] = { 0xFF, 0xFF, 0x33, 0xFF, 0xDE };
const uint8_t graphic_S_6x8[6] = { 0xCE, 0xDF, 0xDB, 0xFB, 0xFB, 0x73 };
const uint8_t graphic_T_6x8[6] = { 0x03, 0x03, 0xFF, 0xFF, 0x03, 0x03 };
const uint8_t graphic_U_6x8[6] = { 0x7F, 0xFF, 0xC0, 0xC0, 0xFF, 0x7F };
const uint8_t graphic_W_7x8[7] = { 0xFF, 0xFF, 0x60, 0x78, 0x60, 0xFF, 0xFF };

const uint8_t* letters_8px[] = {
    [0] = graphic_A_6x8,
    [1] = graphic_E_5x8,
    [2] = graphic_I_2x8,
    [3] = graphic_K_5x8,
    [4] = graphic_M_8x8,
    [5] = graphic_O_6x8,
    [6] = graphic_P_5x8,
    [7] = graphic_R_5x8,
    [8] = graphic_S_6x8,
    [9] = graphic_T_6x8,
    [10] = graphic_U_6x8,
    [11] = graphic_W_7x8,
};

/* Words */

const graphic_t repeat_8px = {
    { 7, 1, 6, 1, 0, 9, 0, 0 },
    { 5, 5, 5, 5, 6, 6, 0, 0 },
    7,
    letters_8px
};

const graphic_t pause_8px = {
    { 6, 0, 10, 8, 1, 0, 0, 0 },
    { 5, 6, 6, 6, 5, 0, 0, 0 },
    5,
    letters_8px
};

const graphic_t work_8px = {
    { 11, 5, 7, 3, 0, 0, 0, 0 },
    { 7, 6, 5, 5, 0, 0, 0, 0 },
    4,
    letters_8px
};

const graphic_t timer_8px = {
    { 9, 2, 4, 1, 7, 0, 0, 0 },
    { 6, 2, 8, 5, 5, 0, 0, 0 },
    5,
    letters_8px
};

const graphic_t start_8px = {
    { 8, 9, 0, 7, 9, 0, 0, 0 },
    { 6, 6, 6, 5, 6, 0, 0, 0 },
    5,
    letters_8px
};

const graphic_t set_8px = {
    { 8, 1, 9, 0, 0, 0, 0, 0 },
    { 6, 5, 6, 0, 0, 0, 0, 0 },
    3,
    letters_8px
};

/* Symbols */

const uint8_t graphic_right_arrow[9] = { 0x18, 0x18, 0x18, 0x18, 0x18, 0xFF, 0x7E, 0x3C, 0x18 };
const uint8_t graphic_left_selector_5x8[5] = { 0xC3, 0xE7, 0x7E, 0x3C, 0x18 };
const uint8_t graphic_right_selector_5x8[5] = { 0x18, 0x3C, 0x7E, 0xE7, 0xC3 };
const uint8_t graphic_dots_2x8[] = { 0x66, 0x66 };

const uint8_t* symbols[] = {
    graphic_right_arrow,
    graphic_left_selector_5x8,
    graphic_right_selector_5x8,
    graphic_dots_2x8
};

const graphic_t right_arrow_8px = {
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 9, 0, 0, 0, 0, 0, 0, 0 },
    1,
    symbols
};

const graphic_t left_selector_8px = {
    { 1, 0, 0, 0, 0, 0, 0, 0 },
    { 5, 0, 0, 0, 0, 0, 0, 0 },
    1,
    symbols
};

const graphic_t right_selector_8px = {
    { 2, 0, 0, 0, 0, 0, 0, 0 },
    { 5, 0, 0, 0, 0, 0, 0, 0 },
    1,
    symbols
};

const graphic_t dots_8px = {
    { 3, 0, 0, 0, 0, 0, 0, 0 },
    { 2, 0, 0, 0, 0, 0, 0, 0 },
    1,
    symbols
};

/* Letter 16 pixel height */
const uint8_t letter_A_9x16[18] PROGMEM = {
    0xF8, 0xFC, 0xFE, 0x8E, 0x8E, 0x8E, 0xFE, 0xFC, 0xF8,
    0x7F, 0x7F, 0x7F, 0x03, 0x03, 0x03, 0x7F, 0x7F, 0x7F
};

const uint8_t letter_D_9x16[18] PROGMEM = {
    0xFE, 0xFE, 0xFE, 0x0E, 0x0E, 0x0E, 0xFE, 0xFC, 0xF8,
    0x7F, 0x7F, 0x7F, 0x70, 0x70, 0x70, 0x7F, 0x3F, 0x1F
};

const uint8_t letter_E_7x16[14] PROGMEM = {
    0xFE, 0xFE, 0xFE, 0xCE, 0xCE, 0x0E, 0x0E,
    0x7F, 0x7F, 0x7F, 0x71, 0x71, 0x70, 0x70
};

const uint8_t letter_F_7x16[14] PROGMEM = {
    0xFE, 0xFE, 0xFE, 0x8E, 0x8E, 0x0E, 0x0E,
    0x7F, 0x7F, 0x7F, 0x03, 0x03, 0x00, 0x00
};

const uint8_t letter_H_9x16[18] PROGMEM = {
    0xFE, 0xFE, 0xFE, 0xC0, 0xC0, 0xC0, 0xFE, 0xFE, 0xFE,
    0x7F, 0x7F, 0x7F, 0x01, 0x01, 0x01, 0x7F, 0x7F, 0x7F
};

const uint8_t letter_I_3x16[6] PROGMEM = { 0xFE, 0xFE, 0xFE, 0x7F, 0x7F, 0x7F };

const uint8_t letter_K_8x16[16] PROGMEM = {
    0xFE, 0xFE, 0xFE, 0xE0, 0xE0, 0xFE, 0x7E, 0x1E,
    0x7F, 0x7F, 0x7F, 0x07, 0x07, 0x7F, 0x7E, 0x78
};

const uint8_t letter_N_10x16[20] PROGMEM = {
    0xFE, 0xFE, 0xFE, 0xF8, 0xF0, 0xE0, 0xC0, 0xFE, 0xFE, 0xFE,
    0x7F, 0x7F, 0x7F, 0x03, 0x07, 0x0F, 0x1F, 0x7F, 0x7F, 0x7F
};

const uint8_t letter_O_10x16[20] PROGMEM = {
    0xF8, 0xFC, 0xFE, 0x0E, 0x0E, 0x0E, 0x0E, 0xFE, 0xFC, 0xF8,
    0x1F, 0x3F, 0x7F, 0x70, 0x70, 0x70, 0x70, 0x7F, 0x3F, 0x1F
};

const uint8_t letter_P_8x16[16] PROGMEM = {
    0xFE, 0xFE, 0xFE, 0x8E, 0x8E, 0xFE, 0xFC, 0xF8,
    0x7F, 0x7F, 0x7F, 0x03, 0x03, 0x03, 0x01, 0x00
};

const uint8_t letter_R_8x16[16] PROGMEM = {
    0xFE, 0xFE, 0xFE, 0x8E, 0x8E, 0xFE, 0xFC, 0xF8,
    0x7F, 0x7F, 0x7F, 0x1F, 0x3F, 0x7D, 0x79, 0x70
};

const uint8_t letter_S_8x16[16] PROGMEM = {
    0xFC, 0xFE, 0xFE, 0x8E, 0x8E, 0x8E, 0x8E, 0x0C,
    0x31, 0x73, 0x73, 0x73, 0x73, 0x7F, 0x7F, 0x3F
};

const uint8_t letter_U_9x16[18] PROGMEM = {
    0xFE, 0xFE, 0xFE, 0x00, 0x00, 0x00, 0xFE, 0xFE, 0xFE,
    0x1F, 0x3F, 0x7F, 0x70, 0x70, 0x70, 0x7F, 0x3F, 0x1F
};

const uint8_t letter_W_15x16[30] PROGMEM = {
    0xFE, 0xFE, 0xFE, 0x00, 0x00, 0x00, 0xC0, 0xC0, 0xC0, 0x00,
    0x00, 0x00, 0xFE, 0xFE, 0xFE, 0x0F, 0x1F, 0x3F, 0x78, 0x70,
    0x78, 0x3F, 0x1F, 0x3F, 0x78, 0x70, 0x78, 0x3F, 0x1F, 0x0F
};

const uint8_t* letters_16px[] = {
    [0] = letter_A_9x16,
    [1] = letter_D_9x16,
    [2] = letter_E_7x16,
    [3] = letter_F_7x16,
    [4] = letter_H_9x16,
    [5] = letter_I_3x16,
    [6] = letter_K_8x16,
    [7] = letter_N_10x16,
    [8] = letter_O_10x16,
    [9] = letter_P_8x16,
    [10] = letter_R_8x16,
    [11] = letter_S_8x16,
    [12] = letter_U_9x16,
    [13] = letter_W_15x16
};

const graphic_t work_16px = {
    { 13, 8, 10, 6, 0, 0, 0, 0 },
    { 15, 10, 8, 8, 0, 0, 0, 0 },
    4,
    letters_16px
};

const graphic_t pause_16px = {
    { 9, 0, 12, 11, 2, 0, 0, 0 },
    { 8, 9, 9, 8, 7, 0, 0, 0 },
    5,
    letters_16px
};

const graphic_t finished_16px = {
    { 3, 5, 7, 5, 11, 4, 2, 1 },
    { 7, 3, 10, 3, 8, 9, 7, 9 },
    8,
    letters_16px
};
