#include "servo.h"
#include "basic_wiring.h"
#include <util/delay.h>


int main(void) {
    servo_init();
    servo_attach(12);
    servo_attach(10);
    servo_attach(11);
    servo_attach(8);
    while (1) {

        // Move the servo to the minimum position
	servo_write(10,0);
	servo_write(12,0);
	servo_write(11,0);
	servo_write(8,0);
	_delay_ms(3000);
	servo_write(10, 180);
	servo_write(8,180);
	servo_write(11, 180);
	servo_write(12, 90);
        _delay_ms(3000);
    }
}
