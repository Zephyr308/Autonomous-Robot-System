/**
 * @file limb_hw.h
 * @brief Low level DC motor hardware driver.
 *
 * Controls motor direction GPIO only.
 */


#ifndef LIMB_HW_H_
#define LIMB_HW_H_


#include <stdint.h>



/*
 * Motor pins
 */

#define LIMB_LEFT_PIN      (1U << 2)   /* PE2 */

#define LIMB_RIGHT_PIN     (1U << 3)   /* PE3 */



/*
 * Motor output states
 */

#define LIMB_STOP_VALUE    0x00

#define LIMB_LEFT_VALUE    LIMB_LEFT_PIN

#define LIMB_RIGHT_VALUE   LIMB_RIGHT_PIN

#define LIMB_FORWARD_VALUE (LIMB_LEFT_PIN | LIMB_RIGHT_PIN)



/**
 * @brief Initialize motor hardware.
 */
void LIMB_HW_Init(void);



/**
 * @brief Turn robot left.
 */
void LIMB_HW_Left(void);



/**
 * @brief Turn robot right.
 */
void LIMB_HW_Right(void);



/**
 * @brief Drive forward.
 */
void LIMB_HW_Forward(void);



/**
 * @brief Stop motors.
 */
void LIMB_HW_Stop(void);



/**
 * @brief Direct motor output.
 *
 * Useful for future PWM/speed control.
 */
void LIMB_HW_Write(uint8_t value);



#endif /* LIMB_HW_H_ */
