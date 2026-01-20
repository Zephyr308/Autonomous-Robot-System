#include "behavior.h"
#include "head.h"
#include "tail.h"
#include "limbs.h"
#include "lights.h"
#include "delay.h"

static behavior_state_t state;
static uint32_t idle_counter;
static uint32_t state_entry_time;
static uint32_t state_duration;


/* Thresholds are explicit and tunable */
#define OBSTACLE_NEAR   7
#define IDLE_TIMEOUT    3000   // ms

void BEHAVIOR_Init(void)
{
    state = BEHAVIOR_IDLE;
    idle_counter = 0;
}

void Behavior_EnterState(behavior_state_t new_state)
{
    uint32_t now = TIMING_GetTicks();
    state_duration = state_entry_time - now;
    state_entry_time = now;

    LOG_Event(EVENT_STATE_CHANGE, new_state, state_duration);
    state = new_state;
}


void BEHAVIOR_Update(void)
{
    uint8_t head_dist = headSensor_detect();
    bool tail_hit = TAIL_Detected();

    switch (state)
    {
        /* ================= IDLE ================= */
        case BEHAVIOR_IDLE:
            LIGHTS_Set(BLUE);
            STOP();

            idle_counter++;

            if (idle_counter > IDLE_TIMEOUT) {
                idle_counter = 0;
                state = BEHAVIOR_PLAY;
            }
            break;

        /* ================= PLAY ================= */
        case BEHAVIOR_PLAY:
            LIGHTS_Set(GREEN);

            if (head_dist <= OBSTACLE_NEAR && tail_hit) {
                state = BEHAVIOR_EVADE;
            }
            else if (head_dist <= OBSTACLE_NEAR) {
                state = BEHAVIOR_SHY;
            }
            else {
                walkForward(1);
            }
            break;

        /* ================= SHY ================= */
        case BEHAVIOR_SHY:
            LIGHTS_Set(RED);

            shy();                  // your existing routine
            state = BEHAVIOR_IDLE;  // return to calm state
            break;

        /* ================= EVADE ================= */
        case BEHAVIOR_EVADE:
            LIGHTS_Set(RED | BLUE);

            runToHide();            // aggressive evasive action
            state = BEHAVIOR_IDLE;
            break;

        default:
            state = BEHAVIOR_IDLE;
            break;
    }
}
