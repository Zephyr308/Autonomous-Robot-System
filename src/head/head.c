/**
 * @file head.c
 * @brief Ultrasonic sensor processing.
 */


#include <stdint.h>

#include "head.h"
#include "head_hw.h"

#include "timing.h"



/*
 * Measurement interval.
 *
 * HC-SR04 typical:
 * 20-60ms
 */

#define HEAD_SAMPLE_PERIOD_MS     50U



/*
 * Sound conversion constants.
 *
 * Timer clock:
 *
 * 16MHz
 *
 * 1 tick = 62.5ns
 *
 */

#define SOUND_SPEED_CONSTANT      5882U



/*
 * Ignore impossible readings
 */

#define HEAD_MIN_DISTANCE_CM      2U

#define HEAD_MAX_DISTANCE_CM      400U



/*
 * Moving average filter size
 */

#define FILTER_SIZE              5U



/*
 *---------------------------------------------------------
 * Internal variables
 *---------------------------------------------------------
 */


static uint32_t distance_cm;


static uint32_t filter_buffer[FILTER_SIZE];


static uint8_t filter_index;


static uint8_t sensor_ready;


static uint32_t sample_timer;



/*
 *---------------------------------------------------------
 * Convert timer ticks to cm
 *
 * HC-SR04:
 *
 * distance =
 * echo_time * speed_of_sound / 2
 *
 *---------------------------------------------------------
 */

static uint32_t HEAD_ConvertTicks
(
    uint32_t ticks
)
{

    uint32_t distance;



    /*
     * Original project formula:
     *
     * tick_time * multiplier
     */

    distance =
        (ticks * SOUND_SPEED_CONSTANT)
        /
        1000000U;



    /*
     * Divide by 2 because
     * ultrasonic travels:
     *
     * sensor -> object -> sensor
     */

    distance /= 2U;



    return distance;

}



/*
 *---------------------------------------------------------
 * Moving average filter
 *---------------------------------------------------------
 */

static uint32_t HEAD_Filter
(
    uint32_t value
)
{

    uint32_t sum = 0;


    uint8_t i;



    filter_buffer[filter_index] =
        value;



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



/*
 *---------------------------------------------------------
 * Initialize
 *---------------------------------------------------------
 */

void HEAD_Init(void)
{

    uint8_t i;



    HEAD_HW_Init();



    distance_cm = 0;


    filter_index = 0;


    sensor_ready = 0;


    sample_timer = 0;



    for(i=0;i<FILTER_SIZE;i++)
    {
        filter_buffer[i] = 0;
    }

}



/*
 *---------------------------------------------------------
 * Scheduler update
 *
 * Run every 10ms
 *---------------------------------------------------------
 */

void HEAD_Update(void)
{

    uint32_t ticks;


    uint32_t distance;



    /*
     * Request new measurement
     */

    sample_timer += SYSTEM_TICK_MS;



    if(sample_timer >= HEAD_SAMPLE_PERIOD_MS)
    {

        sample_timer = 0;


        HEAD_HW_Start();

    }



    /*
     * Check interrupt result
     */

    if(HEAD_HW_DataReady())
    {

        ticks =
            HEAD_HW_GetEchoTime();



        distance =
            HEAD_ConvertTicks(ticks);



        /*
         * Validate reading
         */

        if(
            distance >= HEAD_MIN_DISTANCE_CM &&
            distance <= HEAD_MAX_DISTANCE_CM
          )
        {

            distance_cm =
                HEAD_Filter(distance);



            sensor_ready = 1;

        }



        HEAD_HW_ClearData();

    }

}



/*
 *---------------------------------------------------------
 * Return distance
 *---------------------------------------------------------
 */

uint32_t HEAD_GetDistance(void)
{

    return distance_cm;

}



/*
 *---------------------------------------------------------
 * Sensor status
 *---------------------------------------------------------
 */

uint8_t HEAD_IsReady(void)
{

    return sensor_ready;

}
