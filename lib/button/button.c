#include "button.h"

#include <avr/interrupt.h>
#include <avr/io.h>

/* Private functions declarations */

void timer0_init(void);

/* Global variables */

uint8_t button_status_history;
uint8_t button_state = BTN_RELEASED;

/* Private functions definitions */

void timer0_init(void)
{
    /* Timer 0 configuration:
     *  - prescaler set to 64;
     *  - CTC mode;
     *  - trigger interrupt when timer reach OCR0A value.
     *
     * In this configuration (cpu @ 16MHz) the timer triggers an interrupt every
     * 400us.
     *
     * The formula to get the interrupt interval is
     *
     *  t = OCR * PRESCALER / F_CPU
     *    = 100 * 64 / 16e6 = 0.0004 s
     *
     */

    OCR0A = 100;
    TIMSK0 = _BV(OCIE0A);
    TCCR0B = _BV(CS01) | _BV(CS00);
    TCCR0A = _BV(WGM01);
}

void button_init(void)
{
    /* Set BUTTON as input using pull-up resistor */

    BUTTON_DDR &= ~(_BV(BUTTON_PIN));
    BUTTON_PORT |= _BV(BUTTON_PIN);

    /* Initiate the timer */

    timer0_init();
}

uint8_t is_button_pressed(void)
{
    switch (button_state) {
    case BTN_RELEASED:
        if (button_status_history == 0x00) {
            button_state = BTN_PRESSED;
            return 1;
        }
        break;

    case BTN_PRESSED:
        if (button_status_history == 0xFF) {
            button_state = BTN_RELEASED;
        }
        break;

    default:
        break;
    }

    return 0;
}

ISR(TIMER0_COMPA_vect)
{
    button_status_history <<= 1;
    button_status_history |= bit_is_set(BUTTON_INPUT_PORT, BUTTON_PIN) ? 0x01 : 0x00;
}
