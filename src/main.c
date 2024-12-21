#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#include "button.h"
#include "hal.h"
#include "i2c.h"
#include "main.h"
#include "ssd1306.h"
#include "ui.h"

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
  ssd1306_clear_screen();

  uint8_t s = 10;
  uint8_t m = 0;

  ui_draw_dots();

  while (1) {

    ui_draw_minutes(m);
    ui_draw_seconds(s);

    s--;

    if (s == 0xff)
    {
      s = 59;
      m--;
      if (m == 0xff){
        set_pin(LED_PORT, LED_PIN);
        while(!is_button_pressed())
          ;
        reset_pin(LED_PORT, LED_PIN);
        m = 2;
      }
    }

    _delay_ms(1000);


  }
}
