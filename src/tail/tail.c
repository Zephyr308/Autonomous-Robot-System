#include "tail.h"

volatile uint8_t tail_flag = 0;

void TAIL_Init(void){
    TAIL_sense(); // assembly sets up PA5
}

/* Non-blocking check */
uint8_t tail_obstacle(void){
    return (TAIL_sense() != 0);
}
