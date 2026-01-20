#include "behavior.h"

int main(void)
{
    TAIL_Init();
    HEAD_Init();
    LIMBS_Init();
    LIGHTS_Init();
    TIMING_Init();

    BEHAVIOR_Init();
    __enable_irq();

    while (1)
    {
        if (task_behavior) {
            task_behavior = false;
            BEHAVIOR_Update();
        }
    }
}
