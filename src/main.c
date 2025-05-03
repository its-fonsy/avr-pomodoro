#include "main.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#include "button.h"
#include "fsm.h"
#include "gpio.h"
#include "i2c.h"
#include "main.h"
#include "rotary_encoder.h"
#include "ssd1306.h"
#include "timers.h"

button_t button;
rotary_encoder_t re;

int main(void)
{
    system_t sys;
    ssd1306_t display;

    /* Initialize the i2c, button, rotary encoder, TIM 0 and TIM 1 */

    i2c_init(4, 4);
    timer1_init();
    timer0_init();
    gpio_init();

    button_init(&button);
    button.read_pin = &gpio_button_read;

    rotary_encoder_init(&re);
    re.read_pinA = &rot_enc_read_pinA;
    re.read_pinB = &rot_enc_read_pinB;

    /* Activate the interrupts */

    sei();

    /* Initialize the display */

    display.i2c_address = (SSD1306_I2C_ADDRESS << 1);
    display.i2c_write = &i2c_send;

    ssd1306_init(&display);
    ssd1306_clear_screen(&display);
    ssd1306_goto(&display, 0, 0);

    /* Initialize the system FSM */

    sys.state = STATE_INIT;
    sys.display = &display;
    sys.rotary_encoder = &re;
    sys.button = &button;

    // ui_test(display, re);

    while (1) {
        run_state_machine(&sys);
        _delay_ms(5);
    }
}

ISR(TIMER0_COMPA_vect)
{
    button_update(&button);
    rotary_encoder_update(&re);
}

ISR(TIMER1_COMPA_vect)
{
}
