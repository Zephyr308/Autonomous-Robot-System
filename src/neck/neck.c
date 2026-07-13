/**
 * @file neck.c
 * @brief PWM servo (neck) control for TM4C123GH6PM
 */

#include "TM4C123GH6PM.h"
#include "delay.h"

/*----------------------------------------------------------
 * PWM Configuration
 *---------------------------------------------------------*/
#define PWM_CLOCK_FREQ      16000000U      /* 16 MHz */
#define SERVO_PWM_FREQ      50U            /* 50 Hz */

#define PWM_LOAD_VALUE      (PWM_CLOCK_FREQ / SERVO_PWM_FREQ)

/* Servo position limits */
#define SERVO_LEFT_LIMIT    319000U
#define SERVO_RIGHT_LIMIT   260000U

/* Sweep parameters */
#define SERVO_STEP          6400U
#define LEFT_DELAY_MS       1200U
#define RIGHT_DELAY_MS      1000U

/*----------------------------------------------------------
 * Internal Helper
 *---------------------------------------------------------*/
static void servo_set_position(uint32_t position)
{
    PWM1->_3_CMPA = position;
}

/*----------------------------------------------------------
 * Initialization
 *---------------------------------------------------------*/
void neck_init(void)
{
    SYSCTL->RCGCPWM  |= (1U << 1);      /* Enable PWM1 */
    SYSCTL->RCGCGPIO |= (1U << 5);      /* Enable Port F */

    SYSCTL->RCC &= ~(1U << 20);         /* PWM clock = System clock */

    volatile uint32_t delay = SYSCTL->RCGCGPIO;
    (void)delay;

    /* Configure PF3 as M1PWM7 */
    GPIOF->AFSEL |= (1U << 3);

    GPIOF->PCTL &= ~(0xFU << 12);
    GPIOF->PCTL |=  (0x5U << 12);

    GPIOF->DEN |= (1U << 3);

    /* Configure PWM Generator 3 */
    PWM1->_3_CTL = 0;

    /*
     * Set output HIGH on reload
     * Clear output when counter reaches CMPA
     */
    PWM1->_3_GENB = 0x8C;

    PWM1->_3_LOAD = PWM_LOAD_VALUE;
    PWM1->_3_CMPA = SERVO_LEFT_LIMIT;

    PWM1->_3_CTL = 1;

    PWM1->ENABLE |= (1U << 7);
}

/*----------------------------------------------------------
 * Set Servo Position
 *---------------------------------------------------------*/
void neck_turn(uint32_t position)
{
    servo_set_position(position);
}

/*----------------------------------------------------------
 * Generic Sweep Function
 *---------------------------------------------------------*/
static void servo_sweep(uint32_t start,
                        uint32_t end,
                        uint32_t step,
                        uint32_t delay_ms)
{
    PWM1->ENABLE |= (1U << 7);

    if (start > end)
    {
        for (uint32_t pos = start; pos >= end; pos -= step)
        {
            servo_set_position(pos);
            delayMs(delay_ms);

            if (pos - step < end)
                break;
        }
    }
    else
    {
        for (uint32_t pos = start; pos <= end; pos += step)
        {
            servo_set_position(pos);
            delayMs(delay_ms);

            if (pos + step > end)
                break;
        }
    }

    PWM1->ENABLE &= ~(1U << 7);
}

/*----------------------------------------------------------
 * Public Functions
 *---------------------------------------------------------*/
void check_left(void)
{
    servo_sweep(SERVO_LEFT_LIMIT,
                SERVO_RIGHT_LIMIT,
                SERVO_STEP,
                LEFT_DELAY_MS);
}

void check_right(void)
{
    servo_sweep(SERVO_RIGHT_LIMIT,
                SERVO_LEFT_LIMIT,
                SERVO_STEP,
                RIGHT_DELAY_MS);
}
