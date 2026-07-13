/**
 * @file    neck.h
 * @brief   Interface for PWM-based servo (neck) control.
 *
 * This module provides functions to initialize the PWM hardware,
 * position the servo, and perform predefined left and right sweep
 * operations.
 */

#ifndef NECK_H_
#define NECK_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize the PWM peripheral for servo control.
 *
 * Configures PWM Module 1 Generator 3 (M1PWM7) on PF3 to generate
 * a 50 Hz PWM signal suitable for driving a servo motor.
 */
void neck_init(void);

/**
 * @brief Set the servo position.
 *
 * Writes a PWM compare value to the servo output. The valid range
 * depends on the configured servo limits.
 *
 * @param position PWM compare value corresponding to the desired
 *                 servo position.
 */
void neck_turn(uint32_t position);

/**
 * @brief Sweep the servo from the left limit to the right limit.
 *
 * The servo moves incrementally with a fixed delay between steps.
 */
void check_left(void);

/**
 * @brief Sweep the servo from the right limit to the left limit.
 *
 * The servo moves incrementally with a fixed delay between steps.
 */
void check_right(void);

#ifdef __cplusplus
}
#endif

#endif /* NECK_H_ */
