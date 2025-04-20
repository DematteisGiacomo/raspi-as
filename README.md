# raspi-as

Assembly projects on Raspberry Pi 4 model B

## blinky_42
Blinky on built-in led

## blinky_17
Blinky using a GPIO (17 randomly chosen)

Connect a led with 1k resistor in series from GPIO17 to ground

## uart_write
UART peripheral used to write strings to usb via TTL

## uart_read
UART peripheral used to read strings from usb via TTL

Uart reads are use to control the built-in LED.

## pwd_blinky
Control an led with pwd peripheral

## pwd_motor
Control a motor with pwd peripheral


## To compile and boot

First, format an SD card in FAT32 format and name it "BOOT." To make this card bootable, a few more files are required:

```bash
bcm2711-rpi-4-b.dtb
bootcode.bin
start.elf
start4.elf
```

These can be downloaded from https://github.com/raspberrypi/firmware/tree/master/boot


Generate program with
```bash
arm-none-eabi-as blinky.s -o blinky.o
arm-none-eabi-ld --no-undefined blinky.o -o blinky.elf
arm-none-eabi-objcopy blinky.elf -O binary kernel7l.img
```

You can now copy your generated "kernel7i.img" file to the boot partition of the SD card. Now insert the card into the Raspberry Pi and boot the Raspberry Pi
