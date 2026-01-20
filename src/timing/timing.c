#include "TM4C123GH6PM.h"
#include "timing.h"

volatile bool task_sense;
volatile bool task_control;
volatile bool task_behavior;

void TIMING_Init(void)
{
    SYSCTL->RCGCTIMER |= (1<<2);
    TIMER2->CTL = 0;
    TIMER2->CFG = 0x04;
    TIMER2->TAMR = 0x02;
    TIMER2->TAILR = 16000; // 1ms @16MHz
    TIMER2->IMR |= 1;
    TIMER2->CTL |= 1;
    NVIC->ISER[0] |= (1<<23);
}

void TIMING_Tick(void)
{
    static uint8_t div = 0;

    task_sense = true;
    task_control = true;

    if (++div >= 10) {
        task_behavior = true;
        div = 0;
    }
}

uint32_t TIMING_GetTicks(void)
{
    return TIMER1->TAR; // free-running down-counter
}

