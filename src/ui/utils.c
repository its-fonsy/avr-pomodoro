#include "utils.h"

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdint.h>
#include <string.h>

#include <util/delay.h>

#include "../ssd1306.h"
#include "font.h"

#define UI_UTIL_PACKET_MAX_SIZE 96

uint8_t packet[UI_UTIL_PACKET_MAX_SIZE] = { 0 };
uint8_t packet_size;

graphic_t ui_util_number_to_graphic_8px(uint8_t n)
{
    graphic_t number = { { 0 }, { 0 }, 0, numbers_8px };

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

void ui_util_draw_graphic_8px_one_line(ssd1306_t* display, graphic_t g)
{
    uint8_t i;
    memset(packet, 0x00, UI_UTIL_PACKET_MAX_SIZE);
    packet_size = 0;
    for (i = 0; i < g.size; i++) {
        memcpy(packet + packet_size, g.base_array[g.graphic_lut[i]], g.graphic_size[i]);
        packet_size += g.graphic_size[i] + 1;
    }
    ssd1306_data(display, packet, packet_size - 1);
}

void ui_util_draw_graphic_8px_between_two_lines(ssd1306_t* display, graphic_t g)
{
    uint8_t i;
    uint8_t k;
    uint8_t byte;

    memset(packet, 0x00, UI_UTIL_PACKET_MAX_SIZE);
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

    memset(packet, 0x00, UI_UTIL_PACKET_MAX_SIZE);
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

uint8_t ui_util_graphic_8px_pixel_width(graphic_t graphic)
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

void ui_util_draw_graphic_16px_two_line(ssd1306_t* display, graphic_t g)
{
    uint8_t i;

    memset(packet, 0x00, UI_UTIL_PACKET_MAX_SIZE);
    packet_size = 0;

    for (i = 0; i < g.size; i++) {
        memcpy_P(packet + packet_size, g.base_array[g.graphic_lut[i]], g.graphic_size[i]);
        packet_size += g.graphic_size[i] + 2;
    }
    ssd1306_data(display, packet, packet_size - 2);

    packet_size = 0;
    for (i = 0; i < g.size; i++) {
        memcpy_P(
            packet + packet_size,
            g.base_array[g.graphic_lut[i]] + g.graphic_size[i],
            g.graphic_size[i]);
        packet_size += g.graphic_size[i] + 2;
    }
    ssd1306_data(display, packet, packet_size - 2);
}

uint8_t ui_util_graphic_16px_pixel_width(graphic_t graphic)
{
    uint8_t i;
    uint8_t length;

    length = 0;

    for (i = 0; i < graphic.size; i++) {
        length += graphic.graphic_size[i];

        /* For every letter add 1 pixel offset */
        length += 2;
    }

    /* Remove from the last letter the offset */
    length -= 2;

    return length;
}
