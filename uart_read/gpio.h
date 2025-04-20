
/* void LED_on (int r0)
   the LED pin is passed in r0
*/
LED_on:
   push {r5,lr}
   mov r5,r0 @save the argument

/* First, assign the function */
   mov r1,#0b001
   bl SetGPIOFunction

/* Now we turn on the LED. */
   mov r0,r5         @retrieve our LED number

   ldr r1,=GPSET0
   cmp r0,#31
   subhi r0,#32
   addhi r1,#4

   mov r2,#1
   lsl r2,r0

   str r2,[r1]
   pop {r5,pc}

/* void LED_off (int r0)
   the LED pin is passed in r0
*/
LED_off:
   push {r5,lr}
   mov r5,r0 @save the argument

/* First, assign the function */
   mov r1,#0b001
   bl SetGPIOFunction

/* Now we turn off the LED. */
   mov r0,r5         @retrieve our LED number

   ldr r1,=GPCLR0
   cmp r0,#31
   subhi r0,#32
   addhi r1,#4

   mov r2,#1
   lsl r2,r0

   str r2,[r1]
   pop {r5,pc}

/* void SetGPIOFunction (int Pin(r0), int Function(r1)) */
SetGPIOFunction:
   push {lr}
   ldr r2,=GPFSEL0
SetGPIOFunction_loop1:
   cmp r0,#9
   subhi r0,#10
   addhi r2,#4
   bhi SetGPIOFunction_loop1

   @ r0 now contains the remainder
   @ r2 contains the corresponding register

   add r0,r0,lsl #1  @ equivalent to multiplying by 3

   lsl r1,r0         @ shift code into position

   @ Create a mask for the old code

   mov r3,#0b111     @ represents one function in the register
   lsl r3,r0         @ and shift it to the same position as before
   mvn r3,r3         @ invert the value

   ldr r4,[r2]       @ load the original value of the register
   and r4,r3         @ clear the desired bits

   orr r1,r4         @ insert new value
   str r1,[r2]       @ and store it

   pop {pc}
