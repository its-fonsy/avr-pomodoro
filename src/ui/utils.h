#ifndef __UI_COMMON_H
#define __UI_COMMON_H

#include "../ssd1306.h"
#include "font.h"
#include <stdint.h>

void ui_util_draw_graphic_8px_one_line(ssd1306_t* display, graphic_t g);
void ui_util_draw_graphic_8px_between_two_lines(ssd1306_t* display, graphic_t g);
void ui_util_draw_graphic_16px_two_line(ssd1306_t* display, graphic_t g);

uint8_t ui_util_graphic_8px_pixel_width(graphic_t graphic);
uint8_t ui_util_graphic_16px_pixel_width(graphic_t graphic);
graphic_t ui_util_number_to_graphic_8px(uint8_t n);

#endif /* __UI_COMMON_H */
