#ifndef SERVO_H
#define SERVO_H
#include <stdint.h>
void servo_init(void);
uint8_t find_pin_pulse_arr(uint8_t pin);
void servo_write(uint8_t pin, uint8_t angle);
void servo_attach(uint8_t pin);
#endif
