#include "basic_wiring.h"
#include <avr/io.h>

const uint16_t PROGMEM pin_to_bit_mask_PGM[] = {
	_BV(0), //PD
	_BV(1),
	_BV(2),
	_BV(3),
	_BV(4),
	_BV(5),
	_BV(6),
	_BV(7),
	_BV(0), // PB index 8
	_BV(1),
	_BV(2),
	_BV(3),
	_BV(4),
	_BV(5)
};

const uint8_t PROGMEM pin_to_port_PGM[] = {
	PD,
	PD,
	PD,
	PD,
	PD,
	PD,
	PD,
	PD,
	PB,
	PB,
	PB,
	PB,
	PB,
	PB
};

const uint16_t PROGMEM port_to_mode_PGM[] = {
	NOT_A_PORT,
	NOT_A_PORT,
	(uint16_t) &DDRB,
	(uint16_t) &DDRC,
	(uint16_t) &DDRD,
};
const uint16_t PROGMEM port_to_output_PGM[] = {
	NOT_A_PORT,
	NOT_A_PORT,
	(uint16_t) &PORTB,
	(uint16_t) &PORTC,
	(uint16_t) &PORTD,
};
void set_pin_output(uint8_t pin) {
	uint8_t bitmask = pin_to_bitmask(pin);
	uint8_t port = pin_to_port(pin);
	volatile uint8_t *reg;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"
	reg = port_mode_register(port);
#pragma GCC diagnostic pop
	*reg |= bitmask;
}
void write_pin(uint8_t pin, uint8_t val) {
	uint8_t bitmask = pin_to_bitmask(pin);
	uint8_t port = pin_to_port(pin); 
	volatile uint8_t *out;

	if (port == NOT_A_PORT) return;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"
	out = port_mode_output(port);
#pragma GCC diagnostic pop
	if (val == LOW) {
		*out &= ~bitmask;
	} else {
		*out |= bitmask;
	}
}
