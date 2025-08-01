#ifndef COM_H
#define COM_H


#include <stdint.h>


#define UART_BASE ((volatile uint32_t *) 0x9000000) //placeholder addr
//ARM PL011 UART
#define UART_DR      (*(UART_BASE + 0x0/4))
#define UART_FR      (*(UART_BASE + 0x18/4))
#define UART_FR_TXFF (1<<5)


static inline void serial_putc(char c)
{
    // --------------------------------------
    // wait until TX FIFO isn't full
    // --------------------------------------
    while (UART_FR & UART_FR_TXFF);
    UART_DR = c;
}


static inline void serial_print(const char* str)
{
    while (*str)
    {
        serial_putc(*str++);
    }
}


static inline void serial_print_hex64(uint64_t val)
{
    //placeholdrs for now
    const char hex[] = "0123456789ABCDEF";
    serial_print("0x");
    for (int i = 60; i >= 0; i -= 4)
    {
        serial_putc( hex[(val >> i) & 0xF]);
    }
}


static inline void serial_print_hex32(uint32_t val)
{
    const char hex[] = "0123456789ABCDEF";
    serial_print("0x");
    for (int i = 28; i >= 0; i -= 4) {
        serial_putc( hex[(val >> i) & 0xF] );
    }
}


#endif  // COM_H
