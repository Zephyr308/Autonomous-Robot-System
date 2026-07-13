/**
 * @file    lights.c
 * @brief   LED control driver for TM4C123GH6PM.
 *
 * This module controls the onboard RGB LEDs connected to:
 *
 * PF1 - Red LED
 * PF2 - Blue LED
 * PF3 - Green LED
 *
 */

#include "TM4C123GH6PM.h"
#include "lights.h"


/*----------------------------------------------------------
 * LED Pin Definitions
 *---------------------------------------------------------*/

#define RED_LED     (1U << 1)    /* PF1 */
#define BLUE_LED    (1U << 2)    /* PF2 */
#define GREEN_LED   (1U << 3)    /* PF3 */

#define LED_MASK    (RED_LED | BLUE_LED | GREEN_LED)


/*----------------------------------------------------------
 * Initialize LEDs
 *---------------------------------------------------------*/

void LIGHTS_Init(void)
{
    /* Enable Port F clock */
    SYSCTL->RCGCGPIO |= (1U << 5);

    /* Allow GPIO clock to stabilize */
    (void)SYSCTL->RCGCGPIO;


    /*
     * Unlock Port F
     * Required for PF0 and PF4.
     * Kept here for compatibility with LaunchPad Port F setup.
     */
    GPIOF->LOCK = 0x4C4F434B;
    GPIOF->CR |= 0xFF;


    /* Configure PF1-PF3 as GPIO */
    GPIOF->AFSEL &= ~LED_MASK;
    GPIOF->PCTL &= ~0x0000FFF0;
    GPIOF->AMSEL &= ~LED_MASK;


    /* Configure LED pins as outputs */
    GPIOF->DIR |= LED_MASK;


    /* Enable digital function */
    GPIOF->DEN |= LED_MASK;


    /* Turn LEDs OFF initially */
    GPIOF->DATA &= ~LED_MASK;
}


/*----------------------------------------------------------
 * LED Control Functions
 *---------------------------------------------------------*/

/**
 * @brief Turn on selected LEDs.
 *
 * @param led LED mask:
 *            RED_LED, BLUE_LED, GREEN_LED
 */
void LIGHTS_On(uint8_t led)
{
    GPIOF->DATA |= (led & LED_MASK);
}


/**
 * @brief Turn off selected LEDs.
 *
 * @param led LED mask:
 *            RED_LED, BLUE_LED, GREEN_LED
 */
void LIGHTS_Off(uint8_t led)
{
    GPIOF->DATA &= ~(led & LED_MASK);
}


/**
 * @brief Toggle selected LEDs.
 *
 * @param led LED mask:
 *            RED_LED, BLUE_LED, GREEN_LED
 */
void LIGHTS_Toggle(uint8_t led)
{
    GPIOF->DATA ^= (led & LED_MASK);
}


/**
 * @brief Set RGB LED state directly.
 *
 * @param color LED mask combination.
 */
void LIGHTS_Set(uint8_t color)
{
    GPIOF->DATA = (GPIOF->DATA & ~LED_MASK) |
                  (color & LED_MASK);
}
