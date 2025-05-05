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
    STATE_DRAW_HOMEPAGE_SELECT_SET,
    STATE_SET_WORK_MIN,
    STATE_SET_WORK_SEC,
    STATE_SET_PAUSE_MIN,
    STATE_SET_PAUSE_SEC,
    STATE_WORK_TIMER,
    STATE_WORK_FINISHED,
    STATE_PAUSE_TIMER,
    STATE_PAUSE_FINISHED_IDLE,
    STATE_PAUSE_FINISHED_SEL_RESTART,
    STATE_PAUSE_FINISHED_SEL_SET_TIMER,
} fsm_state_t;

typedef enum {
    SEL_NONE = 0,
    SEL_HOMEPAGE_START,
    SEL_HOMEPAGE_SET,
    SEL_PAUSE_FINISHED_RESTART,
    SEL_PAUSE_FINISHED_SET_TIMER,
} selection_t;

typedef struct {
    int8_t min;
    int8_t sec;
} timer_t;

typedef struct {
    fsm_state_t state;
    selection_t selection;
    timer_t work_timer;
    timer_t pause_timer;
    uint8_t tick;
    button_t* button;
    rotary_encoder_t* rotary_encoder;
    ssd1306_t* display;
} system_t;

void state_function_init(system_t* sys);

void state_function_draw_homepage(system_t* sys);
void state_function_draw_homepage_sel_start(system_t* sys);
void state_function_draw_homepage_sel_set(system_t* sys);
void state_function_homepage_idle(system_t* sys);

void state_function_set_work_min(system_t* sys);
void state_function_set_work_sec(system_t* sys);
void state_function_set_pause_min(system_t* sys);
void state_function_set_pause_sec(system_t* sys);

void state_function_work_timer(system_t* sys);
void state_function_work_finished(system_t* sys);
void state_function_pause_timer(system_t* sys);
void state_function_pause_finished_idle(system_t* sys);
void state_function_pause_finished_sel_restart(system_t* sys);
void state_function_pause_finished_sel_set_timer(system_t* sys);

void run_state_machine(system_t* sys);

#endif /* __FSM_H */
