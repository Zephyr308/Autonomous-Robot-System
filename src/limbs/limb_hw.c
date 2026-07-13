/**
 * @file limb_hw.c
 * @brief DC motor hardware implementation.
 */


#include "TM4C123GH6PM.h"

#include "limb_hw.h"



/*
 *---------------------------------------------------------
 * Initialize GPIO Port E motor pins
 *---------------------------------------------------------
 */

void LIMB_HW_Init(void)
{

    /*
     * Enable Port E clock
     */

    SYSCTL->RCGCGPIO |=
        (1U << 4);



    /*
     * Small delay for clock stabilization
     */

    (void)SYSCTL->RCGCGPIO;



    /*
     * Disable alternate function
     */

    GPIOE->AFSEL &=
        ~(LIMB_LEFT_PIN |
          LIMB_RIGHT_PIN);



    /*
     * Configure as GPIO
     */

    GPIOE->PCTL &=
        ~0x0000FF00;



    /*
     * Output direction
     */

    GPIOE->DIR |=
        (LIMB_LEFT_PIN |
         LIMB_RIGHT_PIN);



    /*
     * Enable digital function
     */

    GPIOE->DEN |=
        (LIMB_LEFT_PIN |
         LIMB_RIGHT_PIN);



    /*
     * 8mA drive strength
     *
     * Same as original assembly.
     */

    GPIOE->DR8R |=
        (LIMB_LEFT_PIN |
         LIMB_RIGHT_PIN);



    /*
     * Start stopped.
     */

    LIMB_HW_Stop();

}



/*
 *---------------------------------------------------------
 * Write raw motor output
 *---------------------------------------------------------
 */

void LIMB_HW_Write(uint8_t value)
{

    GPIOE->DATA =
        (GPIOE->DATA &
        ~(LIMB_LEFT_PIN |
          LIMB_RIGHT_PIN))
        |
        (value &
        (LIMB_LEFT_PIN |
         LIMB_RIGHT_PIN));

}



/*
 *---------------------------------------------------------
 * Movement commands
 *---------------------------------------------------------
 */


void LIMB_HW_Left(void)
{

    LIMB_HW_Write(
        LIMB_LEFT_VALUE
    );

}



void LIMB_HW_Right(void)
{

    LIMB_HW_Write(
        LIMB_RIGHT_VALUE
    );

}



void LIMB_HW_Forward(void)
{

    LIMB_HW_Write(
        LIMB_FORWARD_VALUE
    );

}



void LIMB_HW_Stop(void)
{

    LIMB_HW_Write(
        LIMB_STOP_VALUE
    );

}
