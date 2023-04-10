## Preface
This library is created for basic control over a hobbyist continous or standar servos in the C language, tested up to 4 servos at the sime time. The library slightly extends to having a few functions to switch pin modes and set a pin high or low. These functions are very similar to the Arduino Library functions.

## Examples
Here is a basic example on how to control a singular servo

```c
servo_init(); // Initialize the 
servo_attach(pin_number);

servo_write(pin_number, angle); 
```
For more than one servo it is not any different
```c
servo_init();
servo_attach(pin_number);
serv_attach(pin_number_2);

servo_write(pin_number, angle); 
servo_write(pin_number, speed);
```
Continous and Standard servos can be used with this library
### Important Notes
- `servo_init()` must be called before attaching or writing to any pins
- `servo_attach()` will automatically set the angle/speed to 90
- Timer/Counter 1 is used with this library, it is currently not possible to change the timer at this current moment
- This implementation uses Interrupts and clearing interrupts will disturb the functionality
## Reference Table
### Servo.h Functions
| Function | Brief Description |
|---|---|
| servo_init() | Turn on hardware timers and options|
| servo_attach(uint8_t pin) | Set pin to send servo control pulse |
| servo_write(uint8_t pin, uint8_t val) | Sends control signal to servo on pin |
### Basic_wiring.h Functions
These are basic wiring functions that are implemented almost exactly like the Arduino Library, it is currently very limited
| Function | Brief Description |
|---|---|
| set_pin_output(uint8_t pin) | Sets pin to output|
| write_pin (uint8_t pin, uint8_t val) | Writes HIGH or LOW to pin|

## Demo
The Code used in the video 
// Youtube url
```c
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

```

## Implementation Details

### PWM 

### Basic Wiring


## Problems faced
set_angle math did not work due to uint16_t having limited space.
Figuring out how Math for PWM clock Servo Library

