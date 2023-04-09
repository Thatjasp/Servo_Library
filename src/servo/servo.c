#define F_CPU 16000000UL
#include "basic_wiring.h"
#include "servo.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define F_CPU 16000000UL   // CPU frequency in Hz
#define SERVO_FREQ 50      // Servo PWM frequency in Hz
#define SERVO_MIN_US 1000  // Minimum pulse width for servo in microseconds
#define SERVO_MAX_US 2000  // Maximum pulse width for servo in microseconds
#define MIN_SERVO 1000
#define MAX_SERVO 5000
#define RANGE_SERVO (MAX_SERVO - MIN_SERVO)
#define MAX_SERVOS_ATTACHED 8

volatile uint8_t num_servos_attached = 0;
volatile uint32_t servo_pulse_sum = 0;
volatile uint8_t servo_pin_array[] = {0,0,0,0,0,0,0,0};
volatile uint16_t servo_pulse_array[] = {0,0,0,0,0,0,0,0};
volatile uint8_t cur_servo_index = 0;
volatile uint8_t prev_servo_index = 0;

volatile uint8_t is_ready = 0;
ISR(TIMER1_COMPA_vect) {
	if (num_servos_attached == 0) {
		return;
	}
	uint8_t pin = servo_pin_array[cur_servo_index];
	if (cur_servo_index == 0) {
		uint16_t pulse_length = servo_pulse_array[cur_servo_index];

		// Correct PWM
		write_pin(pin, HIGH);
		
		OCR1A = pulse_length - 1;
		prev_servo_index = cur_servo_index;
		cur_servo_index++;
		is_ready = 0;
		TCNT1 = 0;
	}
	else if ((num_servos_attached) == cur_servo_index) {
		uint8_t prev_pin = servo_pin_array[prev_servo_index];
		// Correct PWM
		write_pin(prev_pin, LOW);

		prev_servo_index = cur_servo_index - 1;
		cur_servo_index = 0;
		OCR1A = (F_CPU / SERVO_FREQ / 8) - servo_pulse_sum;
		is_ready = 1;
		TCNT1 = 0;
	} 
	else {
		uint8_t prev_pin = servo_pin_array[prev_servo_index];
		uint16_t pulse_length = servo_pulse_array[cur_servo_index];
		write_pin(prev_pin, LOW);
		write_pin(pin, HIGH);
		OCR1A = pulse_length-1;
		prev_servo_index = cur_servo_index;
		cur_servo_index++;
		TCNT1 = 0;
	}
}

void servo_init(void) {

    // Set Timer/Counter 1 to Fast CTC mode, non-inverting mode
    TCCR1A |= (1 << COM1A1);
    TCCR1B |= (1 << WGM12) | (1 << CS11);
    
    // Set the output pin for the servo to be an output
    //DDRB |= (1 << PB2);
    //DDRB |= (1 << PB4);
    // Enable Timer/Counter1 Compare A interrupt
    TIMSK1 |= (1 << OCIE1A);
    
    OCR1A = 3000;
    // Enable global interrupts
    sei();
}

uint8_t find_pin_pulse_arr(uint8_t pin) {
	for ( uint8_t i = 0; i < num_servos_attached; ++i) {
		if ( servo_pin_array[i] == pin ) {
			return i;
		}
	}
	return -1;
}

void servo_write(uint8_t pin, uint8_t angle) {
    while (is_ready == 0);
    uint16_t pulse = MIN_SERVO + (((uint32_t)angle * RANGE_SERVO) / 180);
     
    // Limit the pulse width to the range supported by the servo
    uint16_t pulse_width = (pulse_width > 180) ? MAX_SERVO : pulse;
    pulse_width = (pulse_width < 0) ? MIN_SERVO : pulse;

    uint8_t arr_index = find_pin_pulse_arr(pin);
    if (arr_index == -1){
	    return;
    }	
    
    servo_pulse_sum -= servo_pulse_array[arr_index];
    servo_pulse_array[arr_index] = pulse_width;
    servo_pulse_sum += servo_pulse_array[arr_index];
    
}

void servo_attach(uint8_t pin) {
	if (num_servos_attached >= MAX_SERVOS_ATTACHED) return;
	set_pin_output(pin);
	servo_pulse_array[num_servos_attached] = 3000; // Default 90 degrees
	servo_pin_array[num_servos_attached] = pin;
	num_servos_attached++;
	servo_pulse_sum += 3000;
}


