/**
 * @file tail.c
 * @brief Rear IR sensor driver.
 */


#include "TM4C123GH6PM.h"

#include "tail.h"



/*
 *---------------------------------------------------------
 * Initialize PA5 as digital input
 *---------------------------------------------------------
 */

void TAIL_Init(void)
{

    /*
     * Enable GPIO Port A clock
     */

    SYSCTL->RCGCGPIO |=
        (1U << 0);



    /*
     * Wait for peripheral ready
     */

    (void)SYSCTL->RCGCGPIO;



    /*
     * Disable alternate function
     */

    GPIOA->AFSEL &=
        ~TAIL_IR_PIN;



    /*
     * Disable analog mode
     */

    GPIOA->AMSEL &=
        ~TAIL_IR_PIN;



    /*
     * Configure input
     */

    GPIOA->DIR &=
        ~TAIL_IR_PIN;



    /*
     * Enable digital input
     */

    GPIOA->DEN |=
        TAIL_IR_PIN;


}



/*
 *---------------------------------------------------------
 * Read IR sensor
 *---------------------------------------------------------
 */

uint8_t TAIL_Read(void)
{

    if(GPIOA->DATA & TAIL_IR_PIN)
    {
        return 1U;
    }


    return 0U;

}
