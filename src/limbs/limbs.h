#ifndef LIMBS_H__
#define LIMBS_H__

#include <stdint.h>

/* Assembly drivers */
void LIMBS_Init(void);
void FORWARD(void);
void STOP(void);
void TURN_Left(void);
void TURN_Right(void);

/* Non-blocking movement interface */
typedef enum {MOVE_IDLE, MOVE_FORWARD, TURN_LEFT_STATE, TURN_RIGHT_STATE} MoveState_t;

typedef struct {
    MoveState_t state;
    uint32_t ticks_remaining;
} Motion_t;

extern Motion_t motion;

void move_forward(uint32_t duration_ms);
void turn_left(uint32_t duration_ms);
void turn_right(uint32_t duration_ms);
void update_motion(void);

#endif
