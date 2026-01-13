#ifndef LIGHT_H__
#define LIGHT_H__

#define RED   (1U<<1)
#define BLUE  (1U<<2)
#define GREEN (1U<<3)

void LIGHTS_Init(void);
void light_set(uint8_t color);

#endif
