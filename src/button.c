#include "button.h"

#include <avr/interrupt.h>
#include <avr/io.h>

#include "hal.h"

/* Private functions declarations */

void timer0_init ();

/* Global variables */

uint8_t button_status_history;
uint8_t button_state = BTN_RELEASED;

/* Private functions definitions */

void
timer0_init ()
{
  /* Configure Timer 1:
   *  - set prescaler to 64;
   *  - enable CTC mode;
   *  - trigger interrupt when timer reach OCR1A value.
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

void
button_init ()
{
  /* Set BUTTON as input using pull-up resistor */

  reset_pin (BUTTON_DDR, BUTTON_PIN);
  set_pin (BUTTON_PORT, BUTTON_PIN);

  /* Initiate the timer */

  timer0_init ();
}

uint8_t
is_button_pressed ()
{
  switch (button_state)
    {
    case BTN_RELEASED:
      if (button_status_history == 0x00)
        {
          button_state = BTN_PRESSED;
          return 1;
        }
      break;

    case BTN_PRESSED:
      if (button_status_history == 0xFF)
        {
          button_state = BTN_RELEASED;
        }
      break;

    default:
      break;
    }

  return 0;
}

ISR (TIMER0_COMPA_vect)
{
  uint8_t button_status;
  button_status = status_pin (BUTTON_INPUT_PORT, BUTTON_PIN);
  button_status_history = (button_status_history << 1) | button_status;
}
