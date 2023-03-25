#include <avr/io.h>
#include <util/delay.h>

#define SERVO_FREQ 50
#define MEGA_FREQ 16000000UL
// with prescaler 8
#define MEGA_FREQ_8 2000000UL

// In the thousands for greater precision
#define MIN_SERVO 1000
// In the thousands for greater precision
#define MAX_SERVO 4750

#define CONT_MAX_SERVO 4000

#define CONT_MIN_SERVO 2000

#define CONT_RANGE_SERVO (CONT_MAX_SERVO - CONT_MIN_SERVO)

#define RANGE_SERVO (MAX_SERVO - MIN_SERVO)

//
#define SERVO_PERIOD 20000

// avr-gcc -Wall -Os -DF_CPU=16000000UL -mmcu=atmega328 -c -o pwm.o pwm.c
void servo_setup() {
	TCCR1A |= (1 << COM1A1) | (1 << COM1B1);
	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS11);
	ICR1 = ( MEGA_FREQ_8 / SERVO_FREQ) - 1;
	DDRB |= ( 1 << PB1 );
}

void set_angle(uint32_t angle) {
	// range handling
	uint16_t pulse = MIN_SERVO + ((angle * RANGE_SERVO) / 180);

	// uint16_t translated_pulse = (pulse * (ICR1+1)) / SERVO_PERIOD;

	OCR1A = pulse;
	
	_delay_ms(20);
}


int main() {

	servo_setup();
	while(1) {
			for (int pos = 0; pos < 180; ++pos) {
				set_angle(pos);
			}
//		set_angle(0);
//		OCR1A = 1000;
//		_delay_ms(2000);
		//OCR1A = 2800;
		// 
		// FOR STANDARD SERVO
//		 OCR1A = 2875;

//		set_angle(90);
		// FOR CONTINOUS SERVO
//		OCR1A = 3000;
//		_delay_ms(2000);

		// FOR STANDARD SERVO
//		OCR1A = 4750;
//		OCR1A = 5000;

		// FOR CONTINOUS SERVO
//		OCR1A = 4000;
//		_delay_ms(2000);
//		set_angle(180);
//		_delay_ms(2000);
	}

}




