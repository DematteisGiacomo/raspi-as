.include "base.inc"
.include "gpio.h"
.include "time.h"
.include "uart.h"

.section .init
.globl _start
_start:

b main

.section .text    @Next is code

main:             @Label "main"
   mov sp,#0x8000 @Create Stack (32768 Bytes)

   bl UartInit             @Initiate UART first so that I can send messages

   ldr r0,=Text1           @Load pointer of the text to r0
   mov r1,#Text1End-Text1  @Length to r1
   bl UartPuts

MainLoop:         @Endlosschleife 

   ldr r0,=PippoString           @Load pointer of the text to r0
   mov r1,#PippoStringEnd-PippoString  @Length to r1
   bl UartPuts

   mov r0,#42
   bl LED_on

   mov r0,#0x100000
   bl wait

   mov r0,#42
   bl LED_off

   mov r0,#0x100000
   bl wait
   
   b MainLoop

.section .data
Text1:
.ascii "Hello World!"
Text1End:
.byte 'H','a','l','l','o'

PippoString:
.ascii "ciao pippo!"
PippoStringEnd:
.byte 'H','a','l','l','o'
