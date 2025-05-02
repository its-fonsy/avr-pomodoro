#include "ui.h"

#include <avr/io.h>
#include <stdint.h>
#include <string.h>

#include <util/delay.h>

#include "font.h"
#include "ssd1306.h"

void ui_test(ssd1306_t* dev)
{

    ssd1306_address_boundary_t col;
    ssd1306_address_boundary_t page;
    graphic_t number;
    uint8_t disp_pt;

    disp_pt = 5;

    ssd1306_goto(dev, disp_pt, 0);
    ui_print_line(dev, work);
    disp_pt += ui_graphic_pixel_width(work) + 5;

    ssd1306_goto(dev, disp_pt, 0);
    ui_print_line(dev, timer);
    disp_pt += ui_graphic_pixel_width(timer) + 5;

    ssd1306_goto(dev, disp_pt, 0);
    ui_print_line(dev, right_arrow);
    disp_pt += ui_graphic_pixel_width(right_arrow) + 5;

    number = number_to_graphic(25);
    ssd1306_goto(dev, disp_pt, 0);
    ui_print_line(dev, number);
    disp_pt += ui_graphic_pixel_width(number) + 5;

    number = number_to_graphic(30);
    ssd1306_goto(dev, disp_pt, 0);
    ui_print_line(dev, number);
    disp_pt += ui_graphic_pixel_width(number) + 5;

    page.start = 1;
    page.end = 2;

    col.start = 0;
    col.end = col.start + ui_graphic_pixel_width(pause) - 1;
    ssd1306_set_column_and_page_address_boundary(dev, col, page);
    ui_print_between_two_line(dev, pause);

    col.start += ui_graphic_pixel_width(pause) + 5;
    col.end = col.start + ui_graphic_pixel_width(timer) - 1;
    ssd1306_set_column_and_page_address_boundary(dev, col, page);
    ui_print_between_two_line(dev, timer);

    col.start += ui_graphic_pixel_width(timer) + 5;
    col.end = col.start + ui_graphic_pixel_width(right_arrow) - 1;
    ssd1306_set_column_and_page_address_boundary(dev, col, page);
    ui_print_between_two_line(dev, right_arrow);

    number = number_to_graphic(5);
    col.start += ui_graphic_pixel_width(right_arrow) + 5;
    col.end = col.start + ui_graphic_pixel_width(number) - 1;
    ssd1306_set_column_and_page_address_boundary(dev, col, page);
    ui_print_between_two_line(dev, number);

    col.start += ui_graphic_pixel_width(number) + 5;
    number = number_to_graphic(30);
    col.end = col.start + ui_graphic_pixel_width(number) - 1;
    ssd1306_set_column_and_page_address_boundary(dev, col, page);
    ui_print_between_two_line(dev, number);

    ssd1306_reset_column_and_page_boundaries(dev);
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

void ui_print_line(ssd1306_t* dev, graphic_t g)
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

void ui_print_between_two_line(ssd1306_t* dev, graphic_t g)
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
