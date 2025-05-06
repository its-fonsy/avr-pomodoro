#ifndef __UI_TIMER_H
#define __UI_TIMER_H

#include "../ssd1306.h"

#define FONT_8x16_OFFSET 2
#define FONT_DOT_WIDTH 5
#define FONT_OFFSET 4
#define FONT_MINUTES_X 9
#define FONT_DOTS_X FONT_MINUTES_X + 2 * FONT_20x32_WIDTH + 3 * FONT_OFFSET
#define FONT_SECONDS_X FONT_DOTS_X + FONT_DOT_WIDTH + 2 * FONT_OFFSET

void ui_timer_draw_minutes(ssd1306_t* display, uint8_t minutes);
void ui_timer_draw_seconds(ssd1306_t* display, uint8_t seconds);
void ui_timer_draw_dots(ssd1306_t* display);
void ui_timer_draw_timer(ssd1306_t* display, uint8_t minutes, uint8_t seconds);

#endif /* __UI_TIMER_H */
