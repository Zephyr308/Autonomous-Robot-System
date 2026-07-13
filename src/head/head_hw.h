/**
 * @file    head_hw.h
 * @brief   Low-level ultrasonic sensor hardware driver.
 *
 * Hardware:
 *
 * Trigger:
 *      PA4  (GPIO output)
 *
 * Echo:
 *      PB6  (Timer0A Capture Input)
 *
 */

#ifndef HEAD_HW_H_
#define HEAD_HW_H_

#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif


/*----------------------------------------------------------
 * Hardware pins
 *---------------------------------------------------------*/

#define HEAD_TRIGGER_PIN   (1U << 4)   /* PA4 */

#define HEAD_ECHO_PIN      (1U << 6)   /* PB6 */


/*----------------------------------------------------------
 * API
 *---------------------------------------------------------*/


/**
 * @brief Initialize ultrasonic hardware.
 *
 * Configures trigger GPIO and echo timer capture.
 */
void HEAD_HW_Init(void);



/**
 * @brief Send ultrasonic trigger pulse.
 *
 * Generates approximately 10us trigger pulse.
 */
void HEAD_HW_Trigger(void);



/**
 * @brief Check if echo capture occurred.
 *
 * @return
 * 1 if capture event available.
 * 0 otherwise.
 */
uint8_t HEAD_HW_EchoReady(void);



/**
 * @brief Read captured echo timer value.
 *
 * @return Timer capture timestamp.
 */
uint32_t HEAD_HW_ReadCapture(void);



/**
 * @brief Clear timer capture flag.
 */
void HEAD_HW_ClearCapture(void);



#ifdef __cplusplus
}
#endif


#endif /* HEAD_HW_H_ */
