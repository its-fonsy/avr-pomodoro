#include "fsm.h"
#include "button.h"
#include "rotary_encoder.h"
#include "ssd1306.h"
#include "timers.h"
#include "ui/homepage.h"
#include "ui/pages.h"
#include "ui/timer.h"

#include <avr/eeprom.h>

timer_t tim;
timer_t eeprom_work_tim EEMEM;
timer_t eeprom_pause_tim EEMEM;

void (*p_state_function_array[])(system_t* sys) = {
    [STATE_INIT] = state_function_init,
    [STATE_DRAW_HOMEPAGE] = state_function_draw_homepage,
    [STATE_HOMEPAGE_IDLE] = state_function_homepage_idle,
    [STATE_DRAW_HOMEPAGE_SELECT_START] = state_function_draw_homepage_sel_start,
    [STATE_DRAW_HOMEPAGE_SELECT_SET] = state_function_draw_homepage_sel_set,
    [STATE_SET_WORK_MIN] = state_function_set_work_min,
    [STATE_SET_WORK_SEC] = state_function_set_work_sec,
    [STATE_SET_PAUSE_MIN] = state_function_set_pause_min,
    [STATE_SET_PAUSE_SEC] = state_function_set_pause_sec,
    [STATE_WORK_TIMER] = state_function_work_timer,
    [STATE_WORK_FINISHED] = state_function_work_finished,
    [STATE_PAUSE_TIMER] = state_function_pause_timer,
    [STATE_PAUSE_FINISHED_IDLE] = state_function_pause_finished_idle,
    [STATE_PAUSE_FINISHED_SEL_RESTART] = state_function_pause_finished_sel_restart,
    [STATE_PAUSE_FINISHED_SEL_SET_TIMER] = state_function_pause_finished_sel_set_timer
};

void run_state_machine(system_t* sys)
{
    (*p_state_function_array[sys->state])(sys);
}

void state_function_init(system_t* sys)
{
    eeprom_read_block(&(sys->work_timer), &(eeprom_work_tim), sizeof(timer_t));
    eeprom_read_block(&(sys->pause_timer), &(eeprom_pause_tim), sizeof(timer_t));
    sys->tick = 0;
    sys->state = STATE_DRAW_HOMEPAGE;
    sys->selection = SEL_NONE;
}

void state_function_draw_homepage(system_t* sys)
{
    sys->state = STATE_DRAW_HOMEPAGE_SELECT_START;
    ui_homepage_draw(sys->display, sys->work_timer, sys->pause_timer);
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
        case SEL_HOMEPAGE_START:
            sys->state = STATE_WORK_TIMER;
            setup_sys_for_timer_countdown(sys, sys->work_timer);
            break;
        case SEL_HOMEPAGE_SET:
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
    sys->selection = SEL_HOMEPAGE_START;
}

void state_function_draw_homepage_sel_set(system_t* sys)
{
    ui_homepage_draw_right_selectors(sys->display);
    ui_homepage_clear_left_selectors(sys->display);
    sys->state = STATE_HOMEPAGE_IDLE;
    sys->selection = SEL_HOMEPAGE_SET;
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
        eeprom_update_block(&(sys->pause_timer), &eeprom_pause_tim, sizeof(timer_t));
        eeprom_update_block(&(sys->work_timer), &eeprom_work_tim, sizeof(timer_t));
    }
}

void state_function_work_timer(system_t* sys)
{
    static uint8_t tk = 0;

    /* Return if one second is not elapsed */

    if (sys->tick % 5 || tk == sys->tick)
        return;

    /* Update timer minute and second */

    tk = sys->tick;

    tim.sec--;
    if (tim.sec < 0) {
        tim.sec = 59;
        tim.min--;
    }

    if (tim.min < 0) {
        sys->state = STATE_WORK_FINISHED;
        tk = 0;
        button_reset(sys->button);
        ssd1306_clear_screen(sys->display);
        ui_page_draw_work_finished(sys->display);
        return;
    }

    ui_timer_draw_timer(sys->display, tim.min, tim.sec);
}

void state_function_work_finished(system_t* sys)
{
    if (button_is_pressed(sys->button)) {
        timer1_stop_and_reset();
        sys->state = STATE_PAUSE_TIMER;
        sys->tick = 0;
        tim.min = sys->pause_timer.min;
        tim.sec = sys->pause_timer.sec;
        ssd1306_clear_screen(sys->display);
        ui_timer_draw_timer(sys->display, tim.min, tim.sec);
        ui_timer_draw_dots(sys->display);
        timer1_start();
    }
}

void state_function_pause_timer(system_t* sys)
{
    static uint8_t tk = 0;

    /* Return if one second is not elapsed */

    if (sys->tick % 5 || tk == sys->tick)
        return;

    /* Update timer minute and second */

    tk = sys->tick;

    tim.sec--;
    if (tim.sec < 0) {
        tim.sec = 59;
        tim.min--;
    }

    if (tim.min < 0) {
        sys->state = STATE_PAUSE_FINISHED_SEL_RESTART;
        tk = 0;
        ssd1306_clear_screen(sys->display);
        button_reset(sys->button);
        ui_page_draw_pause_finished(sys->display);
        return;
    }

    ui_timer_draw_timer(sys->display, tim.min, tim.sec);
}

void state_function_pause_finished_idle(system_t* sys)
{
    switch (rotary_encoder_is_turned(sys->rotary_encoder)) {
    case ROTARY_ENCODER_CW:
        sys->state = STATE_PAUSE_FINISHED_SEL_RESTART;
        return;
    case ROTARY_ENCODER_CCW:
        sys->state = STATE_PAUSE_FINISHED_SEL_SET_TIMER;
        return;
    }

    if (button_is_pressed(sys->button)) {
        switch (sys->selection) {
        case SEL_PAUSE_FINISHED_SET_TIMER:
            sys->state = STATE_SET_WORK_MIN;
            ssd1306_clear_screen(sys->display);
            ui_homepage_draw(sys->display, sys->work_timer, sys->pause_timer);
            break;
        case SEL_PAUSE_FINISHED_REPEAT:
            sys->state = STATE_WORK_TIMER;
            setup_sys_for_timer_countdown(sys, sys->work_timer);
            break;
        default:
            sys->state = STATE_DRAW_HOMEPAGE;
            ssd1306_clear_screen(sys->display);
            break;
        }
    }
}

void state_function_pause_finished_sel_restart(system_t* sys)
{
    ui_page_clear_right_selectors(sys->display);
    ui_page_draw_left_selectors(sys->display);
    sys->state = STATE_PAUSE_FINISHED_IDLE;
    sys->selection = SEL_PAUSE_FINISHED_REPEAT;
}

void state_function_pause_finished_sel_set_timer(system_t* sys)
{
    ui_page_clear_left_selectors(sys->display);
    ui_page_draw_right_selectors(sys->display);
    sys->state = STATE_PAUSE_FINISHED_IDLE;
    sys->selection = SEL_PAUSE_FINISHED_SET_TIMER;
}

void setup_sys_for_timer_countdown(system_t* sys, timer_t timer)
{
    timer1_stop_and_reset();
    sys->tick = 0;
    tim = timer;
    ssd1306_clear_screen(sys->display);
    ui_timer_draw_timer(sys->display, tim.min, tim.sec);
    ui_timer_draw_dots(sys->display);
    timer1_start();
}
