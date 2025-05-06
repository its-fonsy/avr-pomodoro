#ifndef _UI_PAGES_H
#define _UI_PAGES_H

#include "../ssd1306.h"

void ui_page_draw_work_finished(ssd1306_t* display);
void ui_page_draw_pause_finished(ssd1306_t* display);
void ui_page_draw_left_selectors(ssd1306_t* display);
void ui_page_draw_right_selectors(ssd1306_t* display);

void ui_page_clear_left_selectors(ssd1306_t* display);
void ui_page_clear_right_selectors(ssd1306_t* display);

#endif /* _UI_PAGES_H */
