#ifndef HEAD_H__
#define HEAD_H__
#include <stdint.h>

/**@brief Initialize ultrasonic trigger pin and Timer0 capture interrupt */
void HEAD_Init(void);

/**@brief Get last measured distance in cm */
uint32_t head_getDistance(void);

#endif
