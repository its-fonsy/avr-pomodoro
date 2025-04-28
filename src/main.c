#include "main.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#include "button.h"
#include "gpio.h"
#include "i2c.h"
#include "main.h"
#include "ssd1306.h"
#include "timers.h"
#include "ui.h"

uint8_t s = 10;
uint8_t m = 0;
uint8_t frame = 0;
button_t button;

int main(void)
{
    /* Initialize the 2-wire, button, Timer 1 interface */

    i2c_init(4, 4);
    timer1_init();
    timer0_init();
    gpio_init();

    button_init(&button);
    button.read_pin = &gpio_button_read;

    /* Activate the interrupts */

    sei();

    /* Initialize the display */

    ssd1306_init();

    /* Drawing welcome screen and wait for the user to press the button */

    timer1_stop_and_reset();
    timer1_start();
    while (1) {
        ui_draw_welcome();

        button.lock = BUTTON_LOCKED;
        if (button.status == BUTTON_PRESSED) {
            button.status = BUTTON_PRESS_ACK;
            break;
        }
        button.lock = BUTTON_UNLOCKED;
    }

    /* Prepare the variable for WORK timer */

    uint8_t fsm_state = MAIN_FSM_TIMER;
    uint8_t prev_timer_type = TIMER_WORK;
    m = WORK_MINUTES;
    s = WORK_SECONDS;

    /* Reset and start the timer */

    timer1_stop_and_reset();
    timer1_start();

    /* Main loop */

    while (1) {
        switch (fsm_state) {
        case MAIN_FSM_WAIT_FOR_BUTTON:

            ui_draw_wait_for_button(prev_timer_type);

            /* When the user press the button start the WORK/PAUSE timer */

            button.lock = BUTTON_LOCKED;
            if (button.status == BUTTON_PRESSED) {
                button.status = BUTTON_PRESS_ACK;
                timer1_stop_and_reset();
                fsm_state = MAIN_FSM_TIMER;

                switch (prev_timer_type) {
                case TIMER_WORK:
                    m = PAUSE_MINUTES;
                    s = PAUSE_SECONDS;
                    prev_timer_type = TIMER_PAUSE;
                    break;
                case TIMER_PAUSE:
                    m = WORK_MINUTES;
                    s = WORK_SECONDS;
                    prev_timer_type = TIMER_WORK;
                    break;
                }

                ui_draw_timer(m, s);
                timer1_start();
            }
            button.lock = BUTTON_UNLOCKED;

            break;

        case MAIN_FSM_TIMER:

            ui_draw_timer(m, s);

            /* When timer has finished change state */

            if (m >= 0xFA) {
                timer1_stop_and_reset();
                fsm_state = MAIN_FSM_WAIT_FOR_BUTTON;
                ui_draw_wait_for_button(prev_timer_type);
                timer1_start();
            }

            break;
        }
    }
}

ISR(TIMER0_COMPA_vect) { button_update(&button); }

ISR(TIMER1_COMPA_vect)
{
    s--;
    if (s > 250) {
        s = 59;
        m--;
    }

    frame++;
}
