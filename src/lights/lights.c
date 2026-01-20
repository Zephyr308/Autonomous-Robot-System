#include "TM4C123GH6PM.h"
#include "lights.h"

void LIGHTS_Set(uint8_t mask)
{
    GPIOF->DATA = mask;
}
