#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "hal.h"
#include "i2c.h"
#include "button.h"
#include "main.h"

int main(void)
{

  /* Set onboard LED as output */

  set_pin(LED_DDR, LED_PIN);
  reset_pin(LED_PORT, LED_PIN);

  /* Init the 2-wire interface */

  i2c_init(4, 4);

  /* Configure the button */

  button_init();

  /* Activate the interrupts */

  sei();

  uint8_t data[5] = { 0, 1, 2, 3, 4 };

	while(1)
    {
      /* Send the data vector to test the driver */

      i2c_send(0x3c, data, 5);
      _delay_ms(1000);
    }
}
