#include "TM4C123GH6PM.h"
#include "head.h"
#include "tail.h"
#include "limbs.h"
#include "neck.h"
#include "lights.h"
#include "timing.h"
#include "behavior.h"

int main(void){
    TAIL_Init();
    HEAD_Init();
    LIGHTS_Init();
    LIMBS_Init();
    neck_init();
    timer_tick_init();
    __enable_irq();

    while(1){
        behavior_update();
    }
}
