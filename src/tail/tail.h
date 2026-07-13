/**
 * @file tail.h
 * @brief Rear IR sensor interface.
 *
 * The tail sensor is an IR obstacle detector
 * connected to GPIOA PA5.
 */


#ifndef TAIL_H_
#define TAIL_H_


#include <stdint.h>



/*
 * Tail IR input pin
 */

#define TAIL_IR_PIN      (1U << 5)     /* PA5 */



/**
 * @brief Initialize tail IR sensor.
 */
void TAIL_Init(void);



/**
 * @brief Read tail sensor state.
 *
 * @return
 * 1 = obstacle detected
 * 0 = no obstacle
 */
uint8_t TAIL_Read(void);



#endif /* TAIL_H_ */
