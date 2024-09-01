.include "base.inc"
.include "gpio.h"
.include "time.h"
.include "uart.h"

.section .init
.globl _start
_start:

.section  .data
Text1:
      .ascii  "Hello World!"
Text1End:

b main

.section .text    @Next is code

main:             @Label "main"
   mov sp,#0x8000 @Create Stack (32768 Bytes)

MainLoop:

   bl UartInit             @Initiate UART first so that I can send messages

   ldr r0,=Text1           @Load pointer of the text to r0
   mov r1,#Text1End-Text1  @Length to r1
   bl UartPuts
