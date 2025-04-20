.include "base.inc"
.include "gpio.h"
.include "time.h" 
.include "uart.h"

.section .init
.globl _start
_start:

b main

.section .text    @ Directive to the linker that code follows

main:             @ Create the label "main"
   mov sp,#0x8000 @ Create a stack of 32768 bytes

   bl UartInit             @ First initialize UART so we can send messages

MainLoop:                  @ Infinite loop

   ldr r0,=Text1           @ Load pointer to text into r0
   mov r1,#Text1End-Text1  @ Load length into r1
   bl UartPuts

   bl UartGetLine
   ldr r1,[r0]
   add r0,#4
   ldrb r0,[r0]
   cmp r0,#48              @ Compare to ASCII '0'
   beq LEDOFF              @ If '0', turn LED off
      mov r0,#42
      bl LED_on
      b MainLoop
LEDOFF:
      mov r0,#42
      bl LED_off
      b MainLoop

.section .data
Text1:
.ascii "0 = LEDOFF, 1 or other = LEDON"
Text1End:
