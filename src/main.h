#ifndef __MAIN_H
#define __MAIN_H

#include <stdint.h>
#define LED_PIN PB5
#define LED_PORT PORTB
#define LED_DDR DDRB

#define WORK_MINUTES 25
#define WORK_SECONDS 0
#define PAUSE_MINUTES 5
#define PAUSE_SECONDS 0

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

void timer1_init(void);
void timer1_start(void);
void timer1_stop_and_reset(void);

#endif /* __MAIN_H */
