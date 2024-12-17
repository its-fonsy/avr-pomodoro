#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "hal.h"
#include "button.h"

#define LED_PIN   PB5
#define LED_PORT  PORTB
#define LED_DDR   DDRB

int main(void)
{

  /* Set LED as output */

  set_pin(LED_DDR, LED_PIN);

  /* Configure the button */

  button_init();

  /* Activate the interrupts */

  sei();

	while(1)
	{

    if (is_button_pressed())
      {
        toggle_pin(LED_PORT, LED_PIN);
      }

	}
}
