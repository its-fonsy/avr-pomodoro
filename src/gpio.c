#include <avr/io.h>
#include <stdint.h>

#include "gpio.h"

void gpio_init(void)
{
    /* Button initialization */
    DDRB &= ~(_BV(BUTTON_PIN));
    PORTB |= _BV(BUTTON_PIN);
}

uint8_t gpio_button_read(void)
{
    return bit_is_set(BUTTON_PORT, BUTTON_PIN) ? 0x01 : 0x00;
}
