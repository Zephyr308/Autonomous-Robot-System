#ifndef TIMING_H__
#define TIMING_H__

#include <stdint.h>

void timer_tick_init(void); // Timer2A 10ms tick
void TIMER2A_Handler(void);

#endif
