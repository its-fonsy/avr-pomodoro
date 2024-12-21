#ifndef __UI_H
#define __UI_H

#include <stdint.h>
#include "font.h"

#define FONT_DOT_WIDTH 6
#define FONT_OFFSET 4
#define FONT_MINUTES_X 13
#define FONT_DOTS_X FONT_MINUTES_X + 2*FONT_WIDTH + 2*FONT_OFFSET
#define FONT_SECONDS_X FONT_DOTS_X + FONT_DOT_WIDTH + FONT_OFFSET

void ui_draw_minutes(uint8_t n);
void ui_draw_seconds(uint8_t n);
void ui_draw_dots();

#endif /* __UI_H */
