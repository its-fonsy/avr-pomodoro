#include "ui.h"

#include <avr/io.h>
#include <stdint.h>
#include <string.h>

#include "font.h"
#include "main.h"
#include "ssd1306.h"

DisplayContext disp = { 0xFF, 0xFF, UI_CLEAR, 0 };

void ui_draw_minutes(ssd1306_t* dev, uint8_t minutes)
{
    if (minutes == disp.minutes)
        return;

    uint8_t unit;
    uint8_t tens;
    ssd1306_address_boundary_t column;

    disp.minutes = minutes;
    unit = minutes % 10;
    tens = minutes / 10;

    ssd1306_set_page_address_boundary(dev, 0, 3);

    /* Draw tens digit */

    column.start = FONT_MINUTES_X;
    column.end = FONT_MINUTES_X + FONT_20x32_WIDTH - 1;
    ssd1306_set_column_address_boundary(dev, column.start, column.end);
    ssd1306_data(dev, (uint8_t*)font_20x32[tens], sizeof(font_20x32[tens]));

    /* Draw unit digit */

    column.start = FONT_MINUTES_X + FONT_20x32_WIDTH + FONT_OFFSET;
    column.end = FONT_MINUTES_X + FONT_OFFSET + 2 * FONT_20x32_WIDTH - 1;
    ssd1306_set_column_address_boundary(dev, column.start, column.end);
    ssd1306_data(dev, (uint8_t*)font_20x32[unit], sizeof(font_20x32[unit]));
}

void ui_draw_seconds(ssd1306_t* device, uint8_t seconds)
{
    if (seconds == disp.seconds)
        return;

    uint8_t unit;
    uint8_t tens;
    ssd1306_address_boundary_t column;

    disp.seconds = seconds;
    unit = seconds % 10;
    tens = seconds / 10;

    ssd1306_set_page_address_boundary(device, 0, 3);

    /* Draw tens digit */

    column.start = FONT_SECONDS_X;
    column.end = FONT_SECONDS_X + FONT_20x32_WIDTH - 1;
    ssd1306_set_column_address_boundary(device, column.start, column.end);
    ssd1306_data(device, (uint8_t*)font_20x32[tens], sizeof(font_20x32[tens]));

    /* Draw unit digit */

    column.start = FONT_SECONDS_X + FONT_20x32_WIDTH + FONT_OFFSET;
    column.end = FONT_SECONDS_X + FONT_20x32_WIDTH + FONT_OFFSET + FONT_20x32_WIDTH - 1;
    ssd1306_set_column_address_boundary(device, column.start, column.end);
    ssd1306_data(device, (uint8_t*)font_20x32[unit], sizeof(font_20x32[unit]));
}

void ui_draw_dots(ssd1306_t* dev)
{
    uint8_t dot[] = {
        0xE0, 0xE0, 0xE0, 0xE0, 0xE0,
        0x03, 0x03, 0x03, 0x03, 0x03
    };

    ssd1306_address_boundary_t column;

    ssd1306_set_page_address_boundary(dev, 0, 1);

    column.start = FONT_DOTS_X;
    column.end = FONT_DOTS_X + FONT_DOT_WIDTH - 1;
    ssd1306_set_column_address_boundary(dev, column.start, column.end);
    ssd1306_data(dev, dot, sizeof(dot));

    ssd1306_set_page_address_boundary(dev, 2, 3);

    column.start = FONT_DOTS_X;
    column.end = FONT_DOTS_X + FONT_DOT_WIDTH - 1;
    ssd1306_set_column_address_boundary(dev, column.start, column.end);
    ssd1306_data(dev, dot, sizeof(dot));
}

void ui_draw_timer(ssd1306_t* dev, uint8_t minutes, uint8_t seconds)
{
    if (disp.drawn != UI_TIMER) {
        ssd1306_clear_screen(dev);
        ui_draw_dots(dev);
        disp.drawn = UI_TIMER;
        disp.minutes = 0xFF;
        disp.seconds = 0xFF;
    }

    ui_draw_minutes(dev, minutes);
    ui_draw_seconds(dev, seconds);
}

void ui_print_centered(ssd1306_t* dev, const char* str)
{
    uint8_t len;
    uint8_t start;
    uint8_t c;
    uint8_t i;
    ssd1306_address_boundary_t column;

    /* Compute start offset */

    len = strlen(str);
    start = (DISPLAY_WIDTH - (len * FONT_8x16_WIDTH + (len - 1) * FONT_8x16_OFFSET)) / 2;

    for (i = 0; i < len; i++) {
        column.start = start + i * (FONT_8x16_WIDTH + FONT_8x16_OFFSET);
        column.end = start + i * (FONT_8x16_WIDTH + FONT_8x16_OFFSET) + (FONT_8x16_WIDTH - 1);
        ssd1306_set_column_address_boundary(dev, column.start, column.end);

        /* Space character */

        if (str[i] == 32)
            continue;

        /* Print character */

        c = str[i] - 65;
        ssd1306_data(dev, (uint8_t*)font_8x16[c], sizeof(font_8x16[c]));
    }
}

void ui_draw_wait_for_button(ssd1306_t* dev, uint8_t prev_state)
{
    if (disp.drawn != UI_WAIT_FOR_BUTTON) {
        disp.drawn = UI_WAIT_FOR_BUTTON;
        disp.fsm_state = UI_FSM_WAIT4BUTTON_TIMER_ELAPSED;
        goto wait_for_button_fsm;
    }

    if ((disp.frame == frame) || !(frame % 2))
        return;

wait_for_button_fsm:
    disp.frame = frame;
    switch (disp.fsm_state) {
    case UI_FSM_WAIT4BUTTON_TIMER_ELAPSED:
        ssd1306_clear_screen(dev);

        ssd1306_set_page_address_boundary(dev, 0, 1);
        switch (prev_state) {
        case TIMER_WORK:
            ui_print_centered(dev, "WORK TIMER");
            break;
        case TIMER_PAUSE:
            ui_print_centered(dev, "PAUSE TIMER");
            break;
        }
        ssd1306_set_page_address_boundary(dev, 2, 3);
        ui_print_centered(dev, "ELAPSED");

        disp.fsm_state = UI_FSM_WAIT4BUTTON_PRESS_THE_BUTTON;
        break;

    case UI_FSM_WAIT4BUTTON_PRESS_THE_BUTTON:
        ssd1306_clear_screen(dev);

        ssd1306_set_page_address_boundary(dev, 0, 1);
        ui_print_centered(dev, "PRESS THE");

        ssd1306_set_page_address_boundary(dev, 2, 3);
        ui_print_centered(dev, "BUTTON");

        disp.fsm_state = UI_FSM_WAIT4BUTTON_TO_START_TIMER;
        break;

    case UI_FSM_WAIT4BUTTON_TO_START_TIMER:
        ssd1306_clear_screen(dev);

        ssd1306_set_page_address_boundary(dev, 0, 1);
        ui_print_centered(dev, "TO START");

        ssd1306_set_page_address_boundary(dev, 2, 3);
        switch (prev_state) {
        case TIMER_WORK:
            ui_print_centered(dev, "PAUSE TIMER");
            break;
        case TIMER_PAUSE:
            ui_print_centered(dev, "WORK TIMER");
            break;
        }

        disp.fsm_state = UI_FSM_WAIT4BUTTON_TIMER_ELAPSED;
        break;
    }
}

void ui_draw_welcome(ssd1306_t* dev)
{
    if (disp.drawn != UI_WELCOME) {
        disp.drawn = UI_WELCOME;
        disp.fsm_state = UI_FSM_WELCOME_FRAME_PRESS_THE_BUTTON;
        goto welcome_fsm;
    }

    if ((disp.frame == frame) || !(frame % 2))
        return;

welcome_fsm:
    disp.frame = frame;
    switch (disp.fsm_state) {
    case UI_FSM_WELCOME_FRAME_PRESS_THE_BUTTON:
        ssd1306_clear_screen(dev);

        ssd1306_set_page_address_boundary(dev, 0, 1);
        ui_print_centered(dev, "PRESS THE");

        ssd1306_set_page_address_boundary(dev, 2, 3);
        ui_print_centered(dev, "BUTTON");

        ssd1306_set_page_address_boundary(dev, 0, 1);
        ui_print_centered(dev, "PRESS THE");

        ssd1306_set_page_address_boundary(dev, 2, 3);
        ui_print_centered(dev, "BUTTON");

        disp.fsm_state = UI_FSM_WELCOME_FRAME_TO_START_WORK_TIMER;

        break;

    case UI_FSM_WELCOME_FRAME_TO_START_WORK_TIMER:
        ssd1306_clear_screen(dev);

        ssd1306_set_page_address_boundary(dev, 0, 1);
        ui_print_centered(dev, "TO START");

        ssd1306_set_page_address_boundary(dev, 2, 3);
        ui_print_centered(dev, "WORK TIMER");
        disp.fsm_state = UI_FSM_WELCOME_FRAME_PRESS_THE_BUTTON;
        break;
    }
}
