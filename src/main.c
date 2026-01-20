#include "TM4C123GH6PM.h"
#include "head.h"
#include "tail.h"
#include "limbs.h"
#include "lights.h"
#include "timing.h"
#include "logger.h"
#include "safety.h"
#include "behavior.h"

int main(void)
{
    TAIL_Init();
    HEAD_Init();
    LIMBS_Init();
    LIGHTS_Init();
    TIMING_Init();
    LOG_Init();
    WATCHDOG_Init();

    BEHAVIOR_Init();
    __enable_irq();

    while (1)
    {
        WATCHDOG_Kick();
        BEHAVIOR_Update();
    }
}
