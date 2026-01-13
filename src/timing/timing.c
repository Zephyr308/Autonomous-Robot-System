#include "timing.h"
#include "limbs.h"
#include "head.h"
#include "tail.h"

volatile uint32_t system_tick = 0;

void timer_tick_init(void){
    SYSCTL->RCGCTIMER |= (1<<2);
    TIMER2->CTL = 0;
    TIMER2->CFG = 0x04;
    TIMER2->TAMR = 0x02;
    TIMER2->TAILR = 64000; // 10ms tick
    TIMER2->ICR = 1;
    TIMER2->IMR |= 1;
    NVIC->ISER[0] |= (1<<23);
    TIMER2->CTL |= 1;
}

void TIMER2A_Handler(void){
    TIMER2->ICR = 1;
    system_tick++;

    /* Update motion controller */
    update_motion();
}
