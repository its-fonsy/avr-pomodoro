#include <avr/io.h>
#include <avr/interrupt.h>

#include "button.h"
#include "hal.h"

/* Private functions declarations */

void timer_init();

/* Global variables */

uint8_t button_status_history;
uint8_t button_state = BTN_RELEASED;

/* Private functions definitions */

void timer_init()
{
	/* Configure Timer 1:
   *  - set prescaler to 1024;
   *  - enable CTC mode;
   *  - trigger interrupt when timer reach OCR1A value.
   *
   * In this configuration (cpu @ 16MHz) the timer triggers an interrupt every
   * 512us.
   *
   * The formula to get the interrupt interval is
   *  
   *  t = OCR * PRESCALER / F_CPU
   *    = 8 * 1024 / 16e6 = 0.000512 s
   *
   */

	OCR1A = 8;
	TIMSK1 = (1 << OCIE1A);                             
	TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);
}

void button_init()
{
  /* Set BUTTON as input using pull-up resistor */

  reset_pin(BUTTON_DDR, BUTTON_PIN);
  set_pin(BUTTON_PORT, BUTTON_PIN);

  /* Initiate the timer */

  timer_init();
}

uint8_t is_button_pressed()
{
  switch(button_state)
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

ISR(TIMER1_COMPA_vect)
{
  uint8_t button_status;
  button_status = status_pin(BUTTON_INPUT_PORT, BUTTON_PIN);
  button_status_history = (button_status_history << 1) | button_status;
}
