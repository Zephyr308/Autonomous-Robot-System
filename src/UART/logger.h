#ifndef LOGGER_H
#define LOGGER_H

#include <stdint.h>

typedef enum {
    LOG_STATE,
    LOG_SENSOR,
    LOG_WATCHDOG
} log_event_t;

void LOG_Init(void);
void LOG_Event(log_event_t type, uint32_t a, uint32_t b);

#endif
