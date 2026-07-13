/**
 * @file    limb_hw.c
 * @brief   Low-level limb motor hardware control.
 */


#include "TM4C123GH6PM.h"
#include "limb_hw.h"


/*----------------------------------------------------------
 * GPIO configuration
 *---------------------------------------------------------*/

#define MOTOR_LEFT_PIN       (1U << 2)   /* PE2 */
#define MOTOR_RIGHT_PIN      (1U << 3)   /* PE3 */

#define MOTOR_PIN_MASK       \
        (MOTOR_LEFT_PIN | MOTOR_RIGHT_PIN)



/*----------------------------------------------------------
 * Internal functions
 *---------------------------------------------------------*/


static void LIMB_HW_SetPWM(uint8_t speed)
{
    /*
     * Future PWM implementation.
     *
     * speed:
     * 0   = stop
     * 100 = full speed
     */

    (void)speed;
}



/*----------------------------------------------------------
 * Initialization
 *---------------------------------------------------------*/


void LIMB_HW_Init(void)
{
    /*
     * Enable Port E clock
     */
    SYSCTL->RCGCGPIO |= (1U << 4);

    /*
     * Allow clock stabilization
     */
    (void)SYSCTL->RCGCGPIO;



    /*
     * Configure PE2 and PE3 as GPIO
     */

    GPIOE->AFSEL &= ~MOTOR_PIN_MASK;

    GPIOE->PCTL &= ~(0xFF << 8);

    GPIOE->AMSEL &= ~MOTOR_PIN_MASK;


    /*
     * Output pins
     */

    GPIOE->DIR |= MOTOR_PIN_MASK;


    /*
     * Increase drive strength
     */

    GPIOE->DR8R |= MOTOR_PIN_MASK;


    /*
     * Digital enable
     */

    GPIOE->DEN |= MOTOR_PIN_MASK;


    /*
     * Initial safe state
     */

    LIMB_HW_Stop();
}



/*----------------------------------------------------------
 * Movement commands
 *---------------------------------------------------------*/


void LIMB_HW_Forward(uint8_t speed)
{
    GPIOE->DATA =
        (GPIOE->DATA & ~MOTOR_PIN_MASK)
        | MOTOR_PIN_MASK;

    LIMB_HW_SetPWM(speed);
}



void LIMB_HW_Backward(uint8_t speed)
{
    /*
     * Direction depends on motor wiring.
     * Placeholder until H-bridge logic is defined.
     */

    GPIOE->DATA =
        (GPIOE->DATA & ~MOTOR_PIN_MASK)
        | MOTOR_PIN_MASK;


    LIMB_HW_SetPWM(speed);
}



void LIMB_HW_Left(uint8_t speed)
{
    GPIOE->DATA =
        (GPIOE->DATA & ~MOTOR_PIN_MASK)
        | MOTOR_LEFT_PIN;


    LIMB_HW_SetPWM(speed);
}



void LIMB_HW_Right(uint8_t speed)
{
    GPIOE->DATA =
        (GPIOE->DATA & ~MOTOR_PIN_MASK)
        | MOTOR_RIGHT_PIN;


    LIMB_HW_SetPWM(speed);
}



void LIMB_HW_Stop(void)
{
    GPIOE->DATA &= ~MOTOR_PIN_MASK;

    LIMB_HW_SetPWM(0);
}
