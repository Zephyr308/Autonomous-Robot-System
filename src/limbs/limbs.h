/**
 * @file    limbs.h
 * @brief   High-level limb movement controller.
 */

#ifndef LIMBS_H_
#define LIMBS_H_

#include <stdint.h>


typedef enum
{
    LIMB_STOP = 0,

    LIMB_FORWARD,

    LIMB_BACKWARD,

    LIMB_LEFT,

    LIMB_RIGHT,

    LIMB_SPIN_LEFT,

    LIMB_SPIN_RIGHT

} LimbCommand;



/**
 * @brief Initialize limb controller.
 */
void LIMBS_Init(void);



/**
 * @brief Update limb controller.
 *
 * Must be called every 10ms.
 */
void LIMBS_Update(void);



/**
 * @brief Start a movement command.
 *
 * @param command Movement type.
 * @param speed Speed percentage.
 * @param time_ms Duration in milliseconds.
 */
void LIMBS_Command
(
    LimbCommand command,
    uint8_t speed,
    uint32_t time_ms
);



/**
 * @brief Immediately stop movement.
 */
void LIMBS_Stop(void);



/**
 * @brief Check if current movement is finished.
 *
 * @return 1 if finished.
 */
uint8_t LIMBS_IsFinished(void);


#endif
