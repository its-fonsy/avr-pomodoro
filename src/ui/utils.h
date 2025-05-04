#ifndef __UI_COMMON_H
#define __UI_COMMON_H

#include "../ssd1306.h"
#include "font.h"
#include <stdint.h>

void ui_util_draw_graphic_one_line(ssd1306_t* display, graphic_t word);
void ui_util_draw_graphic_between_two_lines(ssd1306_t* display, graphic_t word);

/* Utilities functions */

uint8_t ui_util_graphic_pixel_width(graphic_t word);
graphic_t ui_util_number_to_graphic(uint8_t n);
void ui_util_draw_graphic_array(ssd1306_t display, graphic_t* graphic_arr);

#endif /* __UI_COMMON_H */
