/**
 * @file head_hw.c
 * @brief Ultrasonic hardware driver.
 */


#include "TM4C123GH6PM.h"

#include "head_hw.h"



/*
 * Timer0A capture interrupt flag
 */

#define TIMER0_CAPTURE_FLAG   (1U << 2)



/*
 * Echo edge state
 */

#define EDGE_RISING     0U

#define EDGE_FALLING    1U



static volatile uint32_t rising_edge;

static volatile uint32_t falling_edge;


static volatile uint8_t edge_state;


static volatile uint8_t data_ready;



/*
 *---------------------------------------------------------
 * Initialize hardware
 *---------------------------------------------------------
 */

void HEAD_HW_Init(void)
{

    /*
     * Enable clocks:
     *
     * GPIOA
     * GPIOB
     * TIMER0
     */

    SYSCTL->RCGCGPIO |=
        (1U << 0) |
        (1U << 1);


    SYSCTL->RCGCTIMER |=
        (1U << 0);



    /*
     * Allow clock settling
     */

    (void)SYSCTL->RCGCTIMER;



    /*
     * ------------------------
     * Trigger PA4
     * ------------------------
     */


    GPIOA->DIR |=
        HEAD_TRIGGER_PIN;


    GPIOA->DEN |=
        HEAD_TRIGGER_PIN;


    GPIOA->AFSEL &=
        ~HEAD_TRIGGER_PIN;


    GPIOA->PCTL &=
        ~(0xF << 16);



    GPIOA->DATA &=
        ~HEAD_TRIGGER_PIN;



    /*
     * ------------------------
     * Echo PB6
     * ------------------------
     */


    GPIOB->DIR &=
        ~HEAD_ECHO_PIN;


    GPIOB->DEN |=
        HEAD_ECHO_PIN;



    GPIOB->AFSEL |=
        HEAD_ECHO_PIN;


    GPIOB->PCTL &=
        ~(0xF << 24);


    /*
     * PB6 = T0CCP0
     */

    GPIOB->PCTL |=
        (0x7 << 24);



    /*
     * ------------------------
     * Timer0A capture
     * ------------------------
     */


    TIMER0->CTL = 0;



    /*
     * 16-bit timer mode
     */

    TIMER0->CFG = 4;



    /*
     * Edge time capture
     *
     * Count down
     */

    TIMER0->TAMR = 0x17;



    /*
     * Capture both edges
     */

    TIMER0->CTL |=
        (3U << 2);



    /*
     * Enable capture interrupt
     */

    TIMER0->IMR |=
        TIMER0_CAPTURE_FLAG;



    /*
     * Clear interrupt
     */

    TIMER0->ICR =
        TIMER0_CAPTURE_FLAG;



    /*
     * NVIC enable Timer0A
     */

    NVIC_EnableIRQ(TIMER0A_IRQn);



    /*
     * Start timer
     */

    TIMER0->CTL |= 1;



    edge_state =
        EDGE_RISING;


    data_ready = 0;

}



/*
 *---------------------------------------------------------
 * Trigger ultrasonic burst
 *---------------------------------------------------------
 */

void HEAD_HW_Start(void)
{

    data_ready = 0;



    GPIOA->DATA &=
        ~HEAD_TRIGGER_PIN;



    /*
     * Approx 10us delay.
     *
     * Temporary.
     * Later replace with timer compare.
     */

    for(volatile uint32_t i=0;i<80;i++);



    GPIOA->DATA |=
        HEAD_TRIGGER_PIN;



    for(volatile uint32_t i=0;i<80;i++);



    GPIOA->DATA &=
        ~HEAD_TRIGGER_PIN;

}



/*
 *---------------------------------------------------------
 * Timer0A Interrupt Handler
 *---------------------------------------------------------
 */

void TIMER0A_Handler(void)
{

    /*
     * Clear interrupt
     */

    TIMER0->ICR =
        TIMER0_CAPTURE_FLAG;



    if(edge_state == EDGE_RISING)
    {

        rising_edge =
            TIMER0->TAR;



        edge_state =
            EDGE_FALLING;

    }

    else
    {

        falling_edge =
            TIMER0->TAR;



        data_ready = 1;



        edge_state =
            EDGE_RISING;

    }

}



/*
 *---------------------------------------------------------
 * Get measurement
 *---------------------------------------------------------
 */

uint8_t HEAD_HW_DataReady(void)
{

    return data_ready;

}



uint32_t HEAD_HW_GetEchoTime(void)
{

    return
        rising_edge - falling_edge;

}



void HEAD_HW_ClearData(void)
{

    data_ready = 0;

}
