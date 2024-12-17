#include <avr/io.h>
#include <util/delay.h>

#include "hal.h"

#define LED_PIN   PB5
#define LED_PORT  PORTB
#define LED_DDR   DDRB

#define BUTTON_PIN  PB0
#define BUTTON_PORT PORTB
#define BUTTON_INPUT_PORT PINB
#define BUTTON_DDR  DDRB

int main(void)
{

  /* Set LED as output */

  set_pin(LED_DDR, LED_PIN);

  /* Set BUTTON as input using pull-up resistor */

  reset_pin(BUTTON_DDR, BUTTON_PIN);
  set_pin(BUTTON_PORT, BUTTON_PIN);

	while(1)
	{

    if (pin_is_low(BUTTON_INPUT_PORT, BUTTON_PIN))
      toggle_pin(LED_PORT, LED_PIN);

    _delay_ms(100);

	}
}
