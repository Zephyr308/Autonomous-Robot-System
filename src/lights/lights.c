/**
 * @file lights.c
 * @brief RGB LED driver.
 */


#include "TM4C123GH6PM.h"

#include "lights.h"



/*
 * Current LED state
 */

static uint8_t led_state;



/*
 *---------------------------------------------------------
 * Initialize GPIO Port F LEDs
 *---------------------------------------------------------
 */

void LIGHTS_Init(void)
{

    /*
     * Enable Port F clock
     */

    SYSCTL->RCGCGPIO |=
        (1U << 5);



    /*
     * Wait for peripheral ready
     */

    (void)SYSCTL->RCGCGPIO;



    /*
     * Unlock PF1-3
     *
     * Original assembly unlocked
     * entire Port F.
     */

    GPIOF->LOCK =
        0x4C4F434B;



    GPIOF->CR |=
        LED_ALL;



    /*
     * Configure output
     */

    GPIOF->DIR |=
        LED_ALL;



    /*
     * Disable alternate function
     */

    GPIOF->AFSEL &=
        ~LED_ALL;



    /*
     * Enable digital
     */

    GPIOF->DEN |=
        LED_ALL;



    /*
     * Start OFF
     */

    led_state = 0;


    LIGHTS_Off();

}



/*
 *---------------------------------------------------------
 * Write LED state
 *---------------------------------------------------------
 */

static void LIGHTS_Write
(
    uint8_t value
)
{

    led_state =
        value &
        LED_ALL;


    GPIOF->DATA =
        (GPIOF->DATA &
        ~LED_ALL)
        |
        led_state;

}



/*
 *---------------------------------------------------------
 * Turn LEDs on
 *---------------------------------------------------------
 */

void LIGHTS_On
(
    uint8_t color
)
{

    LIGHTS_Write(
        led_state | color
    );

}



/*
 *---------------------------------------------------------
 * Turn LEDs off
 *---------------------------------------------------------
 */

void LIGHTS_Off(void)
{

    LIGHTS_Write(0);

}



/*
 *---------------------------------------------------------
 * Toggle LEDs
 *---------------------------------------------------------
 */

void LIGHTS_Toggle
(
    uint8_t color
)
{

    LIGHTS_Write(
        led_state ^ color
    );

}



/*
 *---------------------------------------------------------
 * RGB control
 *---------------------------------------------------------
 */

void LIGHTS_RGB
(
    uint8_t red,
    uint8_t green,
    uint8_t blue
)
{

    uint8_t value = 0;



    if(red)
    {
        value |= LED_RED;
    }


    if(green)
    {
        value |= LED_GREEN;
    }


    if(blue)
    {
        value |= LED_BLUE;
    }



    LIGHTS_Write(value);

}



/*
 *---------------------------------------------------------
 * Scheduler task
 *
 * Currently unused.
 *
 * Future:
 * - breathing effect
 * - status indication
 * - sensor feedback
 *
 *---------------------------------------------------------
 */

void LIGHTS_Update(void)
{

    /*
     * Reserved.
     */

}
