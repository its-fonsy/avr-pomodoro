#include "ui.h"

#include <avr/io.h>
#include <stdint.h>
#include <string.h>

#include <util/delay.h>

#include "font.h"
#include "ssd1306.h"

void ui_draw_homepage(ssd1306_t* display)
{
    ui_draw_homepage_words(display);
    ui_draw_homepage_work_min(display, 25);
    ui_draw_homepage_work_sec(display, 0);
    ui_draw_homepage_timers_dots(display);
    ui_draw_homepage_pause_min(display, 10);
    ui_draw_homepage_pause_sec(display, 30);
}

void ui_draw_homepage_timers_dots(ssd1306_t* display)
{
    ssd1306_address_boundary_t col;
    ssd1306_address_boundary_t page;

    col.start = 100;
    col.end = 101;
    page.start = 1;
    page.end = 2;

    ssd1306_goto(display, col.start, 0);
    ui_draw_graphic_one_line(display, dots);

    ssd1306_set_column_and_page_address_boundary(display, col, page);
    ui_draw_graphic_between_two_lines(display, dots);
    ssd1306_reset_column_and_page_boundaries(display);
}

void ui_clear_homepage_work_min(ssd1306_t* display)
{
    uint8_t blank[13] = { 0 };
    ssd1306_goto(display, 85, 0);
    ssd1306_data(display, blank, 13);
}

void ui_clear_homepage_work_sec(ssd1306_t* display)
{
    uint8_t blank[13] = { 0 };
    ssd1306_goto(display, 104, 0);
    ssd1306_data(display, blank, 13);
}

void ui_clear_homepage_pause_min(ssd1306_t* display)
{
    ssd1306_address_boundary_t col;
    ssd1306_address_boundary_t page;
    uint8_t blank[13] = { 0 };

    page.start = 1;
    page.end = 2;
    col.start = 85;
    col.end = col.start + 13 - 1;

    ssd1306_set_column_and_page_address_boundary(display, col, page);
    ssd1306_data(display, blank, 13);
    ssd1306_data(display, blank, 13);
    ssd1306_reset_column_and_page_boundaries(display);
}
void ui_clear_homepage_pause_sec(ssd1306_t* display)
{
    ssd1306_address_boundary_t col;
    ssd1306_address_boundary_t page;
    uint8_t blank[13] = { 0 };

    page.start = 1;
    page.end = 2;
    col.start = 104;
    col.end = col.start + 13 - 1;

    ssd1306_set_column_and_page_address_boundary(display, col, page);
    ssd1306_data(display, blank, 13);
    ssd1306_data(display, blank, 13);
    ssd1306_reset_column_and_page_boundaries(display);
}

void ui_draw_homepage_work_min(ssd1306_t* display, uint8_t min)
{
    uint8_t blank[6] = { 0 };
    graphic_t number;

    number = number_to_graphic(min);

    if (min < 10) {
        ssd1306_goto(display, 85, 0);
        ssd1306_data(display, blank, 6);
    }

    ssd1306_goto(display, (min < 10) ? 92 : 85, 0);
    ui_draw_graphic_one_line(display, number);
}

void ui_draw_homepage_work_sec(ssd1306_t* display, uint8_t sec)
{
    graphic_t number;
    number = number_to_graphic(sec);

    if (sec < 10) {
        number.graphic_lut[1] = number.graphic_lut[0];
        number.graphic_lut[0] = 0;
        number.graphic_size[1] = 6;
        number.size = 2;
    }

    ssd1306_goto(display, 104, 0);
    ui_draw_graphic_one_line(display, number);
}

void ui_draw_homepage_pause_min(ssd1306_t* display, uint8_t min)
{
    ssd1306_address_boundary_t col;
    ssd1306_address_boundary_t page;
    graphic_t number;
    uint8_t blank[6] = { 0 };

    page.start = 1;
    page.end = 2;
    number = number_to_graphic(min);

    if (min < 10) {
        col.start = 85;
        col.end = col.start + 6 - 1;
        ssd1306_set_column_and_page_address_boundary(display, col, page);
        ssd1306_data(display, blank, 6);
        ssd1306_data(display, blank, 6);
    }

    col.start = (min >= 10) ? 85 : 92;
    col.end = col.start + ui_graphic_pixel_width(number) - 1;
    ssd1306_set_column_and_page_address_boundary(display, col, page);
    ui_draw_graphic_between_two_lines(display, number);
    ssd1306_reset_column_and_page_boundaries(display);
}

void ui_draw_homepage_pause_sec(ssd1306_t* display, uint8_t sec)
{
    ssd1306_address_boundary_t col;
    ssd1306_address_boundary_t page;
    graphic_t number;

    number = number_to_graphic(sec);
    if (sec < 10) {
        number.graphic_lut[1] = number.graphic_lut[0];
        number.graphic_lut[0] = 0;
        number.graphic_size[1] = 6;
        number.size = 2;
    }

    col.start = 104;
    col.end = col.start + ui_graphic_pixel_width(number) - 1;
    page.start = 1;
    page.end = 2;

    ssd1306_set_column_and_page_address_boundary(display, col, page);
    ui_draw_graphic_between_two_lines(display, number);
    ssd1306_reset_column_and_page_boundaries(display);
}

void ui_draw_homepage_words(ssd1306_t* display)
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
        ui_draw_graphic_one_line(display, line1[i]);
        disp_pt += ui_graphic_pixel_width(line1[i]) + 5;
    }

    /* Print "PAUSE TIMER ->" */

    page.start = 1;
    page.end = 2;
    col.start = 0;
    for (i = 0; i < 3; i++) {
        col.end = col.start + ui_graphic_pixel_width(line2[i]) - 1;
        ssd1306_set_column_and_page_address_boundary(display, col, page);
        ui_draw_graphic_between_two_lines(display, line2[i]);
        col.start += ui_graphic_pixel_width(line2[i]) + 5;
    }

    ssd1306_reset_column_and_page_boundaries(display);

    /* Print "START" on bottom line */

    disp_pt = 10;
    ssd1306_goto(display, disp_pt, 3);
    ui_draw_graphic_one_line(display, start);

    /* Print "SET" on bottom line */

    disp_pt = 98;
    ssd1306_goto(display, disp_pt, 3);
    ui_draw_graphic_one_line(display, set);
}
graphic_t number_to_graphic(uint8_t n)
{
    graphic_t number = { { 0 }, { 0 }, 0, numbers_6x8 };

    if (n > 100)
        return number;

    if (n >= 10) {
        number.size = 2;
        number.graphic_lut[1] = n % 10;
        number.graphic_size[1] = 6;

        n /= 10;

        number.graphic_lut[0] = n;
        number.graphic_size[0] = 6;
    } else {
        number.size = 1;
        number.graphic_lut[0] = n;
        number.graphic_size[0] = 6;
    }

    return number;
}

void ui_draw_graphic_one_line(ssd1306_t* display, graphic_t g)
{
    uint8_t i;
    uint8_t packet[64] = { 0 };
    uint8_t packet_size;
    packet_size = 0;
    for (i = 0; i < g.size; i++) {
        memcpy(packet + packet_size, g.base_array[g.graphic_lut[i]], g.graphic_size[i]);
        packet_size += g.graphic_size[i] + 1;
    }
    ssd1306_data(display, packet, packet_size - 1);
}

void ui_draw_graphic_between_two_lines(ssd1306_t* display, graphic_t g)
{
    uint8_t i;
    uint8_t k;
    uint8_t packet[64] = { 0 };
    uint8_t packet_size;
    uint8_t byte;

    packet_size = 0;
    for (i = 0; i < g.size; i++) {
        for (k = 0; k < g.graphic_size[i]; k++) {
            byte = g.base_array[g.graphic_lut[i]][k];
            byte <<= 4;
            memcpy(packet + packet_size, &byte, 1);
            packet_size++;
        }
        packet_size += (g.size > 1) ? 1 : 0;
    }
    packet_size -= (g.size > 1) ? 1 : 0;
    ssd1306_data(display, packet, packet_size);

    memset(packet, 0x00, 64);

    packet_size = 0;
    for (i = 0; i < g.size; i++) {
        for (k = 0; k < g.graphic_size[i]; k++) {
            byte = g.base_array[g.graphic_lut[i]][k];
            byte >>= 4;
            memcpy(packet + packet_size, &byte, 1);
            packet_size++;
        }
        packet_size += (g.size > 1) ? 1 : 0;
    }
    packet_size -= (g.size > 1) ? 1 : 0;
    ssd1306_data(display, packet, packet_size);
}

uint8_t ui_graphic_pixel_width(graphic_t graphic)
{
    uint8_t i;
    uint8_t length;

    length = 0;

    for (i = 0; i < graphic.size; i++) {
        length += graphic.graphic_size[i];

        /* For every letter add 1 pixel offset */
        length += 1;
    }

    /* Remove from the last letter the offset */
    length -= 1;

    return length;
}

void ui_draw_left_selectors(ssd1306_t* display)
{
    ssd1306_goto(display, 0, 3);
    ui_draw_graphic_one_line(display, left_selector);
    ssd1306_goto(display, 48, 3);
    ui_draw_graphic_one_line(display, right_selector);
}

void ui_draw_right_selectors(ssd1306_t* display)
{
    ssd1306_goto(display, 88, 3);
    ui_draw_graphic_one_line(display, left_selector);
    ssd1306_goto(display, 122, 3);
    ui_draw_graphic_one_line(display, right_selector);
}

uint8_t blank[5] = { 0 };
void ui_clear_left_selectors(ssd1306_t* display)
{
    ssd1306_goto(display, 0, 3);
    ssd1306_data(display, blank, 5);
    ssd1306_goto(display, 48, 3);
    ssd1306_data(display, blank, 5);
}

void ui_clear_right_selectors(ssd1306_t* display)
{
    ssd1306_goto(display, 88, 3);
    ssd1306_data(display, blank, 5);
    ssd1306_goto(display, 122, 3);
    ssd1306_data(display, blank, 5);
}
