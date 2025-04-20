.equ RPI_BASE, 0xFE000000 

.equ GPIO_BASE, RPI_BASE + 0x200000

@ GPIO function select (GFSEL) registers have 3 bits per GPIO
.equ GPFSEL0, GPIO_BASE + 0x0   @GPIO select 0
.equ GPFSEL1, GPIO_BASE + 0x4   @GPIO select 1
.equ GPFSEL2, GPIO_BASE + 0x8   @GPIO select 2
.equ GPFSEL3, GPIO_BASE + 0xC   @GPIO select 3
.equ GPFSEL4, GPIO_BASE + 0x10  @GPIO select 4

   .equ GPIO_input,  0b000      @Input
   .equ GPIO_output, 0b001      @Output
   .equ GPIO_alt0,   0b100      @alternate function 0
   .equ GPIO_alt1,   0b101      @alternate function 1
   .equ GPIO_alt2,   0b110      @alternate function 2
   .equ GPIO_alt3,   0b111      @alternate function 3
   .equ GPIO_alt4,   0b011      @alternate function 4
   .equ GPIO_alt5,   0b010      @alternate function 5

@GPIO SET/CLEAR registers have 1 bit per GPIO
.equ GPSET0, GPIO_BASE + 0x1C @set0 (GPIO 0 - 31)
.equ GPSET1, GPIO_BASE + 0x20 @set1 (GPIO 32 - 63)
.equ GPCLR0, GPIO_BASE + 0x28 @clear0 (GPIO 0 - 31)
.equ GPCLR1, GPIO_BASE + 0x2C @clear1 (GPIO 32 - 63)

@ Old GPIO functions
.equ GPPUD,     GPIO_BASE + 0x94        
    .equ   GPPUD_OFF,       0b00
.equ GPPUDCLK0, GPIO_BASE + 0x98


@Timer registers
.equ TIMER_BASE, RPI_BASE + 0x003000
.equ TIMER_CS, TIMER_BASE + 0x00 @clock status
.equ TIMER_CLO, TIMER_BASE + 0x04 @ clock low 32 bytes
.equ TIMER_CHI, TIMER_BASE + 0x08 @ clock high 32 bytes

.equ MICROS_PER_SECOND, 1000000 @ Microseconds per second
.equ MICROS_PER_MILLISECOND, 1000 @ Microseconds per millisecond

.equ T1_CLOCK_SECOND, MICROS_PER_SECOND @ RPi is microseconds

@UART0
.equ UART0_BASE, RPI_BASE + 0x201000    @ Base address UART0
.equ UART0_DATA,      UART0_BASE + 0x00 @DR Data Register 
.equ UART0_RSRECR,    UART0_BASE + 0x04 @RSRECR
.equ UART0_STATUS,     UART0_BASE + 0x18 @FR Flag Register
	.equ TX_FIFO_FULL, 		0b100000
   .equ RX_FIFO_EMPTY,     0b10000
.equ UART0_ILPR,      UART0_BASE + 0x20 @ILPR not in use
.equ UART0_IBRD,      UART0_BASE + 0x24 @IBRD Integer Baud rate divisor
.equ UART0_FBRD,      UART0_BASE + 0x28 @FBRD Fractional Baud rate divisor
.equ UART0_LINE_CTRL, UART0_BASE + 0x2C @LCRH Line Control register
	.equ ENABLE_FIFO, 		0b10000
	.equ BYTE_WORD_LENGTH, 	0b1100000
.equ UART0_CONTROL,   UART0_BASE + 0x30 @CR Control register
	.equ ENABLE, 			0b1
	.equ TX_ENABLE, 		0b100000000
	.equ RX_ENABLE, 		0b1000000000
.equ UART0_IFLS,      UART0_BASE + 0x34 @IFLS Interrupt FIFO Level Select Register 
.equ UART0_IMSC,      UART0_BASE + 0x38 @IMSC Interrupt Mask Set Clear Register
.equ UART0_RIS,       UART0_BASE + 0x3C @RIS Raw Interrupt Status Register
.equ UART0_MIS,       UART0_BASE + 0x40 @MIS Masked Interrupt Status Register
.equ UART0_ICR,       UART0_BASE + 0x44 @ICR Interrupt Clear Register
.equ UART0_DMACR,     UART0_BASE + 0x48 @DMACR DMA Control register
.equ UART0_ITCR,      UART0_BASE + 0x80 @ITCR Test Control register
.equ UART0_ITIP,      UART0_BASE + 0x84 @ITIP Integration test input reg
.equ UART0_ITOP,      UART0_BASE + 0x88 @ITOP Integration test output reg
.equ UART0_TDR,       UART0_BASE + 0x8C @TDR Test Data reg
