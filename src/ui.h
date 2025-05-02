#ifndef __UI_H
#define __UI_H

#include "font.h"
#include "rotary_encoder.h"
#include "ssd1306.h"
#include <stdint.h>

void ui_test(ssd1306_t* dev, rotary_encoder_t* rotary);

void ui_print_line(ssd1306_t* dev, graphic_t word);
void ui_print_between_two_line(ssd1306_t* dev, graphic_t word);
void ui_print_left_selectors(ssd1306_t* dev);
void ui_print_right_selectors(ssd1306_t* dev);
void ui_clear_left_selectors(ssd1306_t* dev);
void ui_clear_right_selectors(ssd1306_t* dev);

/* Utilities functions */

uint8_t ui_graphic_pixel_width(graphic_t word);
graphic_t number_to_graphic(uint8_t n);
void ui_print_graphic_array(ssd1306_t dev, graphic_t* graphic_arr);

#endif /* __UI_H */
