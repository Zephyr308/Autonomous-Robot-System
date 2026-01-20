#include "TM4C123GH6PM.h"
#include "logger.h"

void LOG_Init(void)
{
    SYSCTL->RCGCUART |= 1;
    SYSCTL->RCGCGPIO |= 1;

    GPIOA->AFSEL |= (1<<0)|(1<<1);
    GPIOA->DEN   |= (1<<0)|(1<<1);
    GPIOA->PCTL  |= 0x11;

    UART0->CTL = 0;
    UART0->IBRD = 104;
    UART0->FBRD = 11;
    UART0->LCRH = 0x60;
    UART0->CTL = 0x301;
}

void LOG_Event(log_event_t type, uint32_t a, uint32_t b)
{
    while (UART0->FR & 0x20);
    UART0->DR = type;
    UART0->DR = a;
    UART0->DR = b;
}
