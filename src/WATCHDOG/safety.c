#include "TM4C123GH6PM.h"
#include "limbs.h"
#include "lights.h"
#include "logger.h"

void WATCHDOG_Init(void)
{
    SYSCTL->RCGCWD |= 1;
    WATCHDOG0->LOAD = 16000000;
    WATCHDOG0->CTL = 0x3;
}

void WATCHDOG_Kick(void)
{
    WATCHDOG0->ICR = 1;
}

void Watchdog_Handler(void)
{
    LOG_Event(LOG_WATCHDOG, 0, 0);
    FAILSAFE_Enter();
}

void FAILSAFE_Enter(void)
{
    STOP();
    GPIOF->DATA = RED;
    while (1);
}
