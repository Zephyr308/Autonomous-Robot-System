/**
 * @file timing.c
 * @brief Cooperative task scheduler.
 */


#include "TM4C123GH6PM.h"

#include "timing.h"



/*
 * Maximum firmware tasks.
 *
 * Increase if required.
 */

#define MAX_TASKS     12U



/*
 * Scheduler task list
 */

static SchedulerTask task_table[MAX_TASKS];



static uint8_t task_count;



/*
 * System time counter.
 *
 * Updated by SysTick interrupt.
 */

static volatile uint32_t system_time;



/*
 *---------------------------------------------------------
 * SysTick initialization
 *---------------------------------------------------------
 */

void TIMING_Init(void)
{

    system_time = 0;


    task_count = 0;



    /*
     * 16MHz clock
     *
     * 10ms tick:
     *
     * 16,000,000 * 0.01
     *
     * =160000 cycles
     */

    SysTick->LOAD =
        160000U - 1U;



    SysTick->VAL = 0;



    /*
     * Enable interrupt
     *
     * Use processor clock
     */

    SysTick->CTRL =
        (1U<<2) |
        (1U<<1);

}



/*
 *---------------------------------------------------------
 * Start scheduler clock
 *---------------------------------------------------------
 */

void TIMING_Start(void)
{

    SysTick->CTRL |= 1U;

}



/*
 *---------------------------------------------------------
 * SysTick interrupt
 *---------------------------------------------------------
 */

void SysTick_Handler(void)
{

    system_time += SYSTEM_TICK_MS;

}



/*
 *---------------------------------------------------------
 * Current system time
 *---------------------------------------------------------
 */

uint32_t TIMING_GetMillis(void)
{

    return system_time;

}



/*
 *---------------------------------------------------------
 * Add task
 *---------------------------------------------------------
 */

uint8_t TIMING_AddTask
(
    TaskFunction function,
    uint32_t period_ms
)
{

    if(task_count >= MAX_TASKS)
    {
        return 0;
    }



    if(function == 0)
    {
        return 0;
    }



    task_table[task_count].function =
        function;


    task_table[task_count].period_ms =
        period_ms;


    task_table[task_count].last_run =
        0;


    task_table[task_count].enabled =
        1;



    task_count++;


    return 1;

}



/*
 *---------------------------------------------------------
 * Run scheduler
 *---------------------------------------------------------
 */

void TIMING_Run(void)
{

    uint8_t i;


    uint32_t now;


    now = system_time;



    for(i=0;i<task_count;i++)
    {


        if(task_table[i].enabled == 0)
        {
            continue;
        }



        if((now - task_table[i].last_run)
            >= task_table[i].period_ms)
        {

            /*
             * Update timestamp before running.
             *
             * Prevents timing drift.
             */

            task_table[i].last_run = now;



            task_table[i].function();

        }

    }

}
