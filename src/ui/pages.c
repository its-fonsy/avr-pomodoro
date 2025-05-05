#include "pages.h"

#include "../ssd1306.h"
#include "font.h"
#include "utils.h"
#include <stdint.h>

void ui_page_draw_work_finished(ssd1306_t* display)
{
    uint8_t i;
    ssd1306_address_boundary_t col;
    ssd1306_address_boundary_t page;
    graphic_t start_pause[] = { left_selector_8px, start_8px, pause_8px, right_selector_8px };

    /* Draw "WORK" */
    page.start = 0;
    page.end = 1;
    col.start = 0;
    col.end = col.start + ui_util_graphic_16px_pixel_width(work_16px) - 1;
    ssd1306_set_column_and_page_address_boundary(display, col, page);
    ui_util_draw_graphic_16px_two_line(display, work_16px);

    /* Draw "FINISHED" */
    page.start = 0;
    page.end = 1;
    col.end = DISPLAY_WIDTH - 1;
    col.start = col.end - ui_util_graphic_16px_pixel_width(finished_16px) + 1;
    ssd1306_set_column_and_page_address_boundary(display, col, page);
    ui_util_draw_graphic_16px_two_line(display, finished_16px);

    /* Draw "> START PAUSE <" */
    page.start = 2;
    page.end = 3;
    col.start = 19;
    for (i = 0; i < 4; i++) {
        col.end = col.start + ui_util_graphic_8px_pixel_width(start_pause[i]) - 1;
        ssd1306_set_column_and_page_address_boundary(display, col, page);
        ui_util_draw_graphic_8px_between_two_lines(display, start_pause[i]);
        col.start += ui_util_graphic_8px_pixel_width(start_pause[i]) + 5;
    }
}

void ui_page_draw_pause_finished(ssd1306_t* display)
{
    uint8_t i;
    ssd1306_address_boundary_t col;
    ssd1306_address_boundary_t page;
    graphic_t set_timer[] = { set_8px, timer_8px };

    /* Draw "WORK" */
    page.start = 0;
    page.end = 1;
    col.start = 0;
    col.end = col.start + ui_util_graphic_16px_pixel_width(pause_16px) - 1;
    ssd1306_set_column_and_page_address_boundary(display, col, page);
    ui_util_draw_graphic_16px_two_line(display, pause_16px);

    /* Draw "FINISHED" */
    page.start = 0;
    page.end = 1;
    col.end = DISPLAY_WIDTH - 1;
    col.start = col.end - ui_util_graphic_16px_pixel_width(finished_16px) + 1;
    ssd1306_set_column_and_page_address_boundary(display, col, page);
    ui_util_draw_graphic_16px_two_line(display, finished_16px);

    ssd1306_reset_column_and_page_boundaries(display);

    /* Draw "REPEAT" */
    ssd1306_goto(display, 7, 3);
    ui_util_draw_graphic_8px_one_line(display, repeat_8px);

    /* Draw "SET TIMER" */
    col.start = 66;
    for (i = 0; i < 2; i++) {
        ssd1306_goto(display, col.start, 3);
        ui_util_draw_graphic_8px_one_line(display, set_timer[i]);
        col.start += ui_util_graphic_8px_pixel_width(set_timer[i]) + 5;
    }
}

#define LEFT_LEFT_SEL_X 0
#define LEFT_RIGHT_SEL_X 45
#define RIGHT_LEFT_SEL_X 59
#define RIGHT_RIGHT_SEL_X 122

void ui_page_draw_left_selectors(ssd1306_t* display)
{
    ssd1306_goto(display, LEFT_LEFT_SEL_X, 3);
    ui_util_draw_graphic_8px_one_line(display, left_selector_8px);
    ssd1306_goto(display, LEFT_RIGHT_SEL_X, 3);
    ui_util_draw_graphic_8px_one_line(display, right_selector_8px);
}

void ui_page_draw_right_selectors(ssd1306_t* display)
{
    ssd1306_goto(display, RIGHT_LEFT_SEL_X, 3);
    ui_util_draw_graphic_8px_one_line(display, left_selector_8px);
    ssd1306_goto(display, RIGHT_RIGHT_SEL_X, 3);
    ui_util_draw_graphic_8px_one_line(display, right_selector_8px);
}

void ui_page_clear_left_selectors(ssd1306_t* display)
{
    uint8_t blank[5] = { 0 };
    ssd1306_goto(display, LEFT_LEFT_SEL_X, 3);
    ssd1306_data(display, blank, 5);
    ssd1306_goto(display, LEFT_RIGHT_SEL_X, 3);
    ssd1306_data(display, blank, 5);
}

void ui_page_clear_right_selectors(ssd1306_t* display)
{
    uint8_t blank[5] = { 0 };
    ssd1306_goto(display, RIGHT_LEFT_SEL_X, 3);
    ssd1306_data(display, blank, 5);
    ssd1306_goto(display, RIGHT_RIGHT_SEL_X, 3);
    ssd1306_data(display, blank, 5);
}
