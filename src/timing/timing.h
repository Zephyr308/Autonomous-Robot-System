/**
 * @file timing.h
 * @brief Cooperative firmware scheduler interface.
 */


#ifndef TIMING_H_
#define TIMING_H_

#include <stdint.h>



/*
 * System scheduler tick.
 *
 * All task timing is based on this.
 */

#define SYSTEM_TICK_MS     10U



typedef void (*TaskFunction)(void);



typedef struct
{

    /*
     * Function executed by task
     */

    TaskFunction function;



    /*
     * Execution period
     * milliseconds
     */

    uint32_t period_ms;



    /*
     * Last execution timestamp
     */

    uint32_t last_run;



    /*
     * Task enabled flag
     */

    uint8_t enabled;


} SchedulerTask;




/**
 * @brief Initialize system timing.
 */
void TIMING_Init(void);



/**
 * @brief Start scheduler timer.
 */
void TIMING_Start(void);



/**
 * @brief Execute all scheduled tasks.
 *
 * Called continuously from main loop.
 */
void TIMING_Run(void);



/**
 * @brief Get system uptime.
 */
uint32_t TIMING_GetMillis(void);



/**
 * @brief Add task to scheduler.
 *
 * @return 1 success, 0 failure.
 */
uint8_t TIMING_AddTask
(
    TaskFunction function,
    uint32_t period_ms
);



#endif
