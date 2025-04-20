/* time.h */

/* void wait (int r0)
   r0 specifies the number of milliseconds
*/

wait:
   push {lr}

   mov r2,r0            @ save the comparison value

   bl GetTimeStamp      @ get the current time counter
   mov r3,r0            @ and store it in r3

wait_loop$:
   bl GetTimeStamp      @ get the current time counter
   sub r1,r0,r3         @ subtract the stored value from r0 and store it in r1
   cmp r1,r2            @ compare the difference with the argument
   bls wait_loop$       @ if less or equal, keep waiting

   pop {pc}             @ end wait

/* int GetTimeStamp (void)
*/
GetTimeStamp:
   push {lr}

   ldr r0,=TIMER_CLO    @ address of the lower system timer counter
   ldr r0,[r0]          @ get the current value

   pop {pc}
