/**
 * @file head_hw.h
 * @brief Ultrasonic sensor hardware driver.
 */


#ifndef HEAD_HW_H_
#define HEAD_HW_H_


#include <stdint.h>



/*
 * Ultrasonic pins
 */

#define HEAD_TRIGGER_PIN     (1U << 4)   /* PA4 */

#define HEAD_ECHO_PIN        (1U << 6)   /* PB6 */



/**
 * @brief Initialize ultrasonic hardware.
 *
 * Configures:
 * PA4 trigger
 * PB6 Timer0A capture
 */
void HEAD_HW_Init(void);



/**
 * @brief Start ultrasonic measurement.
 *
 * Generates trigger pulse.
 */
void HEAD_HW_Start(void);



/**
 * @brief Check measurement status.
 *
 * @return
 * 1 = new measurement available
 */
uint8_t HEAD_HW_DataReady(void);



/**
 * @brief Get echo pulse width.
 *
 * @return Timer ticks
 */
uint32_t HEAD_HW_GetEchoTime(void);



/**
 * @brief Clear completed measurement flag.
 */
void HEAD_HW_ClearData(void);



#endif /* HEAD_HW_H_ */
