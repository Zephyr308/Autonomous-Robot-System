#ifndef BEHAVIOR_H
#define BEHAVIOR_H

typedef enum {
    BEHAVIOR_IDLE,
    BEHAVIOR_PLAY,
    BEHAVIOR_SHY,
    BEHAVIOR_EVADE
} behavior_state_t;

void BEHAVIOR_Init(void);
void BEHAVIOR_Update(void);

#endif
