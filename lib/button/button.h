#ifndef __BUTTON_H
#define __BUTTON_H

#include <stdint.h>

#define BUTTON_PIN PB0
#define BUTTON_PORT PORTB
#define BUTTON_INPUT_PORT PINB
#define BUTTON_DDR DDRB

typedef enum ButtonState
{
  BTN_RELEASED,
  BTN_PRESSED,
} ButtonState;

/* Public functions */

uint8_t is_button_pressed ();
void button_init ();

#endif /* __BUTTON_H */
