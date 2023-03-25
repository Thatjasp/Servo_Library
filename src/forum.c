#define F_CPU 16000000UL

#define _BV(bit)	(1UL << (bit))

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>

//static volatile uint8_t servo_cnt = 8;
//static volatile uint16_t 	currPos[8];
static volatile uint16_t 	pos;
//static volatile uint16_t 	nextPos[8];

ISR(TIM1_CAPT_vect) 
{
	PORTB |= _BV(PORTB0);
}
ISR(TIM1_COMPA_vect) {
	PORTB &= ~_BV(PORTB0);
}

int main(){
	// Set up Timer 1 for 2.5ms counter (20ms period shared by 8 servos)
	TCCR1A = 0x00;      // Outputs Disabled
	TCCR1B = 
		_BV(WGM13) |        // TOP - ICR1
		_BV(WGM12) |        // CTC Mode
		_BV(CS11);          // Prescaler = 8
	ICR1 = 4999;            // Top = (16Mhz * 2.5ms / 8) -1
	OCR1A = 5000;           // Ensure Timer 1 Compare Match A does not happen first
	TIMSK1 = 
		_BV(ICIE1) |        // Enable Input Capture Interrupt
		_BV(OCIE1A);        // Enable Output Compare Match A Interrupt
	DDRB |= (1 << PB0);
	//DDRB |= (1 << PB1);
}
