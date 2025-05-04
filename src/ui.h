#ifndef __UI_H
#define __UI_H

#include "font.h"
#include "rotary_encoder.h"
#include "ssd1306.h"
#include <stdint.h>

void ui_test(ssd1306_t* display, rotary_encoder_t* rotary);

void ui_draw_homepage(ssd1306_t* display);
void ui_draw_homepage_words(ssd1306_t* display);
void ui_draw_homepage_work_min(ssd1306_t* display, uint8_t min);
void ui_draw_homepage_work_sec(ssd1306_t* display, uint8_t sec);
void ui_draw_homepage_pause_min(ssd1306_t* display, uint8_t min);
void ui_draw_homepage_pause_sec(ssd1306_t* display, uint8_t sec);
void ui_draw_homepage_timers_dots(ssd1306_t* display);
void ui_draw_homepage_pause_timer_dots(ssd1306_t* display);

void ui_clear_homepage_work_min(ssd1306_t* display);
void ui_clear_homepage_work_sec(ssd1306_t* display);
void ui_clear_homepage_pause_min(ssd1306_t* display);
void ui_clear_homepage_pause_sec(ssd1306_t* display);

void ui_draw_graphic_one_line(ssd1306_t* display, graphic_t word);
void ui_draw_graphic_between_two_lines(ssd1306_t* display, graphic_t word);
void ui_draw_left_selectors(ssd1306_t* display);
void ui_draw_right_selectors(ssd1306_t* display);
void ui_clear_left_selectors(ssd1306_t* display);
void ui_clear_right_selectors(ssd1306_t* display);

/* Utilities functions */

uint8_t ui_graphic_pixel_width(graphic_t word);
graphic_t number_to_graphic(uint8_t n);
void ui_print_graphic_array(ssd1306_t display, graphic_t* graphic_arr);

#endif /* __UI_H */
