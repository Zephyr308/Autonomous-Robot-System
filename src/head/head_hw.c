#include "TM4C123GH6PM.h"
#include "head_hw.h"



static volatile uint32_t risingEdge;

static volatile uint32_t fallingEdge;


static volatile uint8_t edgeState;

static volatile uint8_t dataReady;



#define WAIT_RISING   0
#define WAIT_FALLING  1



void HEAD_HW_Init(void)
{

    /*
     * GPIO clocks
     */

    SYSCTL->RCGCGPIO |=
        (1U<<0) | (1U<<1);


    /*
     * Timer0 clock
     */

    SYSCTL->RCGCTIMER |=
        (1U<<0);



    /*
     * Trigger PA4
     */

    GPIOA->DIR |= HEAD_TRIGGER_PIN;

    GPIOA->DEN |= HEAD_TRIGGER_PIN;



    /*
     * Echo PB6
     */

    GPIOB->DIR &= ~HEAD_ECHO_PIN;

    GPIOB->DEN |= HEAD_ECHO_PIN;


    GPIOB->AFSEL |= HEAD_ECHO_PIN;


    GPIOB->PCTL &= ~(0xF<<24);

    GPIOB->PCTL |= (0x7<<24);



    /*
     * Timer0A edge capture
     */

    TIMER0->CTL &= ~1;


    TIMER0->CFG = 4;


    TIMER0->TAMR = 0x17;


    /*
     * Both edges
     */

    TIMER0->CTL |= (3<<2);



    /*
     * Enable capture interrupt
     */

    TIMER0->IMR |= (1<<2);



    /*
     * NVIC enable Timer0A
     */

    NVIC_EnableIRQ(TIMER0A_IRQn);



    TIMER0->CTL |= 1;


    edgeState = WAIT_RISING;

}
