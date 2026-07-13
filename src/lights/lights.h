 /**
  * @file    lights.h
  * @brief   Interface for RGB LED control.
  *
  * This module controls the onboard RGB LEDs connected to:
  *
  * PF1 - Red LED
  * PF2 - Blue LED
  * PF3 - Green LED
  */

#ifndef LIGHTS_H_
#define LIGHTS_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


/*----------------------------------------------------------
 * LED Definitions
 *---------------------------------------------------------*/

/** Red LED connected to PF1 */
#define RED_LED     (1U << 1)

/** Blue LED connected to PF2 */
#define BLUE_LED    (1U << 2)

/** Green LED connected to PF3 */
#define GREEN_LED   (1U << 3)

/** Mask containing all RGB LED pins */
#define LED_ALL     (RED_LED | BLUE_LED | GREEN_LED)


/*----------------------------------------------------------
 * Public API
 *---------------------------------------------------------*/

/**
 * @brief Initialize RGB LEDs.
 *
 * Configures PF1, PF2, and PF3 as digital GPIO outputs.
 */
void LIGHTS_Init(void);


/**
 * @brief Turn on selected LEDs.
 *
 * @param led LED mask:
 *            RED_LED, BLUE_LED, GREEN_LED
 */
void LIGHTS_On(uint8_t led);


/**
 * @brief Turn off selected LEDs.
 *
 * @param led LED mask:
 *            RED_LED, BLUE_LED, GREEN_LED
 */
void LIGHTS_Off(uint8_t led);


/**
 * @brief Toggle selected LEDs.
 *
 * @param led LED mask:
 *            RED_LED, BLUE_LED, GREEN_LED
 */
void LIGHTS_Toggle(uint8_t led);


/**
 * @brief Set RGB LED output state.
 *
 * Replaces the current LED state with the supplied mask.
 *
 * @param color LED combination using RED_LED,
 *              BLUE_LED, and GREEN_LED.
 */
void LIGHTS_Set(uint8_t color);


#ifdef __cplusplus
}
#endif

#endif /* LIGHTS_H_ */
