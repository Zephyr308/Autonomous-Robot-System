/**
 * @file limbs.c
 * @brief High level non-blocking movement controller.
 */


#include "limbs.h"

#include "limb_hw.h"

#include "timing.h"



/*
 * Current movement command
 */

static LimbCommand current_command;



/*
 * Timed movement control
 */

static uint8_t timed_mode;


static uint32_t command_start;


static uint32_t command_duration;



/*
 *---------------------------------------------------------
 * Initialize
 *---------------------------------------------------------
 */

void LIMBS_Init(void)
{

    LIMB_HW_Init();



    current_command =
        LIMB_CMD_STOP;



    timed_mode = 0;


    command_start = 0;


    command_duration = 0;



    LIMB_HW_Stop();

}



/*
 *---------------------------------------------------------
 * Send continuous command
 *---------------------------------------------------------
 */

void LIMBS_Command
(
    LimbCommand command
)
{

    current_command = command;


    timed_mode = 0;

}



/*
 *---------------------------------------------------------
 * Send timed command
 *---------------------------------------------------------
 */

void LIMBS_CommandTimed
(
    LimbCommand command,
    uint32_t duration_ms
)
{

    current_command = command;


    command_duration =
        duration_ms;


    command_start =
        TIMING_GetMillis();



    timed_mode = 1;

}



/*
 *---------------------------------------------------------
 * Stop
 *---------------------------------------------------------
 */

void LIMBS_Stop(void)
{

    current_command =
        LIMB_CMD_STOP;


    timed_mode = 0;



    LIMB_HW_Stop();

}



/*
 *---------------------------------------------------------
 * Scheduler update
 *
 * Runs every 10ms
 *---------------------------------------------------------
 */

void LIMBS_Update(void)
{


    /*
     * Handle timed movement
     */

    if(timed_mode)
    {

        if((TIMING_GetMillis()
            -
            command_start)
            >= command_duration)
        {

            LIMBS_Stop();

            return;

        }

    }



    /*
     * Apply command
     */

    switch(current_command)
    {


        case LIMB_CMD_FORWARD:

            LIMB_HW_Forward();

            break;



        case LIMB_CMD_LEFT:

            LIMB_HW_Left();

            break;



        case LIMB_CMD_RIGHT:

            LIMB_HW_Right();

            break;



        case LIMB_CMD_STOP:

        default:

            LIMB_HW_Stop();

            break;

    }


}



/*
 *---------------------------------------------------------
 * Read current state
 *---------------------------------------------------------
 */

LimbCommand LIMBS_GetCommand(void)
{

    return current_command;

}
