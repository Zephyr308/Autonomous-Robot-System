/**
 * @file lights.h
 * @brief RGB LED control interface.
 */


#ifndef LIGHTS_H_
#define LIGHTS_H_


#include <stdint.h>



/*
 * RGB LED pins
 *
 * TM4C123 LaunchPad
 */

#define LED_RED       (1U << 1)   /* PF1 */

#define LED_BLUE      (1U << 2)   /* PF2 */

#define LED_GREEN     (1U << 3)   /* PF3 */



#define LED_ALL       (LED_RED | LED_BLUE | LED_GREEN)



/**
 * @brief Initialize LEDs.
 */
void LIGHTS_Init(void);



/**
 * @brief Turn LEDs on/off directly.
 *
 * @param color LED mask
 */
void LIGHTS_On
(
    uint8_t color
);



/**
 * @brief Turn LEDs off.
 */
void LIGHTS_Off(void);



/**
 * @brief Toggle LEDs.
 */
void LIGHTS_Toggle
(
    uint8_t color
);



/**
 * @brief Set RGB value.
 *
 * @param red   0/1
 * @param green 0/1
 * @param blue  0/1
 */
void LIGHTS_RGB
(
    uint8_t red,
    uint8_t green,
    uint8_t blue
);



/**
 * @brief Scheduler update.
 *
 * Reserved for future animations.
 */
void LIGHTS_Update(void);



#endif /* LIGHTS_H_ */
