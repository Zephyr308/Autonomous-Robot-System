/**
 * @file main.c
 * @brief Main firmware entry point.
 *
 * Cooperative scheduler based robot firmware.
 */


#include <stdint.h>


#include "timing.h"

#include "robot.h"

#include "limbs.h"

#include "head.h"

#include "tail.h"

#include "neck.h"

#include "lights.h"



/*
 *---------------------------------------------------------
 * Main application
 *---------------------------------------------------------
 */

int main(void)
{


    /*
     * ---------------------------
     * System timing
     * ---------------------------
     */

    TIMING_Init();



    /*
     * ---------------------------
     * Hardware drivers
     * ---------------------------
     */


    LIMBS_Init();


    HEAD_Init();


    TAIL_Init();


    NECK_Init();


    LIGHTS_Init();



    /*
     * ---------------------------
     * Control modules
     * ---------------------------
     */

    ROBOT_Init();



    /*
     * ---------------------------
     * Register scheduler tasks
     * ---------------------------
     */


    /*
     * Motor update
     *
     * Fast update:
     * 10ms
     */

    TIMING_AddTask
    (
        LIMBS_Update,
        10
    );



    /*
     * Ultrasonic processing
     *
     * 10ms scheduler,
     * internally samples at 50ms
     */

    TIMING_AddTask
    (
        HEAD_Update,
        10
    );



    /*
     * Robot decision making
     */

    TIMING_AddTask
    (
        ROBOT_Update,
        50
    );



    /*
     * Servo movement
     */

    TIMING_AddTask
    (
        NECK_Update,
        20
    );



    /*
     * LED effects
     */

    TIMING_AddTask
    (
        LIGHTS_Update,
        100
    );



    /*
     * Enable scheduler tick
     */

    TIMING_Start();



    /*
     * Main cooperative loop
     */

    while(1)
    {

        TIMING_Run();

    }


}
