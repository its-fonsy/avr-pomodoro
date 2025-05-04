#include "fsm.h"
#include "button.h"
#include "rotary_encoder.h"
#include "ui/homepage.h"

void (*p_state_function_array[])(system_t* sys) = {
    [STATE_INIT] = state_function_init,
    [STATE_DRAW_HOMEPAGE] = state_function_draw_homepage,
    [STATE_HOMEPAGE_IDLE] = state_function_homepage_idle,
    [STATE_DRAW_HOMEPAGE_SELECT_START] = state_function_draw_homepage_sel_start,
    [STATE_DRAW_HOMEPAGE_SELECT_SET] = state_function_draw_homepage_sel_set,
    [STATE_SET_WORK_MIN] = state_function_set_work_min,
    [STATE_SET_WORK_SEC] = state_function_set_work_sec,
    [STATE_SET_PAUSE_MIN] = state_function_set_pause_min,
    [STATE_SET_PAUSE_SEC] = state_function_set_pause_sec
};

void run_state_machine(system_t* sys)
{
    (*p_state_function_array[sys->state])(sys);
}

void state_function_init(system_t* sys)
{
    sys->work_timer.min = 25;
    sys->work_timer.sec = 0;
    sys->pause_timer.min = 5;
    sys->pause_timer.sec = 0;

    sys->tick = 0;
    sys->state = STATE_DRAW_HOMEPAGE;
    sys->selection = SEL_NONE;
}

void state_function_draw_homepage(system_t* sys)
{
    sys->state = STATE_DRAW_HOMEPAGE_SELECT_START;

    ui_homepage_draw_words(sys->display);

    ui_homepage_draw_work_min(sys->display, sys->work_timer.min);
    ui_homepage_draw_work_sec(sys->display, sys->work_timer.sec);

    ui_homepage_draw_timers_dots(sys->display);

    ui_homepage_draw_pause_min(sys->display, sys->pause_timer.min);
    ui_homepage_draw_pause_sec(sys->display, sys->pause_timer.sec);
}

void state_function_homepage_idle(system_t* sys)
{
    switch (rotary_encoder_is_turned(sys->rotary_encoder)) {
    case ROTARY_ENCODER_CW:
        sys->state = STATE_DRAW_HOMEPAGE_SELECT_START;
        return;
    case ROTARY_ENCODER_CCW:
        sys->state = STATE_DRAW_HOMEPAGE_SELECT_SET;
        return;
    }

    if (button_is_pressed(sys->button)) {
        switch (sys->selection) {
        case SEL_START:
            sys->state = STATE_DRAW_HOMEPAGE_SELECT_START;
            break;
        case SEL_SET:
            sys->state = STATE_SET_WORK_MIN;
            ui_homepage_clear_right_selectors(sys->display);
            break;
        default:
            sys->state = STATE_DRAW_HOMEPAGE_SELECT_START;
            break;
        }
    }
}

void state_function_draw_homepage_sel_start(system_t* sys)
{
    ui_homepage_clear_right_selectors(sys->display);
    ui_homepage_draw_left_selectors(sys->display);
    sys->state = STATE_HOMEPAGE_IDLE;
    sys->selection = SEL_START;
}

void state_function_draw_homepage_sel_set(system_t* sys)
{
    ui_homepage_draw_right_selectors(sys->display);
    ui_homepage_clear_left_selectors(sys->display);
    sys->state = STATE_HOMEPAGE_IDLE;
    sys->selection = SEL_SET;
}

void state_function_set_work_min(system_t* sys)
{
    /* Increase/Decrease work minutes when turn the rotary encoder */

    switch (rotary_encoder_is_turned(sys->rotary_encoder)) {
    case ROTARY_ENCODER_CW:
        sys->work_timer.min++;
        if (sys->work_timer.min > 59)
            sys->work_timer.min = 59;
        break;
    case ROTARY_ENCODER_CCW:
        sys->work_timer.min--;
        if (sys->work_timer.min < 0)
            sys->work_timer.min = 0;
        break;
    default:
        break;
    }

    /* Work minutes blink */

    if (sys->tick % 2) {
        ui_homepage_draw_work_min(sys->display, sys->work_timer.min);
    } else {
        ui_homepage_clear_work_min(sys->display);
    }

    /* Change state on button press */

    if (button_is_pressed(sys->button)) {
        sys->state = STATE_SET_WORK_SEC;
        ui_homepage_draw_work_min(sys->display, sys->work_timer.min);
    }
}

void state_function_set_work_sec(system_t* sys)
{
    /* Increase/Decrease work seconds when turn the rotary encoder */

    switch (rotary_encoder_is_turned(sys->rotary_encoder)) {
    case ROTARY_ENCODER_CW:
        sys->work_timer.sec++;
        if (sys->work_timer.sec > 59)
            sys->work_timer.sec = 59;
        break;
    case ROTARY_ENCODER_CCW:
        sys->work_timer.sec--;
        if (sys->work_timer.sec < 0)
            sys->work_timer.sec = 0;
        break;
    default:
        break;
    }

    /* Work seconds blink */

    if (sys->tick % 2) {
        ui_homepage_draw_work_sec(sys->display, sys->work_timer.sec);
    } else {
        ui_homepage_clear_work_sec(sys->display);
    }

    /* Change state on button press */

    if (button_is_pressed(sys->button)) {
        sys->state = STATE_SET_PAUSE_MIN;
        ui_homepage_draw_work_sec(sys->display, sys->work_timer.sec);
    }
}

void state_function_set_pause_min(system_t* sys)
{
    /* Update pause minutes when user turn the rotary encoder */

    switch (rotary_encoder_is_turned(sys->rotary_encoder)) {
    case ROTARY_ENCODER_CW:
        sys->pause_timer.min++;
        if (sys->pause_timer.min > 59)
            sys->pause_timer.min = 59;
        break;
    case ROTARY_ENCODER_CCW:
        sys->pause_timer.min--;
        if (sys->pause_timer.min < 0)
            sys->pause_timer.min = 0;
        break;
    default:
        break;
    }

    /* Pause minutes blink */

    if (sys->tick % 2) {
        ui_homepage_draw_pause_min(sys->display, sys->pause_timer.min);
    } else {
        ui_homepage_clear_pause_min(sys->display);
    }

    /* Change state on button press */

    if (button_is_pressed(sys->button)) {
        sys->state = STATE_SET_PAUSE_SEC;
        ui_homepage_draw_pause_min(sys->display, sys->pause_timer.min);
    }
}
void state_function_set_pause_sec(system_t* sys)
{
    /* Update pause seconds when user turn the rotary encoder */

    switch (rotary_encoder_is_turned(sys->rotary_encoder)) {
    case ROTARY_ENCODER_CW:
        sys->pause_timer.sec++;
        if (sys->pause_timer.sec > 59)
            sys->pause_timer.sec = 59;
        break;
    case ROTARY_ENCODER_CCW:
        sys->pause_timer.sec--;
        if (sys->pause_timer.sec < 0)
            sys->pause_timer.sec = 0;
        break;
    default:
        break;
    }

    /* Pause seconds blink */

    if (sys->tick % 2) {
        ui_homepage_draw_pause_sec(sys->display, sys->pause_timer.sec);
    } else {
        ui_homepage_clear_pause_sec(sys->display);
    }

    /* Change state on button press */

    if (button_is_pressed(sys->button)) {
        sys->state = STATE_DRAW_HOMEPAGE_SELECT_START;
        ui_homepage_draw_pause_sec(sys->display, sys->pause_timer.sec);
    }
}
