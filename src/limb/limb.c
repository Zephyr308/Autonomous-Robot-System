#include "limbs.h"
#include "delay.h"

Motion_t motion = {MOVE_IDLE, 0};

void move_forward(uint32_t duration_ms){
    motion.state = MOVE_FORWARD;
    motion.ticks_remaining = duration_ms/10; // assuming 10ms tick
}

void turn_left(uint32_t duration_ms){
    motion.state = TURN_LEFT_STATE;
    motion.ticks_remaining = duration_ms/10;
}

void turn_right(uint32_t duration_ms){
    motion.state = TURN_RIGHT_STATE;
    motion.ticks_remaining = duration_ms/10;
}

void update_motion(void){
    if(motion.ticks_remaining == 0){
        STOP();
        motion.state = MOVE_IDLE;
        return;
    }

    switch(motion.state){
        case MOVE_FORWARD: FORWARD(); break;
        case TURN_LEFT_STATE: TURN_Left(); break;
        case TURN_RIGHT_STATE: TURN_Right(); break;
        default: STOP(); break;
    }
    motion.ticks_remaining--;
}
