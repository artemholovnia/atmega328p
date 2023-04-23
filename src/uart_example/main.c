#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/delay.h>
#include "uart.h"

/* Define CPU frequency in Hz in Makefile or toolchain compiler configuration */
#ifndef F_CPU
#error "F_CPU undefined, please define CPU frequency in Hz in Makefile or compiler configuration"
#endif

/* Define UART baud rate here */
#define UART_BAUD_RATE 57600

char* uart_in(char* buf) {
    uint16_t c, li;

    for (;;) {

        c = uart_getc();

        if (c != UART_NO_DATA) {
            if (c == '\n' || c == '\r') {
                return buf;
            } else {
                buf[li] = (char)c;
                li ++;
            }
        }
    }
}

void uart_println(char* buf) {
    uart_puts(buf);
    uart_putc('\n');
}

int main(void)
{

    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));
    sei();

    char name[128], sorname[128];
    for (;;) {
        memset(name, 0, sizeof(name));
        memset(sorname, 0, sizeof(sorname));
        uart_println("\n\nLets speek\n<- Whats your name? ");
        uart_in(name);
        uart_println("<- Sorname? ");
        uart_in(sorname);

        uart_println("\n\nSummary");
        uart_println("\nYour name is:");
        uart_println(name);
        uart_println("\nAnd sorname is:");
        uart_println(sorname);
    };
}