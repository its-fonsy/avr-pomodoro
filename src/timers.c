#include "timers.h"

#include <avr/io.h>

/* Timer 1 configuration:
 *  - prescaler set to 256;
 *  - CTC mode;
 *  - trigger interrupt when timer reach OCR1A value.
 *
 * In this configuration (cpu @ 16MHz) the timer triggers an interrupt every
 * 16us.
 *
 * With OCR1A set to 12500 the timer ticks every 200ms.
 */

void timer1_init(void)
{
    OCR1A = 12500;
    TIMSK1 = (1 << OCIE1A);
}

void timer1_start(void)
{
    /* Set prescaler CTC mode and prescaler to 64.
     * When the prescaler is set, the timer start counting. */

    TCCR1B = (1 << WGM12) | (1 << CS12);
}

void timer1_stop_and_reset(void)
{
    /* Set timer prescaler to 0 to stop the timer */

    TCCR1B = 0x00;

    /* Zero the timer counter */

    TCNT1 = 0x00;
}

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
    TIMSK0 = (1 << OCIE0A);
    TCCR0B = (1 << CS01) | (1 << CS00);
    TCCR0A = (1 << WGM01);
}
