#include "main.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#include "button.h"
#include "font.h"
#include "gpio.h"
#include "i2c.h"
#include "main.h"
#include "ssd1306.h"
#include "timers.h"
#include "ui.h"

button_t button;

int main(void)
{
    /* Initialize the 2-wire, button, Timer 1 interface */

    i2c_init(4, 4);
    timer1_init();
    timer0_init();
    gpio_init();

    button_init(&button);
    button.read_pin = &gpio_button_read;

    /* Activate the interrupts */

    sei();

    /* Initialize the display */

    ssd1306_t display;
    display.i2c_address = (SSD1306_I2C_ADDRESS << 1);
    display.i2c_write = &i2c_send;
    ssd1306_init(&display);

    ssd1306_clear_screen(&display);
    ssd1306_goto(&display, 0, 0);

    ui_test(&display);

    while (1) {
    }
}

ISR(TIMER0_COMPA_vect)
{
    button_update(&button);
}

ISR(TIMER1_COMPA_vect)
{
}
