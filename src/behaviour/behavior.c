#include "behavior.h"
#include "limbs.h"
#include "head.h"
#include "tail.h"
#include "lights.h"

typedef enum {STATE_IDLE, STATE_PLAY, STATE_SHY, STATE_AVOID} RobotState_t;
static RobotState_t robot_state = STATE_IDLE;

void behavior_update(void){
    uint32_t dist = head_getDistance();
    uint8_t tail = tail_obstacle();

    switch(robot_state){
        case STATE_IDLE:
            if(dist<7 || tail) robot_state = STATE_AVOID;
            else robot_state = STATE_PLAY;
            break;

        case STATE_AVOID:
            if(dist<7) turn_left(100); // 1 sec
            else turn_right(100);
            robot_state = STATE_IDLE;
            break;

        case STATE_PLAY:
            move_forward(100); // 1 sec
            robot_state = STATE_IDLE;
            break;

        case STATE_SHY:
            move_forward(70);
            turn_right(180);
            robot_state = STATE_IDLE;
            break;
    }
}
