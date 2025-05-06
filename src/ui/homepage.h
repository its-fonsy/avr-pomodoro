#ifndef __UI_HOMEPAGE_H
#define __UI_HOMEPAGE_H

#include "../fsm.h"
#include "../ssd1306.h"
#include <stdint.h>

void ui_homepage_draw(ssd1306_t* display, timer_t work, timer_t pause);
void ui_homepage_draw_words(ssd1306_t* display);
void ui_homepage_draw_work_min(ssd1306_t* display, uint8_t min);
void ui_homepage_draw_work_sec(ssd1306_t* display, uint8_t sec);
void ui_homepage_draw_pause_min(ssd1306_t* display, uint8_t min);
void ui_homepage_draw_pause_sec(ssd1306_t* display, uint8_t sec);
void ui_homepage_draw_timers_dots(ssd1306_t* display);
void ui_homepage_draw_pause_timer_dots(ssd1306_t* display);
void ui_homepage_draw_left_selectors(ssd1306_t* display);
void ui_homepage_draw_right_selectors(ssd1306_t* display);

void ui_homepage_clear_work_min(ssd1306_t* display);
void ui_homepage_clear_work_sec(ssd1306_t* display);
void ui_homepage_clear_pause_min(ssd1306_t* display);
void ui_homepage_clear_pause_sec(ssd1306_t* display);
void ui_homepage_clear_left_selectors(ssd1306_t* display);
void ui_homepage_clear_right_selectors(ssd1306_t* display);

#endif /* __UI_HOMEPAGE_H */
