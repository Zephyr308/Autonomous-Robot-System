#include "TM4C123GH6PM.h"
#include "timing.h"

void TIMING_Init(void)
{
    SYSCTL->RCGCTIMER |= (1U << 1);   // Timer1
    TIMER1->CTL = 0;
    TIMER1->CFG = 0x0;
    TIMER1->TAMR = 0x02;              // periodic
    TIMER1->TAILR = 0xFFFFFFFF;       // free-running
    TIMER1->CTL |= 0x01;
}

uint32_t TIMING_GetTicksUs(void)
{
    return TIMER1->TAR;
}
