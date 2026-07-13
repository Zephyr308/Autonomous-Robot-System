/**
 * @file    head_hw.c
 * @brief   Ultrasonic sensor hardware driver.
 */


#include "TM4C123GH6PM.h"
#include "head_hw.h"



/*----------------------------------------------------------
 * Timer configuration
 *---------------------------------------------------------*/

#define TIMER_CAPTURE_FLAG   (1U << 2)



/*----------------------------------------------------------
 * Initialize ultrasonic hardware
 *---------------------------------------------------------*/

void HEAD_HW_Init(void)
{

    /*
     * Enable GPIO Port A
     */

    SYSCTL->RCGCGPIO |= (1U << 0);



    /*
     * Enable GPIO Port B
     */

    SYSCTL->RCGCGPIO |= (1U << 1);



    /*
     * Enable Timer0
     */

    SYSCTL->RCGCTIMER |= (1U << 0);



    /*
     * Allow clocks to stabilize
     */

    (void)SYSCTL->RCGCGPIO;
    (void)SYSCTL->RCGCTIMER;



    /*
     * -------------------------
     * Trigger PA4
     * -------------------------
     */


    GPIOA->AFSEL &= ~HEAD_TRIGGER_PIN;

    GPIOA->PCTL &= ~(0xF << 16);

    GPIOA->AMSEL &= ~HEAD_TRIGGER_PIN;


    GPIOA->DIR |= HEAD_TRIGGER_PIN;

    GPIOA->DEN |= HEAD_TRIGGER_PIN;



    /*
     * -------------------------
     * Echo PB6
     * -------------------------
     */


    GPIOB->DIR &= ~HEAD_ECHO_PIN;

    GPIOB->DEN |= HEAD_ECHO_PIN;


    /*
     * Timer capture function
     */

    GPIOB->AFSEL |= HEAD_ECHO_PIN;

    GPIOB->PCTL &= ~(0xF << 24);

    GPIOB->PCTL |= (0x7 << 24);


    /*
     * -------------------------
     * Timer0A capture setup
     * -------------------------
     */


    TIMER0->CTL &= ~1;


    /*
     * 16-bit timer configuration
     */

    TIMER0->CFG = 4;


    /*
     * Edge-time capture mode
     */

    TIMER0->TAMR = 0x17;


    /*
     * Capture both edges
     */

    TIMER0->CTL |= (0x3 << 2);



    /*
     * Start timer
     */

    TIMER0->CTL |= 1;



    /*
     * Initial trigger state
     */

    GPIOA->DATA &= ~HEAD_TRIGGER_PIN;
}



/*----------------------------------------------------------
 * Trigger pulse
 *---------------------------------------------------------*/

void HEAD_HW_Trigger(void)
{

    GPIOA->DATA &= ~HEAD_TRIGGER_PIN;


    /*
     * This will temporarily remain a micro delay.
     * Later replace with timer based pulse.
     */

    for(volatile uint32_t i = 0; i < 80; i++);


    GPIOA->DATA |= HEAD_TRIGGER_PIN;


    for(volatile uint32_t i = 0; i < 80; i++);


    GPIOA->DATA &= ~HEAD_TRIGGER_PIN;

}



/*----------------------------------------------------------
 * Echo handling
 *---------------------------------------------------------*/

uint8_t HEAD_HW_EchoReady(void)
{
    return
    (
        TIMER0->RIS & TIMER_CAPTURE_FLAG
    )
    ? 1U : 0U;
}



uint32_t HEAD_HW_ReadCapture(void)
{
    return TIMER0->TAR;
}



void HEAD_HW_ClearCapture(void)
{
    TIMER0->ICR = TIMER_CAPTURE_FLAG;
}
