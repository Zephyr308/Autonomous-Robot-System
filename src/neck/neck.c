#include "neck.h"

#define MIN_DUTY 1000
#define MAX_DUTY 319000

void neck_init(void){
    /* PWM setup as before */
}

void neck_setAngle(uint16_t angle){
    if(angle>180) angle=180;
    uint32_t duty = MIN_DUTY + ((MAX_DUTY-MIN_DUTY)*angle)/180;
    PWM1->_3_CMPA = duty;
}
