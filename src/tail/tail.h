/**
 * @file    tail.h
 * @brief   Rear IR sensor (tail sensor) interface.
 *
 * This module provides initialization and sensing functions for the
 * rear infrared (IR) sensor connected to GPIO Port A Pin 5 (PA5).
 *
 * Implementation:
 *  - Current : tail.c (Embedded C)
 *  - Legacy  : tail.s (Assembly, retained for reference)
 */

#ifndef TAIL_H_
#define TAIL_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------
 * Hardware Configuration
 *---------------------------------------------------------*/

/** GPIO pin connected to the rear IR sensor (PA5). */
#define IR_PIN    (1U << 5)

/*----------------------------------------------------------
 * Public API
 *---------------------------------------------------------*/

/**
 * @brief Initialize the rear IR sensor.
 *
 * Configures PA5 as a digital GPIO input.
 */
void TAIL_Init(void);

/**
 * @brief Read the current state of the rear IR sensor.
 *
 * @return Sensor state:
 * - #IR_PIN if PA5 is HIGH.
 * - 0 if PA5 is LOW.
 *
 * Example:
 * @code
 * if (TAIL_sense())
 * {
 *     // Sensor active
 * }
 * @endcode
 */
uint32_t TAIL_sense(void);

#ifdef __cplusplus
}
#endif

#endif /* TAIL_H_ */
