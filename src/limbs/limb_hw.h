/**
 * @file    limb_hw.h
 * @brief   Low-level limb motor hardware driver.
 *
 * This module controls the motor hardware directly.
 *
 * Hardware:
 *   PE2 - Motor left control
 *   PE3 - Motor right control
 *
 * Speed control is handled using PWM.
 */

#ifndef LIMB_HW_H_
#define LIMB_HW_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


/*----------------------------------------------------------
 * Motor speed range
 *---------------------------------------------------------*/

#define LIMB_SPEED_STOP       0U
#define LIMB_SPEED_MAX        100U


/*----------------------------------------------------------
 * Hardware API
 *---------------------------------------------------------*/


/**
 * @brief Initialize limb motor hardware.
 *
 * Configures GPIO and PWM peripherals.
 */
void LIMB_HW_Init(void);


/**
 * @brief Move forward.
 *
 * @param speed Motor speed percentage (0-100).
 */
void LIMB_HW_Forward(uint8_t speed);


/**
 * @brief Move backward.
 *
 * @param speed Motor speed percentage (0-100).
 */
void LIMB_HW_Backward(uint8_t speed);


/**
 * @brief Turn left.
 *
 * @param speed Motor speed percentage (0-100).
 */
void LIMB_HW_Left(uint8_t speed);


/**
 * @brief Turn right.
 *
 * @param speed Motor speed percentage (0-100).
 */
void LIMB_HW_Right(uint8_t speed);


/**
 * @brief Stop motors immediately.
 */
void LIMB_HW_Stop(void);


#ifdef __cplusplus
}
#endif


#endif /* LIMB_HW_H_ */
