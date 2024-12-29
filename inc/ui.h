#ifndef __UI_H
#define __UI_H

#include "font.h"
#include <stdint.h>

#define FONT_8x16_OFFSET 2
#define FONT_DOT_WIDTH 5
#define FONT_OFFSET 4
#define FONT_MINUTES_X 9
#define FONT_DOTS_X FONT_MINUTES_X + 2 * FONT_20x32_WIDTH + 3 * FONT_OFFSET
#define FONT_SECONDS_X FONT_DOTS_X + FONT_DOT_WIDTH + 2*FONT_OFFSET

/* Screen drawn on the OLED */

enum
{
  UI_CLEAR = 5,
  UI_WELCOME,
  UI_TIMER,
  UI_WAIT_FOR_BUTTON,
};

/* FSM states when drawing WELCOME screen */

enum
{
  UI_FSM_WELCOME_FRAME_PRESS_THE_BUTTON = 10,
  UI_FSM_WELCOME_FRAME_TO_START_WORK_TIMER,
};

/* FSM states when drawing WAIT_FOR_BUTTON screen */

enum
{
  UI_FSM_WAIT4BUTTON_TIMER_ELAPSED = 20,
  UI_FSM_WAIT4BUTTON_PRESS_THE_BUTTON,
  UI_FSM_WAIT4BUTTON_TO_START_TIMER,
};

typedef struct DisplayContext
{
  uint8_t minutes;
  uint8_t seconds;
  uint8_t drawn;
  uint8_t frame;
  uint8_t fsm_state;
} DisplayContext;

void ui_draw_minutes (uint8_t minutes);
void ui_draw_seconds (uint8_t seconds);
void ui_draw_dots ();

void ui_draw_work_timer_elapsed ();

void ui_draw_timer (uint8_t minutes, uint8_t seconds);
void ui_print_centered (const char *str);
void ui_draw_wait_for_button (uint8_t prev_state);
void ui_draw_welcome ();

#endif /* __UI_H */
