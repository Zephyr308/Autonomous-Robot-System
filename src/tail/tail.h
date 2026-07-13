/**
 * @file    tail.h
 * @brief   Interface for the rear IR sensor (tail sensor).
 *
 * This module provides functions to initialize the rear infrared
 * sensor connected to GPIO Port A Pin 5 (PA5) and to read its
 * current logic state.
 */

#ifndef TAIL_H_
#define TAIL_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief GPIO pin connected to the rear IR sensor.
 */
#define IR_PIN    (1U << 5U)    /**< PA5 */

/**
 * @brief Initialize the rear IR sensor.
 *
 * Configures PA5 as a digital GPIO input for reading the sensor.
 */
void TAIL_Init(void);

/**
 * @brief Read the rear IR sensor state.
 *
 * @return Returns the state of PA5:
 * - `0x20` (IR_PIN) if the sensor output is HIGH.
 * - `0x00` if the sensor output is LOW.
 */
uint32_t TAIL_sense(void);

#ifdef __cplusplus
}
#endif

#endif /* TAIL_H_ */
