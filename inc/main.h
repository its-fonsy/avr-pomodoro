#ifndef __MAIN_H
#define __MAIN_H

#define LED_PIN   PB5
#define LED_PORT  PORTB
#define LED_DDR   DDRB

enum FSM_STATES {
  WAIT_FOR_BUTTON = 0,
  WORK,
  PAUSE
};

void timer1_init();
void timer1_start();
void timer1_stop();

#endif /* __MAIN_H */
