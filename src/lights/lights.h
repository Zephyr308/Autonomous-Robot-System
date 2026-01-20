#ifndef LIGHTS_H
#define LIGHTS_H

#include <stdint.h>

#define RED   (1U<<1)
#define BLUE  (1U<<2)
#define GREEN (1U<<3)

void LIGHTS_Init(void);
void LIGHTS_Set(uint8_t mask);

#endif
