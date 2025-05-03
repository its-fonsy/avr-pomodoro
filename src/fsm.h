#ifndef __FSM_H
#define __FSM_H

#include <stdint.h>

#include "button.h"
#include "rotary_encoder.h"
#include "ssd1306.h"

typedef enum {
    STATE_INIT = 0,
    STATE_DRAW_HOMEPAGE,
    STATE_HOMEPAGE_IDLE,
    STATE_DRAW_HOMEPAGE_SELECT_START,
    STATE_DRAW_HOMEPAGE_SELECT_SET
} fsm_state_t;

typedef struct {
    uint8_t minutes;
    uint8_t seconds;
} timer_t;

typedef struct {
    fsm_state_t state;
    timer_t work_timer;
    timer_t pause_timer;
    button_t* button;
    rotary_encoder_t* rotary_encoder;
    ssd1306_t* display;
} system_t;

void state_function_init(system_t* sys);
void state_function_draw_homepage(system_t* sys);
void state_function_draw_homepage_sel_start(system_t* sys);
void state_function_draw_homepage_sel_set(system_t* sys);
void state_function_homepage_idle(system_t* sys);

void run_state_machine(system_t* sys);

#endif /* __FSM_H */
