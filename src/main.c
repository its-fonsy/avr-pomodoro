#include "main.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#include "button.h"
#include "i2c.h"
#include "main.h"
#include "ssd1306.h"
#include "ui.h"

uint8_t s = 10;
uint8_t m = 0;
uint8_t frame = 0;

int main(void)
{
    /* Initialize the 2-wire, button, Timer 1 interface */

    i2c_init(4, 4);
    button_init();
    timer1_init();

    /* Activate the interrupts */

    sei();

    /* Initialize the display */

    ssd1306_init();

    /* Drawing welcome screen and wait for the user to press the button */

    timer1_start();
    while (1) {
        ui_draw_welcome();
        if (is_button_pressed())
            break;
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

            if (is_button_pressed()) {
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

/* Timer 1 configuration:
 *  - prescaler set to 256;
 *  - CTC mode;
 *  - trigger interrupt when timer reach OCR1A value.
 *
 * In this configuration (cpu @ 16MHz) the timer triggers an interrupt every
 * 16us.
 *
 * With OCR1A set to 62500 the timer ticks every 1s.
 */

void timer1_init()
{
    OCR1A = 62500;
    TIMSK1 = (1 << OCIE1A);
}

void timer1_start()
{
    /* Set prescaler CTC mode and prescaler to 64.
     * When the prescaler is set, the timer start counting. */

    TCCR1B = (1 << WGM12) | (1 << CS12);
}

void timer1_stop_and_reset()
{
    /* Set timer prescaler to 0 to stop the timer */

    TCCR1B = 0x00;

    /* Zero the timer counter */

    TCNT1 = 0x00;

    /* Reset the frame counter */

    frame = 0;
}

ISR(TIMER1_COMPA_vect)
{
    s--;
    if (s > 250) {
        s = 59;
        m--;
    }

    frame++;
}
