/**
 * @file neck.c
 * @brief PWM servo neck controller.
 */


#include "TM4C123GH6PM.h"

#include "neck.h"



/*
 * PWM configuration
 *
 * PWM1 Generator 3
 * M1PWM7
 *
 * PF3
 */


#define NECK_PWM_LOAD     320000U



/*
 * Servo update speed.
 *
 * Smaller:
 * faster movement
 *
 */

#define NECK_STEP         3000U



/*
 * Internal position
 */

static uint32_t current_position;


static uint32_t target_position;



/*
 *---------------------------------------------------------
 * Initialize PWM servo
 *---------------------------------------------------------
 */

void NECK_Init(void)
{

    /*
     * Enable PWM1
     */

    SYSCTL->RCGCPWM |=
        (1U << 1);



    /*
     * Enable Port F
     */

    SYSCTL->RCGCGPIO |=
        (1U << 5);



    (void)SYSCTL->RCGCPWM;



    /*
     * PWM clock = system clock
     */

    SYSCTL->RCC &=
        ~(1U << 20);



    /*
     * PF3 alternate function
     */

    GPIOF->AFSEL |=
        (1U << 3);



    GPIOF->PCTL &=
        ~(0xF << 12);



    /*
     * PF3 = M1PWM7
     */

    GPIOF->PCTL |=
        (5U << 12);



    GPIOF->DEN |=
        (1U << 3);



    /*
     * Disable PWM generator
     */

    PWM1->_3_CTL = 0;



    /*
     * PWM output configuration
     */

    PWM1->_3_GENB =
        0x0000008C;



    /*
     * 50Hz servo frequency
     */

    PWM1->_3_LOAD =
        NECK_PWM_LOAD;



    /*
     * Start center
     */

    current_position =
        NECK_CENTER_POSITION;


    target_position =
        NECK_CENTER_POSITION;



    PWM1->_3_CMPA =
        current_position;



    PWM1->_3_CTL = 1;



    PWM1->ENABLE |=
        (1U << 7);

}



/*
 *---------------------------------------------------------
 * Set target
 *---------------------------------------------------------
 */

void NECK_SetPosition
(
    uint32_t position
)
{

    /*
     * Limit command
     */

    if(position > NECK_LEFT_POSITION)
    {
        position = NECK_LEFT_POSITION;
    }


    if(position < NECK_RIGHT_POSITION)
    {
        position = NECK_RIGHT_POSITION;
    }



    target_position =
        position;

}



/*
 *---------------------------------------------------------
 * Scheduler update
 *
 * Servo moves gradually
 *---------------------------------------------------------
 */

void NECK_Update(void)
{

    if(current_position < target_position)
    {

        current_position +=
            NECK_STEP;


        if(current_position > target_position)
        {
            current_position =
                target_position;
        }

    }


    else if(current_position > target_position)
    {

        current_position -=
            NECK_STEP;


        if(current_position < target_position)
        {
            current_position =
                target_position;
        }

    }



    PWM1->_3_CMPA =
        current_position;

}



/*
 *---------------------------------------------------------
 * Convenience commands
 *---------------------------------------------------------
 */

void NECK_Left(void)
{

    NECK_SetPosition(
        NECK_LEFT_POSITION
    );

}



void NECK_Right(void)
{

    NECK_SetPosition(
        NECK_RIGHT_POSITION
    );

}



void NECK_Center(void)
{

    NECK_SetPosition(
        NECK_CENTER_POSITION
    );

}



/*
 *---------------------------------------------------------
 * Get current position
 *---------------------------------------------------------
 */

uint32_t NECK_GetPosition(void)
{

    return current_position;

}
