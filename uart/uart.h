/* void UartInit (void)
   Initialization of the UART port
*/
UartInit:
   push {r1,lr}

@ The Raspberry Pi works with the UARTs in the background.
@ This can lead to complications.
@ To prevent this from happening, Line_CTRL and CONTROL must be deactivated during the first initialization.
   ldr r0,=UART0_LINE_CTRL       @Line_CTRL
   mov r1,#0                     @All to NULL
   str r1,[r0]                   @and store

   ldr r0,=UART0_CONTROL         @CONTROL
   mov r1,#0                     @All to NULL
   str r1,[r0]                   @and store


@ Set GPIO 14 and 15 to alternative function 0 (TXD0 and RXD0)
   mov r0,#14           @TXD0
   mov r1,#0b100        @ALT 0
   bl SetGPIOFunction

   mov r0,#15           @RXD0
   mov r1,#0b100        @ALT 0
   bl SetGPIOFunction

@ Disable pull up/down for all GPIO pins & delay for 150 cycles
@ UART needs those pins (GPIO 14 for TX and GPIO 15 for RX) to be very responsive,
@ only listening to or sending the exact signals they’re supposed to.
   ldr r0,=GPIO_PUP_PDN_CNTRL_REG0
   ldr r1, [r0]
   bic r1, r1, #(0b11 << 28)  @ Clear bits 28-29 (GPIO 14)
   bic r1, r1, #(0b11 << 30)  @ Clear bits 30-31 (GPIO 15)
   str r1, [r0]

   ldr r0,=MICROS_PER_SECOND
   bl wait

@ Setting baud rate parameters
@ Baud rate divisor BAUDDIV = (FUARTCLK/(16 * Baud rate))
@ FUARTCLK is the internal frequency that the Raspberry works with. For the Raspberry Pi 4 this is 48MHZ.
@ 48,000,000  / ( 16 * 115200 ) = 26 remainder 0.0417
@ IBRD = 26
@ For FBRD the value must be converted to an integer value:
@ 0 ,0417  * 64 = 2 ,667 Rounded 3
   ldr r0,=UART0_IBRD
   mov r1,#26
   str r1,[r0]

   ldr r0,=UART0_FBRD
   mov r1,#3
   str r1,[r0]

@ Setting the line control register
@ 8 bits (BYTE_WORD_LENGTH) and FIFO (ENABLE_FIFO) is now activated
   ldr r0,=UART0_LINE_CTRL
   mov r1,#BYTE_WORD_LENGTH | ENABLE_FIFO
   str r1,[r0]

@ Enable the UART0
   ldr r0,=UART0_CONTROL
   mov r1,#ENABLE | TX_ENABLE | RX_ENABLE
   str r1,[r0]

   pop {r1,pc}



/* void UartPutc (int Char)
   Write char in the UART
*/
UartPutc:
   push {r1,r2,lr}
   mov r2,r0                     @save Char to r2

   UartPutc_loop1$:              @Wait until UART is empty ...
      ldr r0,=UART0_STATUS       @address UART0_STATUS
      ldr r1,[r0]                @Load status to r1
      ands r1,r1,#TX_FIFO_FULL   @If status full...
      bne UartPutc_loop1$        @wait

   ldr r0,=UART0_DATA            @addresse for data to r0
   strb r2,[r0]                  @store char to data

   pop {r1,r2,pc}      @End at the function


/* void UartPuts (int String, int len)
   write string of length (len) to the UART
*/

UartPuts:
   push {r1,r2,lr}
   mov r2,r0                  @Store address of the string to r2

   UartPuts_loop1:
      subs r1,#1              @reduce length at 1
      blt UartPuts_loopend    @Jump as soon as length is zero
      ldrb r0,[r2]            @Load Char from string to r0
      add r2,#1               @Increment the pointer of the string by 1
      bl UartPutc             @Show Char
      b UartPuts_loop1        @Display the next char
   UartPuts_loopend:
   mov r0,#'\n'               @New line
   bl UartPutc                @and display

   mov r0,#'\r'               @return
   bl UartPutc                @and display

   pop {r1,r2,pc}
