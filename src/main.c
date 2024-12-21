#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#include "main.h"
#include "button.h"
#include "hal.h"
#include "i2c.h"
#include "main.h"
#include "ssd1306.h"
#include "ui.h"

uint8_t s = 10;
uint8_t m = 0;

int main(void) {

  /* Set onboard LED as output */

  set_pin(LED_DDR, LED_PIN);
  reset_pin(LED_PORT, LED_PIN);

  /* Init the 2-wire interface */

  i2c_init(4, 4);

  /* Configure the button */

  button_init();

  /* Timer 1 init */

  timer1_init();

  /* Activate the interrupts */

  sei();

  /* Initialize the display */

  ssd1306_init();
  ssd1306_clear_screen();

  uint8_t fsm_state = WAIT_FOR_BUTTON;
  uint8_t fsm_prev = PAUSE;

  while (1) {

    switch(fsm_state)
    {
      case WAIT_FOR_BUTTON:
        ssd1306_clear_screen();
        timer1_stop();
        if (is_button_pressed())
        {
          fsm_state = (fsm_prev == WORK) ? PAUSE : WORK;
          m = (fsm_prev == WORK) ? 0 : 0;
          s = (fsm_prev == WORK) ? 5 : 10;
          ui_update_clock(m, s);
          timer1_start();
        }
        break;

      case WORK:
        ui_update_clock(m, s);
        fsm_prev = WORK;
        if (m >= 250)
          fsm_state = WAIT_FOR_BUTTON;
        break;

      case PAUSE:
        ui_update_clock(m, s);
        fsm_prev = PAUSE;
        if (m >= 250)
          fsm_state = WAIT_FOR_BUTTON;
        break;
    }

  }
}

void timer1_init()
{
	OCR1A = 15625;
	TIMSK1 = (1 << OCIE1A);                             
}

void timer1_start()
{
  TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);
}

void timer1_stop()
{
  TCCR1B = 0x00;
}

ISR(TIMER1_COMPA_vect)
{
  s--;
  if (s > 250)
  {
    s = 59;
    m--;
  }
}
