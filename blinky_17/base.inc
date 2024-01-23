.equ RPI_BASE, 0xFE000000 

.equ GPIO_BASE, RPI_BASE + 0x200000

@ GPIO function select (GFSEL) registers have 3 bits per GPIO
.equ GPFSEL0, GPIO_BASE + 0x0   @GPIO select 0
.equ GPFSEL1, GPIO_BASE + 0x4   @GPIO select 1
.equ GPFSEL2, GPIO_BASE + 0x8   @GPIO select 2
.equ GPFSEL3, GPIO_BASE + 0xC   @GPIO select 3
.equ GPFSEL4, GPIO_BASE + 0x10  @GPIO select 4

@ GPIO SET/CLEAR registers have 1 bit per GPIO
.equ GPSET0, GPIO_BASE + 0x1C @set0 (GPIO 0 - 31)
.equ GPSET1, GPIO_BASE + 0x20 @set1 (GPIO 32 - 63)
.equ GPCLR0, GPIO_BASE + 0x28 @clear0 (GPIO 0 - 31)
.equ GPCLR1, GPIO_BASE + 0x2C @clear1 (GPIO 32 - 63)


@Timer registers
.equ TIMER_BASE, RPI_BASE + 0x003000
.equ TIMER_CS, TIMER_BASE + 0x00 @clock status
.equ TIMER_CLO, TIMER_BASE + 0x04 @ clock low 32 bytes
.equ TIMER_CHI, TIMER_BASE + 0x08 @ clock high 32 bytes

.equ MICROS_PER_SECOND, 1000000 @ Microseconds per second
.equ MICROS_PER_MILLISECOND, 1000 @ Microseconds per millisecond

.equ T1_CLOCK_SECOND, MICROS_PER_SECOND @ RPi is microseconds
