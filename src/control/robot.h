/**
 * @file robot.h
 * @brief Robot behaviour controller.
 */


#ifndef ROBOT_H_
#define ROBOT_H_


#include <stdint.h>



/**
 * @brief Robot behaviour states.
 */

typedef enum
{

    ROBOT_IDLE = 0,

    ROBOT_FORWARD,

    ROBOT_AVOID_FRONT,

    ROBOT_AVOID_REAR,

    ROBOT_ESCAPE


} RobotState;



/**
 * @brief Initialize robot controller.
 */
void ROBOT_Init(void);



/**
 * @brief Scheduler update.
 *
 * Runs robot decision logic.
 */
void ROBOT_Update(void);



/**
 * @brief Get current robot state.
 */
RobotState ROBOT_GetState(void);



#endif /* ROBOT_H_ */
