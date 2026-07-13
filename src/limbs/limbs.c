/**
 * @file    limbs.c
 * @brief   Limb movement state machine.
 */


#include "limbs.h"
#include "limb_hw.h"



#define LIMB_TICK_MS     10U



typedef struct
{
    LimbCommand command;

    uint8_t target_speed;

    uint8_t current_speed;

    uint32_t duration;

    uint32_t elapsed;

} LimbState;



static LimbState limb;



/*
 * Smooth acceleration.
 */
static void LIMBS_UpdateSpeed(void)
{
    if(limb.current_speed < limb.target_speed)
    {
        limb.current_speed++;
    }
    else if(limb.current_speed > limb.target_speed)
    {
        limb.current_speed--;
    }
}



/*
 * Apply current command to hardware.
 */
static void LIMBS_ApplyCommand(void)
{

    switch(limb.command)
    {

        case LIMB_FORWARD:

            LIMB_HW_Forward(
                limb.current_speed
            );

            break;



        case LIMB_BACKWARD:

            LIMB_HW_Backward(
                limb.current_speed
            );

            break;



        case LIMB_LEFT:

            LIMB_HW_Left(
                limb.current_speed
            );

            break;



        case LIMB_RIGHT:

            LIMB_HW_Right(
                limb.current_speed
            );

            break;



        case LIMB_SPIN_LEFT:

            LIMB_HW_Left(
                limb.current_speed
            );

            break;



        case LIMB_SPIN_RIGHT:

            LIMB_HW_Right(
                limb.current_speed
            );

            break;



        case LIMB_STOP:

        default:

            LIMB_HW_Stop();

            break;
    }

}



/*
 * Initialize controller
 */

void LIMBS_Init(void)
{
    limb.command = LIMB_STOP;

    limb.target_speed = 0;

    limb.current_speed = 0;

    limb.duration = 0;

    limb.elapsed = 0;


    LIMB_HW_Init();
}



/*
 * Main 10ms update function.
 */

void LIMBS_Update(void)
{

    /*
     * Smooth speed change
     */

    LIMBS_UpdateSpeed();



    /*
     * Update motor hardware
     */

    LIMBS_ApplyCommand();



    /*
     * Update timer
     */

    if(limb.command != LIMB_STOP)
    {

        limb.elapsed += LIMB_TICK_MS;


        if(limb.elapsed >= limb.duration)
        {
            LIMBS_Stop();
        }

    }

}



/*
 * Start movement
 */

void LIMBS_Command
(
    LimbCommand command,
    uint8_t speed,
    uint32_t time_ms
)
{

    limb.command = command;

    limb.target_speed = speed;

    limb.duration = time_ms;

    limb.elapsed = 0;

}



/*
 * Emergency stop
 */

void LIMBS_Stop(void)
{

    limb.command = LIMB_STOP;

    limb.target_speed = 0;

    limb.duration = 0;

    limb.elapsed = 0;

}



/*
 * Check movement status
 */

uint8_t LIMBS_IsFinished(void)
{

    return
    (
        limb.command == LIMB_STOP
    );

}
