#include "behavior.h"
#include "head.h"
#include "tail.h"
#include "limbs.h"
#include "lights.h"
#include "timing.h"
#include "logger.h"

static behavior_state_t state;
static uint32_t state_entry_time;

static void EnterState(behavior_state_t next)
{
    uint32_t now = TIMING_GetTicksUs();
    LOG_Event(LOG_STATE, state, now - state_entry_time);
    state_entry_time = now;
    state = next;
}

void BEHAVIOR_Init(void)
{
    state = BEHAVIOR_IDLE;
    state_entry_time = TIMING_GetTicksUs();
}

void BEHAVIOR_Update(void)
{
    uint32_t dist = headSensor_detect();
    uint8_t tail  = TAIL_sense();

    switch (state)
    {
        case BEHAVIOR_IDLE:
            STOP();
            GPIOF->DATA = BLUE;
            if (dist > 10)
                EnterState(BEHAVIOR_PLAY);
            break;

        case BEHAVIOR_PLAY:
            GPIOF->DATA = GREEN;
            if (dist < 7 && tail)
                EnterState(BEHAVIOR_EVADE);
            else if (dist < 7)
                EnterState(BEHAVIOR_SHY);
            else
                walkForward(1);
            break;

        case BEHAVIOR_SHY:
            GPIOF->DATA = RED;
            shy();
            EnterState(BEHAVIOR_IDLE);
            break;

        case BEHAVIOR_EVADE:
            GPIOF->DATA = RED | BLUE;
            runToHide();
            EnterState(BEHAVIOR_IDLE);
            break;
    }
}
