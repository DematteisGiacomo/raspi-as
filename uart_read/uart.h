/* void UartInit (void)
   Initialization of the UART port
*/
UartInit:
   push {r1,lr}

   ldr r0,=UART0_LINE_CTRL       @ Line_CTRL
   mov r1,#0                     @ Set everything to NULL
   str r1,[r0]                   @ and store

   ldr r0,=UART0_CONTROL         @ CONTROL
   mov r1,#0                     @ Set everything to NULL
   str r1,[r0]                   @ and store

/* GPIO 14 and 15 */

   mov r0,#14                    @ TXD0
   mov r1,#GPIO_alt0             @ ALT 0
   bl SetGPIOFunction

   mov r0,#15                    @ RXD0
   mov r1,#GPIO_alt0             @ ALT 0
   bl SetGPIOFunction

   ldr r0,=GPPUD
   mov r1,#GPPUD_OFF
   str r1,[r0]

   mov r0,#MICROS_PER_MILLISECOND
   bl wait

   ldr r0,=GPPUDCLK0
   mov r1,#0b11                  @ two pins
   lsl r1,#14                    @ starting from bit 14
   str r1,[r0]

   ldr r0,=UART0_IBRD
   mov r1,#26
   str r1,[r0]

   ldr r0,=UART0_FBRD
   mov r1,#3
   str r1,[r0]

   ldr r0,=UART0_LINE_CTRL
   mov r1,#BYTE_WORD_LENGTH | ENABLE_FIFO
   str r1,[r0]

   ldr r0,=UART0_CONTROL
   mov r1,#ENABLE | TX_ENABLE | RX_ENABLE
   str r1,[r0]

   pop {r1,pc}

/* void UartPutc (int Char)
   Write character to UART
*/
UartPutc:                           
   push {r1,r2,lr}
   mov r2,r0                     @ save Char

   UartPutc_loop1$:              @ Wait until UART is ready...
      ldr r0,=UART0_STATUS       @ Address UART0_STATUS 
      ldr r1,[r0]                @ Load status into r4
      ands r1,r1,#TX_FIFO_FULL   @ If status is full
      bne UartPutc_loop1$        @ Keep waiting

   ldr r0,=UART0_DATA            @ Address for data
   strb r2,[r0]                  @ Write Char to data register

   pop {r1,r2,pc}                @ End of function

/* void UartPuts (int String, int len)
   Write string of given length (len) to UART
*/
UartPuts:
   push {r1,r2,lr}
   mov r2,r0                  @ Save address of the string

   UartPuts_loop1:
      subs r1,#1              @ Decrease length by 1
      blt UartPuts_loopend    @ If length is zero, jump
      ldrb r0,[r2]            @ Load char from string into r0
      add r2,#1               @ Increase string pointer by 1
      bl UartPutc             @ Output char
      b UartPuts_loop1        @ Display next character
   UartPuts_loopend:

   mov r0,#'\n'               @ New line
   bl UartPutc                @ Send and display

   mov r0,#'\r'               @ Return to line start
   bl UartPutc                @ and send

   pop {r1,r2,pc}

/* char UartGetc (void)
   Get char from UART
*/
UartGetc:
   push {r4,lr}

   UartGetc_loop1$:              @ Wait until UART is ready...
      ldr r0,=UART0_STATUS       @ Address UART0_STATUS 
      ldr r1,[r0]                @ Load status into r4
      ands r1,r1,#RX_FIFO_EMPTY  @ If status is empty
      bne UartGetc_loop1$        @ Keep waiting

   ldr r0,=UART0_DATA            @ Address for data
   ldrb r0,[r0]                  @ Load char into r0
   mov r4,r0
   bl UartPutc
   mov r0,r4
   pop {r4,pc}

UartGetLine:
   push {r4,r5,lr}
   mov r0,#'>'               
   bl UartPutc 

   mov r4,#0
   ldr r5,=Eingabe
UartGetLineLoop:  
   bl UartGetc
   cmp r0,#13                  @ 13 is the enter key
   beq UartGetLineEnd
   strb r0,[r5]
   add r5,#1
   add r4,#1
   b UartGetLineLoop

UartGetLineEnd:
   mov r0,#'\n'               @ New line
   bl UartPutc                @ Send and display

   mov r0,#'\r'               @ Return to line start
   bl UartPutc                @ and send

   ldr r0,=EingabeLen
   str r4,[r0]

   pop {r4,r5,pc}

.section .data

GetLineStruct:
   EingabeLen:
      .int 0
   Eingabe:
      .space 256

.section .text
