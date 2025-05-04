#include "homepage.h"
#include "utils.h"

void ui_homepage_draw_words(ssd1306_t* display)
{
    ssd1306_address_boundary_t col;
    ssd1306_address_boundary_t page;
    uint8_t disp_pt;
    uint8_t i;
    graphic_t line1[] = { work, timer, right_arrow };
    graphic_t line2[] = { pause, timer, right_arrow };

    /* Draw "WOR TIMER ->" */

    disp_pt = 6;
    for (i = 0; i < 3; i++) {
        ssd1306_goto(display, disp_pt, 0);
        ui_util_draw_graphic_one_line(display, line1[i]);
        disp_pt += ui_util_graphic_pixel_width(line1[i]) + 5;
    }

    /* Print "PAUSE TIMER ->" */

    page.start = 1;
    page.end = 2;
    col.start = 0;
    for (i = 0; i < 3; i++) {
        col.end = col.start + ui_util_graphic_pixel_width(line2[i]) - 1;
        ssd1306_set_column_and_page_address_boundary(display, col, page);
        ui_util_draw_graphic_between_two_lines(display, line2[i]);
        col.start += ui_util_graphic_pixel_width(line2[i]) + 5;
    }

    ssd1306_reset_column_and_page_boundaries(display);

    /* Print "START" on bottom line */

    disp_pt = 10;
    ssd1306_goto(display, disp_pt, 3);
    ui_util_draw_graphic_one_line(display, start);

    /* Print "SET" on bottom line */

    disp_pt = 98;
    ssd1306_goto(display, disp_pt, 3);
    ui_util_draw_graphic_one_line(display, set);
}

void ui_homepage_draw_timers_dots(ssd1306_t* display)
{
    ssd1306_address_boundary_t col;
    ssd1306_address_boundary_t page;

    col.start = 100;
    col.end = 101;
    page.start = 1;
    page.end = 2;

    ssd1306_goto(display, col.start, 0);
    ui_util_draw_graphic_one_line(display, dots);

    ssd1306_set_column_and_page_address_boundary(display, col, page);
    ui_util_draw_graphic_between_two_lines(display, dots);
    ssd1306_reset_column_and_page_boundaries(display);
}

void ui_homepage_draw_work_min(ssd1306_t* display, uint8_t min)
{
    uint8_t blank[6] = { 0 };
    graphic_t number;

    number = ui_util_number_to_graphic(min);

    if (min < 10) {
        ssd1306_goto(display, 85, 0);
        ssd1306_data(display, blank, 6);
    }

    ssd1306_goto(display, (min < 10) ? 92 : 85, 0);
    ui_util_draw_graphic_one_line(display, number);
}

void ui_homepage_draw_work_sec(ssd1306_t* display, uint8_t sec)
{
    graphic_t number;
    number = ui_util_number_to_graphic(sec);

    if (sec < 10) {
        number.graphic_lut[1] = number.graphic_lut[0];
        number.graphic_lut[0] = 0;
        number.graphic_size[1] = 6;
        number.size = 2;
    }

    ssd1306_goto(display, 104, 0);
    ui_util_draw_graphic_one_line(display, number);
}

void ui_homepage_draw_pause_min(ssd1306_t* display, uint8_t min)
{
    ssd1306_address_boundary_t col;
    ssd1306_address_boundary_t page;
    graphic_t number;
    uint8_t blank[6] = { 0 };

    page.start = 1;
    page.end = 2;
    number = ui_util_number_to_graphic(min);

    if (min < 10) {
        col.start = 85;
        col.end = col.start + 6 - 1;
        ssd1306_set_column_and_page_address_boundary(display, col, page);
        ssd1306_data(display, blank, 6);
        ssd1306_data(display, blank, 6);
    }

    col.start = (min >= 10) ? 85 : 92;
    col.end = col.start + ui_util_graphic_pixel_width(number) - 1;
    ssd1306_set_column_and_page_address_boundary(display, col, page);
    ui_util_draw_graphic_between_two_lines(display, number);
    ssd1306_reset_column_and_page_boundaries(display);
}

void ui_homepage_draw_pause_sec(ssd1306_t* display, uint8_t sec)
{
    ssd1306_address_boundary_t col;
    ssd1306_address_boundary_t page;
    graphic_t number;

    number = ui_util_number_to_graphic(sec);
    if (sec < 10) {
        number.graphic_lut[1] = number.graphic_lut[0];
        number.graphic_lut[0] = 0;
        number.graphic_size[1] = 6;
        number.size = 2;
    }

    col.start = 104;
    col.end = col.start + ui_util_graphic_pixel_width(number) - 1;
    page.start = 1;
    page.end = 2;

    ssd1306_set_column_and_page_address_boundary(display, col, page);
    ui_util_draw_graphic_between_two_lines(display, number);
    ssd1306_reset_column_and_page_boundaries(display);
}

void ui_homepage_draw_left_selectors(ssd1306_t* display)
{
    ssd1306_goto(display, 0, 3);
    ui_util_draw_graphic_one_line(display, left_selector);
    ssd1306_goto(display, 48, 3);
    ui_util_draw_graphic_one_line(display, right_selector);
}

void ui_homepage_draw_right_selectors(ssd1306_t* display)
{
    ssd1306_goto(display, 88, 3);
    ui_util_draw_graphic_one_line(display, left_selector);
    ssd1306_goto(display, 122, 3);
    ui_util_draw_graphic_one_line(display, right_selector);
}

uint8_t blank[13] = { 0 };
void ui_homepage_clear_left_selectors(ssd1306_t* display)
{
    ssd1306_goto(display, 0, 3);
    ssd1306_data(display, blank, 5);
    ssd1306_goto(display, 48, 3);
    ssd1306_data(display, blank, 5);
}

void ui_homepage_clear_right_selectors(ssd1306_t* display)
{
    ssd1306_goto(display, 88, 3);
    ssd1306_data(display, blank, 5);
    ssd1306_goto(display, 122, 3);
    ssd1306_data(display, blank, 5);
}

void ui_homepage_clear_work_min(ssd1306_t* display)
{
    ssd1306_goto(display, 85, 0);
    ssd1306_data(display, blank, 13);
}

void ui_homepage_clear_work_sec(ssd1306_t* display)
{
    ssd1306_goto(display, 104, 0);
    ssd1306_data(display, blank, 13);
}

void ui_homepage_clear_pause_min(ssd1306_t* display)
{
    ssd1306_address_boundary_t col;
    ssd1306_address_boundary_t page;

    page.start = 1;
    page.end = 2;
    col.start = 85;
    col.end = col.start + 13 - 1;

    ssd1306_set_column_and_page_address_boundary(display, col, page);
    ssd1306_data(display, blank, 13);
    ssd1306_data(display, blank, 13);
    ssd1306_reset_column_and_page_boundaries(display);
}

void ui_homepage_clear_pause_sec(ssd1306_t* display)
{
    ssd1306_address_boundary_t col;
    ssd1306_address_boundary_t page;

    page.start = 1;
    page.end = 2;
    col.start = 104;
    col.end = col.start + 13 - 1;

    ssd1306_set_column_and_page_address_boundary(display, col, page);
    ssd1306_data(display, blank, 13);
    ssd1306_data(display, blank, 13);
    ssd1306_reset_column_and_page_boundaries(display);
}
