#ifndef TIMING_H
#define TIMING_H

#include <stdbool.h>

extern volatile bool task_sense;
extern volatile bool task_control;
extern volatile bool task_behavior;

void TIMING_Init(void);
void TIMING_Tick(void);
uint32_t TIMING_GetTicks(void);   // returns microseconds


#endif
