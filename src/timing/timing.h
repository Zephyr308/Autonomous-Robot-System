/**
 * @file timing.h
 * @brief Cooperative scheduler and system timing interface.
 *
 * Provides:
 * - 10ms system tick
 * - Task registration
 * - Cooperative task execution
 */


#ifndef TIMING_H_
#define TIMING_H_

#include <stdint.h>


/*
 * Scheduler heartbeat.
 *
 * All task periods should be
 * multiples of this value.
 */

#define SYSTEM_TICK_MS      10U



/*
 * Maximum number of scheduled tasks.
 *
 * Increase if more modules are added.
 */

#define TIMING_MAX_TASKS    16U



/*
 * Task function pointer type.
 */

typedef void (*TaskFunction)(void);



/**
 * @brief Scheduler task structure.
 */

typedef struct
{

    /*
     * Function executed
     */

    TaskFunction function;


    /*
     * Execution period in ms
     */

    uint32_t period;


    /*
     * Last execution timestamp
     */

    uint32_t last_run;


    /*
     * Enable/disable task
     */

    uint8_t enabled;


} TimingTask;



/**
 * @brief Initialize SysTick timer.
 *
 * Configures a 10ms interrupt tick.
 */
void TIMING_Init(void);



/**
 * @brief Start system tick.
 *
 * Enables SysTick counter.
 */
void TIMING_Start(void);



/**
 * @brief Execute scheduler.
 *
 * Must be called continuously
 * from main while loop.
 */
void TIMING_Run(void);



/**
 * @brief Add task to scheduler.
 *
 * @param task      Function pointer
 * @param period    Execution period in ms
 *
 * @return
 * 1 = success
 * 0 = table full/error
 */
uint8_t TIMING_AddTask
(
    TaskFunction task,
    uint32_t period
);



/**
 * @brief Get system uptime.
 *
 * @return milliseconds since startup.
 */
uint32_t TIMING_GetMillis(void);



/**
 * @brief Enable task.
 */
void TIMING_EnableTask
(
    uint8_t id
);



/**
 * @brief Disable task.
 */
void TIMING_DisableTask
(
    uint8_t id
);



#endif /* TIMING_H_ */
