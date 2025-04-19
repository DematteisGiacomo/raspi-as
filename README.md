# raspi-as

Assembly projects on Raspberry Pi 4 model B:

## blinky_42
Blinky on built-in led

## blinky_17
Blinky using a GPIO (17 randomly chosen).
Connect a led with 1k resistor in series from GPIO17 to ground.

## uart_write
UART peripheral used to write strings to usb via TTL

## uart_read
UART peripheral used to read strings from usb via TTL

## pwd
Control a motor with pwd peripheral

## To compile
```bash
arm-none-eabi-as blinky.s -o blinky.o
arm-none-eabi-ld --no-undefined blinky.o -o blinky.elf
arm-none-eabi-objcopy blinky.elf -O binary kernel7l.img
```
