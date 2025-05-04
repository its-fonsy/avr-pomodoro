#include "timer.h"
#include "font.h"

void ui_timer_draw_minutes(ssd1306_t* display, uint8_t minute)
{
    uint8_t unit;
    uint8_t tens;
    ssd1306_address_boundary_t column;

    unit = minute % 10;
    tens = minute / 10;

    ssd1306_set_page_address_boundary(display, 0, 3);

    /* Draw MSB */

    column.start = FONT_MINUTES_X;
    column.end = FONT_MINUTES_X + FONT_20x32_WIDTH - 1;
    ssd1306_set_column_address_boundary(display, column.start, column.end);
    ssd1306_data(display, (uint8_t*)number_20x32[tens], sizeof(number_20x32[tens]));

    /* Draw LSB */

    column.start = FONT_MINUTES_X + FONT_20x32_WIDTH + FONT_OFFSET;
    column.end = FONT_MINUTES_X + FONT_OFFSET + 2 * FONT_20x32_WIDTH - 1;
    ssd1306_set_column_address_boundary(display, column.start, column.end);
    ssd1306_data(display, (uint8_t*)number_20x32[unit], sizeof(number_20x32[unit]));
}

void ui_timer_draw_seconds(ssd1306_t* display, uint8_t second)
{

    uint8_t unit;
    uint8_t tens;
    ssd1306_address_boundary_t column;

    unit = second % 10;
    tens = second / 10;

    ssd1306_set_page_address_boundary(display, 0, 3);

    /* Draw tens digit */

    column.start = FONT_SECONDS_X;
    column.end = FONT_SECONDS_X + FONT_20x32_WIDTH - 1;
    ssd1306_set_column_address_boundary(display, column.start, column.end);
    ssd1306_data(display, (uint8_t*)number_20x32[tens], sizeof(number_20x32[tens]));

    /* Draw unit digit */

    column.start = FONT_SECONDS_X + FONT_20x32_WIDTH + FONT_OFFSET;
    column.end = FONT_SECONDS_X + FONT_20x32_WIDTH + FONT_OFFSET + FONT_20x32_WIDTH - 1;
    ssd1306_set_column_address_boundary(display, column.start, column.end);
    ssd1306_data(display, (uint8_t*)number_20x32[unit], sizeof(number_20x32[unit]));
}

void ui_timer_draw_dots(ssd1306_t* display)
{
    ssd1306_address_boundary_t column;

    ssd1306_set_page_address_boundary(display, 0, 1);

    column.start = FONT_DOTS_X;
    column.end = FONT_DOTS_X + FONT_DOT_WIDTH - 1;
    ssd1306_set_column_address_boundary(display, column.start, column.end);
    ssd1306_data(display, (uint8_t*)timer_dot, sizeof(timer_dot));

    ssd1306_set_page_address_boundary(display, 2, 3);

    column.start = FONT_DOTS_X;
    column.end = FONT_DOTS_X + FONT_DOT_WIDTH - 1;
    ssd1306_set_column_address_boundary(display, column.start, column.end);
    ssd1306_data(display, (uint8_t*)timer_dot, sizeof(timer_dot));
}

void ui_timer_draw_timer(ssd1306_t* display, uint8_t minute, uint8_t second)
{
    ui_timer_draw_minutes(display, minute);
    ui_timer_draw_seconds(display, second);
}
