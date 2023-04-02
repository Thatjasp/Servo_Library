#define F_CPU 16000000UL

#define _BV(bit)	(1UL << (bit))

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>

#include <avr/io.h>

#define F_CPU 16000000UL   // CPU frequency in Hz
#define SERVO_FREQ 50      // Servo PWM frequency in Hz
#define SERVO_MIN_US 1000  // Minimum pulse width for servo in microseconds
#define SERVO_MAX_US 2000  // Maximum pulse width for servo in microseconds
#define MIN_SERVO 1000
#define MAX_SERVO 5000
#define RANGE_SERVO (MAX_SERVO - MIN_SERVO)
volatile uint32_t pulse_width_us =  3000;  // Initialize pulse width to 90 degrees
volatile uint8_t which_servo = 0;
volatile uint8_t is_ready = 0;

ISR(TIMER1_COMPA_vect) {
    // Set the pulse width for the servo
    switch (which_servo) {
	    case 0:
		which_servo++;
		OCR1A = pulse_width_us; // PB2's pulse_width
		PORTB &= ~(1 << PB2);
		break;
	    case 1:
		which_servo = 0;
		PORTB &= ~(1 << PB4);
		break;
    }
}
ISR (TIMER1_OVF_vect) {
	switch (which_servo) {
		case 0:
		    PORTB |= (1 << PB2);
		    break;
		case 1:
		    OCR1A = pulse_width_us; // PB4's pulse_width
		    PORTB |= (1 << PB4);
		    break;
	}
}

void servo_init(void) {

    // Set Timer/Counter 1 to Fast PWM mode, non-inverting mode
    TCCR1A |= (1 << WGM11) | (1 << COM1A1);
    TCCR1B |= (1 << WGM12) | (1 << WGM13) | (1 << CS11);
    
    // Set the value of ICR1 to set the PWM frequency to 50 Hz
    ICR1 = (F_CPU / SERVO_FREQ / 8) - 1;
    
    // Set the output pin for the servo to be an output
    DDRB |= (1 << PB2);
    DDRB |= (1 << PB4);
    
    // Enable Timer/Counter1 Compare A interrupt
    TIMSK1 |= (1 << OCIE1A);
    TIMSK1 |= (1 << TOIE1);
    
    // Enable global interrupts
    sei();
}

void servo_write(uint32_t pulse_width) {
    while (is_ready == 0);
    uint16_t pulse = MIN_SERVO + ((pulse_width * RANGE_SERVO) / 180);
    // Limit the pulse width to the range supported by the servo
    pulse_width = (pulse_width < 0) ? MIN_SERVO : pulse;
    pulse_width = (pulse_width > 180) ? MAX_SERVO : pulse;
    
    // Set the new pulse width
    pulse_width_us = pulse;
}

int main(void) {
    servo_init();
    
    while (1) {
        // Move the servo to the minimum position
//        servo_write(0);
 //       _delay_ms(1000);
 //        servo_write(90);
// 	_delay_ms(300);      
        // Move the servo to the maximum position
	 servo_write(90);
        _delay_ms(3000);
	
        servo_write(0);
	_delay_ms(3000);
    }
}
