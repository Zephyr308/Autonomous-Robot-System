/**
 * @file robot.c
 * @brief Robot autonomous behaviour.
 */


#include "robot.h"

#include "limbs.h"

#include "head.h"

#include "tail.h"

#include "timing.h"



/*
 * Detection thresholds
 */

#define FRONT_LIMIT_CM      7U



/*
 * Behaviour state
 */

static RobotState robot_state;



/*
 *---------------------------------------------------------
 * Initialize robot
 *---------------------------------------------------------
 */

void ROBOT_Init(void)
{

    robot_state =
        ROBOT_IDLE;


    LIMBS_Stop();

}



/*
 *---------------------------------------------------------
 * Robot update
 *
 * Called by scheduler
 *
 * Example:
 * 50ms period
 *
 *---------------------------------------------------------
 */

void ROBOT_Update(void)
{

    uint32_t distance;


    uint8_t rear;



    distance =
        HEAD_GetDistance();



    rear =
        TAIL_Read();



    /*
     * -------------------------
     * Obstacle decision logic
     * -------------------------
     */


    /*
     * Both sensors detect obstacle
     */

    if(
        (rear == 1U) &&
        (distance < FRONT_LIMIT_CM)
      )
    {

        robot_state =
            ROBOT_ESCAPE;


        LIMBS_CommandTimed(
            LIMB_CMD_LEFT,
            1000
        );


    }



    /*
     * Front obstacle only
     */

    else if(distance < FRONT_LIMIT_CM)
    {

        robot_state =
            ROBOT_AVOID_FRONT;



        /*
         * Turn away
         */

        LIMBS_CommandTimed(
            LIMB_CMD_LEFT,
            1500
        );


    }



    /*
     * Rear obstacle only
     */

    else if(rear == 1U)
    {

        robot_state =
            ROBOT_AVOID_REAR;



        LIMBS_CommandTimed(
            LIMB_CMD_RIGHT,
            1000
        );


    }



    /*
     * Nothing detected
     */

    else
    {

        robot_state =
            ROBOT_FORWARD;



        LIMBS_Command(
            LIMB_CMD_FORWARD
        );

    }


}



/*
 *---------------------------------------------------------
 * Return state
 *---------------------------------------------------------
 */

RobotState ROBOT_GetState(void)
{

    return robot_state;

}
