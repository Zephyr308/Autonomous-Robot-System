#ifndef HEAD_HW_H_
#define HEAD_HW_H_

#include <stdint.h>


#define HEAD_TRIGGER_PIN   (1U << 4)   /* PA4 */
#define HEAD_ECHO_PIN      (1U << 6)   /* PB6 */


/**
 * @brief Initialize ultrasonic hardware.
 */
void HEAD_HW_Init(void);


/**
 * @brief Start a new ultrasonic measurement.
 *
 * Generates trigger pulse.
 */
void HEAD_HW_Start(void);


/**
 * @brief Check if measurement is complete.
 *
 * @return 1 when echo capture finished.
 */
uint8_t HEAD_HW_DataReady(void);


/**
 * @brief Get captured echo time.
 *
 * @return Echo pulse width in timer ticks.
 */
uint32_t HEAD_HW_GetEchoTime(void);


/**
 * @brief Clear measurement flag.
 */
void HEAD_HW_ClearData(void);


#endif
