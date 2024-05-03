/* void SetGPIOFunction (int Pin(r0), int Function(r1))
*/

SetGPIOFunction:
   push {lr}
   ldr r2,=GPFSEL0

SetGPIOFunction_loop1:
   cmp r0,#9
   subhi r0,#10
   addhi r2,#4
   bhi SetGPIOFunction_loop1

add r0,r0,lsl #1

lsl r1,r0

mov r3,#0b111
lsl r3,r0
mvn r3,r3

ldr r4,[r2]
and r4,r3

orr r1,r4

str r1,[r2]

pop {pc}


/* void LED_on (int r0)
   the pin of the LED is transferred in r0
*/
LED_on:
   push {r5,lr}
   mov r5,r0

   mov r1,#0b001
   bl SetGPIOFunction

   mov r0,r5

   ldr r1,=GPSET0
   cmp r0,#31
   subhi r0,#32
   addhi r1,#4

   mov r2,#1
   lsl r2,r0

   str r2,[r1]

   pop {r5,pc}


/* void LED_off (int r0)
   the pin of the LED is transferred in r0
*/
LED_off:
   push {r5,lr}
   mov r5,r0

   mov r1,#0b001
   bl SetGPIOFunction

   mov r0,r5

   ldr r1,=GPCLR0
   cmp r0,#31
   subhi r0,#32
   addhi r1,#4

   mov r2,#1
   lsl r2,r0

   str r2,[r1]

   pop {r5,pc}










