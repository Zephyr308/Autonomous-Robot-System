/**
 * @file    head.c
 * @brief   High-level ultrasonic sensor processing.
 */


#include <stdint.h>

#include "head.h"
#include "head_hw.h"



/*----------------------------------------------------------
 * Sensor configuration
 *---------------------------------------------------------*/


#define HEAD_UPDATE_PERIOD_MS     60U


#define FILTER_SIZE               5U


/*
 * Speed of sound conversion.
 *
 * Timer0 clock:
 *
 * 16MHz
 *
 * 1 tick = 62.5ns
 *
 */

#define SOUND_MULTIPLIER           5882U



/*----------------------------------------------------------
 * Internal variables
 *---------------------------------------------------------*/


static uint32_t distance_cm;


static uint32_t filter_buffer[FILTER_SIZE];


static uint8_t filter_index;


static uint8_t sensor_ready;



static uint32_t update_counter;



/*----------------------------------------------------------
 * Convert timer ticks to distance
 *---------------------------------------------------------*/


static uint32_t HEAD_ConvertDistance(uint32_t ticks)
{

    /*
     * Equivalent to:
     *
     * distance =
     * tick_time *
     * sound_conversion *
     * echo_ticks
     *
     */


    uint64_t value;


    value =
        ((uint64_t)ticks *
         SOUND_MULTIPLIER);


    value /= 1000000U;


    return (uint32_t)value;

}



/*----------------------------------------------------------
 * Simple moving average filter
 *---------------------------------------------------------*/


static uint32_t HEAD_Filter(uint32_t value)
{

    uint32_t sum = 0;


    uint8_t i;



    filter_buffer[filter_index] = value;


    filter_index++;


    if(filter_index >= FILTER_SIZE)
    {
        filter_index = 0;
    }



    for(i=0;i<FILTER_SIZE;i++)
    {
        sum += filter_buffer[i];
    }



    return sum / FILTER_SIZE;

}



/*----------------------------------------------------------
 * Initialization
 *---------------------------------------------------------*/


void HEAD_Init(void)
{

    uint8_t i;


    HEAD_HW_Init();



    distance_cm = 0;


    filter_index = 0;


    sensor_ready = 0;


    update_counter = 0;



    for(i=0;i<FILTER_SIZE;i++)
    {
        filter_buffer[i] = 0;
    }

}



/*----------------------------------------------------------
 * Non blocking update
 *
 * Called every 10ms
 *---------------------------------------------------------*/


void HEAD_Update(void)
{

    update_counter += 10;



    /*
     * Start new measurement
     */

    if(update_counter >= HEAD_UPDATE_PERIOD_MS)
    {

        update_counter = 0;


        HEAD_HW_Start();

    }



    /*
     * Check interrupt result
     */

    if(HEAD_HW_DataReady())
    {

        uint32_t ticks;


        ticks =
            HEAD_HW_GetEchoTime();



        distance_cm =
            HEAD_Filter(
                HEAD_ConvertDistance(ticks)
            );



        sensor_ready = 1;



        HEAD_HW_ClearData();

    }

}



/*----------------------------------------------------------
 * Get distance
 *---------------------------------------------------------*/


uint32_t HEAD_GetDistance(void)
{
    return distance_cm;
}



uint8_t HEAD_IsReady(void)
{
    return sensor_ready;
}
