/**
 * @file neck.h
 * @brief Servo neck control interface.
 */


#ifndef NECK_H_
#define NECK_H_


#include <stdint.h>



/*
 * Servo limits.
 *
 * Adjust experimentally.
 */

#define NECK_LEFT_POSITION     319000U

#define NECK_CENTER_POSITION   160000U

#define NECK_RIGHT_POSITION    1000U



/**
 * @brief Initialize neck servo PWM.
 */
void NECK_Init(void);



/**
 * @brief Scheduler update.
 *
 * Call every 10-20ms.
 */
void NECK_Update(void);



/**
 * @brief Move servo to target position.
 *
 * @param position PWM compare value
 */
void NECK_SetPosition
(
    uint32_t position
);



/**
 * @brief Move servo left.
 */
void NECK_Left(void);



/**
 * @brief Move servo right.
 */
void NECK_Right(void);



/**
 * @brief Move servo center.
 */
void NECK_Center(void);



/**
 * @brief Get current position.
 */
uint32_t NECK_GetPosition(void);



#endif
