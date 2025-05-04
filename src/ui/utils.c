#include "utils.h"

#include <avr/io.h>
#include <stdint.h>
#include <string.h>

#include <util/delay.h>

#include "../ssd1306.h"
#include "font.h"

graphic_t ui_util_number_to_graphic(uint8_t n)
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

void ui_util_draw_graphic_one_line(ssd1306_t* display, graphic_t g)
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

void ui_util_draw_graphic_between_two_lines(ssd1306_t* display, graphic_t g)
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

uint8_t ui_util_graphic_pixel_width(graphic_t graphic)
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
