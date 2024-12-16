#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	// Set pin 13 as output
	DDRB = (1 << DDB5);
	PORTB = 0x00;

	while(1)
	{
		PORTB ^= (1 << PORTB5);
        _delay_ms(250);
	}
}
