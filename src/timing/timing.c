/**
 * @file timing.c
 * @brief Cooperative firmware scheduler.
 */


#include "TM4C123GH6PM.h"
#include "timing.h"



/*
 * System time counter.
 *
 * Updated every 10ms by SysTick ISR.
 */

static volatile uint32_t system_time;



/*
 * Scheduler task table.
 */

static TimingTask task_table[TIMING_MAX_TASKS];



/*
 * Number of registered tasks.
 */

static uint8_t task_count;



/*
 *---------------------------------------------------------
 * Initialize timing system
 *---------------------------------------------------------
 */

void TIMING_Init(void)
{

    uint8_t i;



    system_time = 0;


    task_count = 0;



    /*
     * Clear task table.
     */

    for(i = 0; i < TIMING_MAX_TASKS; i++)
    {

        task_table[i].function = 0;

        task_table[i].period = 0;

        task_table[i].last_run = 0;

        task_table[i].enabled = 0;

    }



    /*
     * TM4C123 clock:
     *
     * 16MHz
     *
     * 10ms tick:
     *
     * 16,000,000 * 0.01
     *
     * =160000 cycles
     */


    SysTick->LOAD =
        (160000U - 1U);



    SysTick->VAL = 0;



    /*
     * Clock source:
     * processor clock
     *
     * Interrupt enabled
     *
     */

    SysTick->CTRL =
        (1U << 2) |
        (1U << 1);

}



/*
 *---------------------------------------------------------
 * Start scheduler timer
 *---------------------------------------------------------
 */

void TIMING_Start(void)
{

    SysTick->CTRL |= 1U;

}



/*
 *---------------------------------------------------------
 * SysTick Interrupt
 *
 * Runs every 10ms
 *---------------------------------------------------------
 */

void SysTick_Handler(void)
{

    system_time += SYSTEM_TICK_MS;

}



/*
 *---------------------------------------------------------
 * Register new task
 *---------------------------------------------------------
 */

uint8_t TIMING_AddTask
(
    TaskFunction task,
    uint32_t period
)
{

    if(task_count >= TIMING_MAX_TASKS)
    {
        return 0;
    }



    if(task == 0)
    {
        return 0;
    }



    task_table[task_count].function =
        task;


    task_table[task_count].period =
        period;


    task_table[task_count].last_run =
        system_time;


    task_table[task_count].enabled =
        1;



    task_count++;


    return 1;

}



/*
 *---------------------------------------------------------
 * Scheduler execution
 *
 * Called from main loop
 *---------------------------------------------------------
 */

void TIMING_Run(void)
{

    uint8_t i;


    uint32_t now;



    now = system_time;



    for(i = 0; i < task_count; i++)
    {

        if(task_table[i].enabled == 0)
        {
            continue;
        }



        if((now - task_table[i].last_run)
            >= task_table[i].period)
        {


            /*
             * Update before execution.
             *
             * Prevents drift if
             * task execution takes time.
             */

            task_table[i].last_run = now;



            task_table[i].function();

        }

    }

}



/*
 *---------------------------------------------------------
 * Get uptime
 *---------------------------------------------------------
 */

uint32_t TIMING_GetMillis(void)
{

    return system_time;

}



/*
 *---------------------------------------------------------
 * Enable task
 *---------------------------------------------------------
 */

void TIMING_EnableTask(uint8_t id)
{

    if(id < task_count)
    {
        task_table[id].enabled = 1;
    }

}



/*
 *---------------------------------------------------------
 * Disable task
 *---------------------------------------------------------
 */

void TIMING_DisableTask(uint8_t id)
{

    if(id < task_count)
    {
        task_table[id].enabled = 0;
    }

}
