#include "ui.h"

#include <avr/io.h>
#include <stdint.h>
#include <string.h>

#include <util/delay.h>

#include "font.h"
#include "rotary_encoder.h"
#include "ssd1306.h"

void ui_test(ssd1306_t* dev, rotary_encoder_t* rotary)
{
    int8_t num;

    ui_draw_homepage(dev);

    num = 0;
    while (1) {

        switch (rotary_encoder_is_turned(rotary)) {
        case ROTARY_ENCODER_CCW:
            num++;
            if (num > 99)
                num = 99;
            ui_draw_homepage_work_min(dev, num);
            ui_draw_homepage_work_sec(dev, num);
            ui_draw_homepage_pause_min(dev, num);
            ui_draw_homepage_pause_sec(dev, num);
            break;
        case ROTARY_ENCODER_CW:
            num--;
            if (num < 0)
                num = 0;
            ui_draw_homepage_work_min(dev, num);
            ui_draw_homepage_work_sec(dev, num);
            ui_draw_homepage_pause_min(dev, num);
            ui_draw_homepage_pause_sec(dev, num);
            break;
        }

        _delay_ms(5);
    }
}

void ui_draw_homepage(ssd1306_t* dev)
{
    ui_draw_homepage_words(dev);
    ui_draw_homepage_work_min(dev, 25);
    ui_draw_homepage_work_sec(dev, 0);
    ui_draw_homepage_timers_dots(dev);
    ui_draw_homepage_pause_min(dev, 10);
    ui_draw_homepage_pause_sec(dev, 30);
}

void ui_draw_homepage_timers_dots(ssd1306_t* dev)
{
    ssd1306_address_boundary_t col;
    ssd1306_address_boundary_t page;

    col.start = 100;
    col.end = 101;
    page.start = 1;
    page.end = 2;

    ssd1306_goto(dev, col.start, 0);
    ui_draw_graphic_one_line(dev, dots);

    ssd1306_set_column_and_page_address_boundary(dev, col, page);
    ui_draw_graphic_between_two_lines(dev, dots);
    ssd1306_reset_column_and_page_boundaries(dev);
}

void ui_draw_homepage_work_min(ssd1306_t* dev, uint8_t min)
{
    uint8_t blank[6] = { 0 };
    graphic_t number;

    number = number_to_graphic(min);

    if (min < 10) {
        ssd1306_goto(dev, 85, 0);
        ssd1306_data(dev, blank, 6);
    }

    ssd1306_goto(dev, (min < 10) ? 92 : 85, 0);
    ui_draw_graphic_one_line(dev, number);
}

void ui_draw_homepage_work_sec(ssd1306_t* dev, uint8_t sec)
{
    graphic_t number;
    number = number_to_graphic(sec);

    if (sec < 10) {
        number.graphic_lut[1] = number.graphic_lut[0];
        number.graphic_lut[0] = 0;
        number.graphic_size[1] = 6;
        number.size = 2;
    }

    ssd1306_goto(dev, 104, 0);
    ui_draw_graphic_one_line(dev, number);
}

void ui_draw_homepage_pause_min(ssd1306_t* dev, uint8_t min)
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
        ssd1306_set_column_and_page_address_boundary(dev, col, page);
        ssd1306_data(dev, blank, 6);
        ssd1306_data(dev, blank, 6);
    }

    col.start = (min >= 10) ? 85 : 92;
    col.end = col.start + ui_graphic_pixel_width(number) - 1;
    ssd1306_set_column_and_page_address_boundary(dev, col, page);
    ui_draw_graphic_between_two_lines(dev, number);
    ssd1306_reset_column_and_page_boundaries(dev);
}

void ui_draw_homepage_pause_sec(ssd1306_t* dev, uint8_t sec)
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

    ssd1306_set_column_and_page_address_boundary(dev, col, page);
    ui_draw_graphic_between_two_lines(dev, number);
    ssd1306_reset_column_and_page_boundaries(dev);
}

void ui_draw_homepage_words(ssd1306_t* dev)
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
        ssd1306_goto(dev, disp_pt, 0);
        ui_draw_graphic_one_line(dev, line1[i]);
        disp_pt += ui_graphic_pixel_width(line1[i]) + 5;
    }

    /* Print "PAUSE TIMER ->" */

    page.start = 1;
    page.end = 2;
    col.start = 0;
    for (i = 0; i < 3; i++) {
        col.end = col.start + ui_graphic_pixel_width(line2[i]) - 1;
        ssd1306_set_column_and_page_address_boundary(dev, col, page);
        ui_draw_graphic_between_two_lines(dev, line2[i]);
        col.start += ui_graphic_pixel_width(line2[i]) + 5;
    }

    ssd1306_reset_column_and_page_boundaries(dev);

    /* Print "START" on bottom line */

    disp_pt = 10;
    ssd1306_goto(dev, disp_pt, 3);
    ui_draw_graphic_one_line(dev, start);

    /* Print "SET" on bottom line */

    disp_pt = 98;
    ssd1306_goto(dev, disp_pt, 3);
    ui_draw_graphic_one_line(dev, set);
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

void ui_draw_graphic_one_line(ssd1306_t* dev, graphic_t g)
{
    uint8_t i;
    uint8_t packet[64] = { 0 };
    uint8_t packet_size;
    packet_size = 0;
    for (i = 0; i < g.size; i++) {
        memcpy(packet + packet_size, g.base_array[g.graphic_lut[i]], g.graphic_size[i]);
        packet_size += g.graphic_size[i] + 1;
    }
    ssd1306_data(dev, packet, packet_size - 1);
}

void ui_draw_graphic_between_two_lines(ssd1306_t* dev, graphic_t g)
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
    ssd1306_data(dev, packet, packet_size);

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
    ssd1306_data(dev, packet, packet_size);
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

void ui_draw_left_selectors(ssd1306_t* dev)
{
    ssd1306_goto(dev, 0, 3);
    ui_draw_graphic_one_line(dev, left_selector);
    ssd1306_goto(dev, 48, 3);
    ui_draw_graphic_one_line(dev, right_selector);
}

void ui_draw_right_selectors(ssd1306_t* dev)
{
    ssd1306_goto(dev, 88, 3);
    ui_draw_graphic_one_line(dev, left_selector);
    ssd1306_goto(dev, 122, 3);
    ui_draw_graphic_one_line(dev, right_selector);
}

uint8_t blank[5] = { 0 };
void ui_clear_left_selectors(ssd1306_t* dev)
{
    ssd1306_goto(dev, 0, 3);
    ssd1306_data(dev, blank, 5);
    ssd1306_goto(dev, 48, 3);
    ssd1306_data(dev, blank, 5);
}

void ui_clear_right_selectors(ssd1306_t* dev)
{
    ssd1306_goto(dev, 88, 3);
    ssd1306_data(dev, blank, 5);
    ssd1306_goto(dev, 122, 3);
    ssd1306_data(dev, blank, 5);
}
