#ifndef BASIC_WIRING_H
#define BASIC_WIRING_H
#include <avr/io.h>
#include <avr/pgmspace.h>
//#define _BV(bit)	(1UL << (bit))
// From the ArduinoCore-avr github

#define pin_to_port(PIN) ( pgm_read_byte( pin_to_port_PGM + (PIN) ))
#define pin_to_bitmask(PIN) ( pgm_read_byte( pin_to_bit_mask_PGM + (PIN) ))


#define port_mode_register(PIN) ( (volatile uint8_t *) pgm_read_byte( port_to_mode_PGM + (PIN) ))
#define port_mode_output(PIN) ( (volatile uint8_t *) pgm_read_byte( port_to_output_PGM + (PIN) ))
#define NOT_A_PORT 0
#define OUTPUT 1
#define INPUT 1

#define LOW 0
#define HIGH 1

#define PB 2
#define PC 3
#define PD 4
extern const uint16_t PROGMEM pin_to_bit_mask_PGM[];

extern const uint8_t PROGMEM pin_to_port_PGM[];

extern const uint16_t PROGMEM port_to_mode_PGM[];
extern const uint16_t PROGMEM port_to_output_PGM[];
void set_pin_output(uint8_t pin);
void write_pin(uint8_t pin, uint8_t val);
#endif
