#ifndef SAFETY_H
#define SAFETY_H

void WATCHDOG_Init(void);
void WATCHDOG_Kick(void);
void FAILSAFE_Enter(void);

#endif
