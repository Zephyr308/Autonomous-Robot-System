#include "lights.h"
#include "TM4C123GH6PM.h"

void light_set(uint8_t color){
    GPIO_PORTF_DATA_R = color;
}
