/**
 * @file    head.h
 * @brief   Ultrasonic distance sensor interface.
 */

#ifndef HEAD_H_
#define HEAD_H_

#include <stdint.h>


/**
 * @brief Initialize ultrasonic sensor.
 */
void HEAD_Init(void);


/**
 * @brief Sensor update function.
 *
 * Call periodically (10ms tick).
 */
void HEAD_Update(void);


/**
 * @brief Get latest filtered distance.
 *
 * @return Distance in cm.
 */
uint32_t HEAD_GetDistance(void);


/**
 * @brief Check if a valid measurement exists.
 *
 * @return 1 if available.
 */
uint8_t HEAD_IsReady(void);


#endif
