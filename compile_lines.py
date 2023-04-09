import os
import sys
import shutil

if len(sys.argv) != 3:
    sys.exit("python compile_lines.py <path_to_c_file> <comXX>")

file_name = os.path.splitext(sys.argv[1])[0]
com_output = sys.argv[2]

if not os.path.exists('objects'):
    os.mkdir("objects");
if not os.path.exists('hex'):
    os.mkdir("hex");
if not os.path.exists('linked_object'):
    os.mkdir("linked_object");
os.system(f'avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -Iinclude -o objects/{file_name}.o {file_name}.c')

os.system(f'avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -Iinclude -o objects/servo.o src/servo/servo.c')

os.system(f'avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -Iinclude -o objects/basic_wiring.o src/basic_wiring/basic_wiring.c')

os.system(f'avr-gcc -mmcu=atmega328p objects/{file_name}.o objects/basic_wiring.o objects/servo.o -o {file_name}')

os.system(f'avr-objcopy -O ihex -R .eeprom {file_name} hex/{file_name}.hex')

os.system(f'avrdude -patmega328p -P{com_output} -carduino -D -U flash:w:hex/{file_name}.hex:i')

if os.path.exists('objects'):
    shutil.rmtree('objects')
if os.path.exists('hex'):
    shutil.rmtree('hex')
if os.path.exists('linked_object'):
    shutil.rmtree('linked_object')
