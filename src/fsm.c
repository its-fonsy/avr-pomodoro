#include "fsm.h"
#include "button.h"
#include "rotary_encoder.h"
#include "ui.h"

void (*p_state_function_array[])(system_t* sys) = {
    [STATE_INIT] = state_function_init,
    [STATE_DRAW_HOMEPAGE] = state_function_draw_homepage,
    [STATE_HOMEPAGE_IDLE] = state_function_homepage_idle,
    [STATE_DRAW_HOMEPAGE_SELECT_START] = state_function_draw_homepage_sel_start,
    [STATE_DRAW_HOMEPAGE_SELECT_SET] = state_function_draw_homepage_sel_set
};

void run_state_machine(system_t* sys)
{
    (*p_state_function_array[sys->state])(sys);
}

void state_function_init(system_t* sys)
{
    sys->work_timer.minutes = 25;
    sys->work_timer.seconds = 0;
    sys->pause_timer.minutes = 5;
    sys->pause_timer.seconds = 0;

    sys->state = STATE_DRAW_HOMEPAGE;
}

void state_function_draw_homepage(system_t* sys)
{
    sys->state = STATE_DRAW_HOMEPAGE_SELECT_START;

    ui_draw_homepage_words(sys->display);

    ui_draw_homepage_work_min(sys->display, sys->work_timer.minutes);
    ui_draw_homepage_work_sec(sys->display, sys->work_timer.seconds);

    ui_draw_homepage_timers_dots(sys->display);

    ui_draw_homepage_pause_min(sys->display, sys->pause_timer.minutes);
    ui_draw_homepage_pause_sec(sys->display, sys->pause_timer.seconds);
}

void state_function_homepage_idle(system_t* sys)
{
    switch (rotary_encoder_is_turned(sys->rotary_encoder)) {
    case ROTARY_ENCODER_CW:
        sys->state = STATE_DRAW_HOMEPAGE_SELECT_START;
        break;
    case ROTARY_ENCODER_CCW:
        sys->state = STATE_DRAW_HOMEPAGE_SELECT_SET;
        break;
    }
}

void state_function_draw_homepage_sel_start(system_t* sys)
{
    ui_clear_right_selectors(sys->display);
    ui_draw_left_selectors(sys->display);
    sys->state = STATE_HOMEPAGE_IDLE;
}

void state_function_draw_homepage_sel_set(system_t* sys)
{
    ui_draw_right_selectors(sys->display);
    ui_clear_left_selectors(sys->display);
    sys->state = STATE_HOMEPAGE_IDLE;
}
