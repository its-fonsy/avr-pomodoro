#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include "button.h"
#include "hal.h"
#include "i2c.h"
#include "main.h"
#include "ssd1306.h"

int main(void) {

  /* Set onboard LED as output */

  set_pin(LED_DDR, LED_PIN);
  reset_pin(LED_PORT, LED_PIN);

  /* Init the 2-wire interface */

  i2c_init(4, 4);

  /* Configure the button */

  button_init();

  /* Activate the interrupts */

  sei();

  ssd1306_init();

  uint8_t data[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

  while (1) {

    /* Send the data vector to test the driver */

    ssd1306_write_gddram(data, 5);

    _delay_ms(100);
  }
}
