#include "TM4C123GH6PM.h"
#include "head.h"

volatile uint32_t head_distance = 0;

/* Timer0 Capture Interrupt Handler */
void TIMER0A_Handler(void){
    static uint32_t rising_edge = 0;
    if(TIMER0->RIS & 0x04){ // Capture event
        uint32_t tar = TIMER0->TAR;
        if((GPIOB->DATA & (1<<6))){ // Rising edge
            rising_edge = tar;
        } else { // Falling edge
            uint32_t pulse = tar - rising_edge;
            head_distance = (uint32_t)(pulse * 62.5e-9 * 5882); // cm
        }
        TIMER0->ICR = 0x04;
    }
}

void HEAD_Init(void){
    /* Setup GPIOA Trigger pin */
    GPIO_PORTA_DIR_R |= (1U<<4);
    GPIO_PORTA_DEN_R |= (1U<<4);

    /* Setup GPIOB Echo pin and Timer0 capture */
    SYSCTL->RCGCTIMER |= 1;
    SYSCTL->RCGCGPIO |= 2;
    GPIOB->DIR &= ~(1<<6);
    GPIOB->DEN |= (1<<6);
    GPIOB->AFSEL |= (1<<6);
    GPIOB->PCTL &= ~0x0F000000;
    GPIOB->PCTL |= 0x07000000;

    TIMER0->CTL = 0;
    TIMER0->CFG = 4;
    TIMER0->TAMR = 0x17;
    TIMER0->CTL |= 0x0C;
    TIMER0->IMR |= 0x04;
    NVIC->ISER[0] |= (1<<19); // Enable Timer0A interrupt
    TIMER0->CTL |= 1;
}

/**@brief Send trigger pulse */
void head_trigger(void){
    GPIOA->DATA &= ~(1<<4);
    for(volatile int i=0;i<12;i++);
    GPIOA->DATA |= (1<<4);
    for(volatile int i=0;i<12;i++);
    GPIOA->DATA &= ~(1<<4);
}

/**@brief Return last measured distance */
uint32_t head_getDistance(void){
    head_trigger(); // Non-blocking, measurement updated in ISR
    return head_distance;
}
