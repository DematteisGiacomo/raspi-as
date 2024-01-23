.include "base.inc"
.include "gpio.h"
.include "time.h"

.section .init
.globl _start
_start:

b main

.section .text    @Next is code

main:             @Label "main"
   mov sp,#0x8000 @Create Stack (32768 Bytes)

MainLoop:

   mov r0,#17
   bl LED_on

   ldr r0,=MICROS_PER_SECOND
   bl wait

   mov r0,#17
   bl LED_off

   ldr r0,=MICROS_PER_SECOND
   bl wait

   b MainLoop
