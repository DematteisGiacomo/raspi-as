# raspi-as

Assembly projects on Raspberry pi 4 model b:

## blinky_42

## blinky_17

## uart

## pwd

## To compile
```bash
arm-none-eabi-as blinky.s -o blinky.o
arm-none-eabi-ld --no-undefined blinky.o -o blinky.elf
arm-none-eabi-objcopy blinky.elf -O binary kernel7l.img
```
