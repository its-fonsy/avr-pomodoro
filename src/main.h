#ifndef __MAIN_H
#define __MAIN_H

#include "button.h"
#include <stdint.h>

#define LED_PIN PB5
#define LED_PORT PORTB
#define LED_DDR DDRB

#define WORK_MINUTES 0
#define WORK_SECONDS 5
#define PAUSE_MINUTES 0
#define PAUSE_SECONDS 2

/* Main FSM states */

enum {
    MAIN_FSM_WAIT_FOR_BUTTON = 40,
    MAIN_FSM_TIMER,
};

/* Timer types */

enum {
    TIMER_WORK = 30,
    TIMER_PAUSE,
};

extern uint8_t frame;
extern uint8_t s;
extern uint8_t m;

#endif /* __MAIN_H */
