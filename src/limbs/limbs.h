/**
 * @file limbs.h
 * @brief High level robot movement control.
 */


#ifndef LIMBS_H_
#define LIMBS_H_


#include <stdint.h>



typedef enum
{

    LIMB_CMD_STOP = 0,

    LIMB_CMD_FORWARD,

    LIMB_CMD_LEFT,

    LIMB_CMD_RIGHT


} LimbCommand;



/**
 * @brief Initialize limb controller.
 */
void LIMBS_Init(void);



/**
 * @brief Scheduler update.
 *
 * Call every 10ms.
 */
void LIMBS_Update(void);



/**
 * @brief Set continuous movement.
 *
 * @param command movement type
 */
void LIMBS_Command
(
    LimbCommand command
);



/**
 * @brief Move for a specific time.
 *
 * After duration expires,
 * robot stops automatically.
 *
 * @param command movement
 * @param duration_ms time
 */
void LIMBS_CommandTimed
(
    LimbCommand command,
    uint32_t duration_ms
);



/**
 * @brief Stop immediately.
 */
void LIMBS_Stop(void);



/**
 * @brief Check current command.
 */
LimbCommand LIMBS_GetCommand(void);



#endif
