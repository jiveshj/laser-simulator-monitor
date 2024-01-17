/*
 * blinky example
 */

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

// Arduino LED is on PB5

#define LED_DDR DDRB
#define LED_BIT 5
#define LED_PORT PORTB

int main (void)
{

  LED_DDR |= (1 << LED_BIT);

  while( 1) {
    LED_PORT |= (1 << LED_BIT);
    _delay_ms( 250);
    LED_PORT &= ~(1 << LED_BIT);
    _delay_ms( 250);
  }
}


