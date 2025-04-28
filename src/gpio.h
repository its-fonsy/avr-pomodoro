#ifndef __GPIO_H
#define __GPIO_H

#include <stdint.h>

#define BUTTON_PIN PB4
#define BUTTON_PORT PINB

void gpio_init(void);
uint8_t gpio_button_read(void);

#endif /* __GPIO_H */
