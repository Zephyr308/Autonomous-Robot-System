/**
 * @file    tail.c
 * @brief   Rear IR sensor driver.
 *
 * This module provides initialization and sensing functions for the
 * rear infrared (IR) sensor connected to GPIO Port A Pin 5 (PA5).
 */

#include "TM4C123GH6PM.h"
#include "tail.h"

/**
 * @brief Initialize the rear IR sensor.
 *
 * Configures PA5 as a digital GPIO input.
 */
void TAIL_Init(void)
{
    /*----------------------------------------------------------
     * Enable clock for GPIO Port A
     *---------------------------------------------------------*/
    SYSCTL->RCGCGPIO |= (1U << 0);

    /* Allow time for the peripheral clock to stabilize */
    (void)SYSCTL->RCGCGPIO;

    /*----------------------------------------------------------
     * Configure PA5 as a GPIO input
     *---------------------------------------------------------*/

    /* Disable alternate function */
    GPIOA->AFSEL &= ~IR_PIN;

    /* Select GPIO function */
    GPIOA->PCTL &= ~(0xFU << 20);

    /* Disable analog mode */
    GPIOA->AMSEL &= ~IR_PIN;

    /* Configure as input */
    GPIOA->DIR &= ~IR_PIN;

    /* Enable digital function */
    GPIOA->DEN |= IR_PIN;
}

/**
 * @brief Read the rear IR sensor.
 *
 * @return
 * - IR_PIN (0x20) if PA5 is HIGH.
 * - 0x00 if PA5 is LOW.
 */
uint32_t TAIL_sense(void)
{
    return (GPIOA->DATA & IR_PIN);
}
