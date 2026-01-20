#include "tail.h"

extern uint32_t TAIL_Read(void);

bool TAIL_Detected(void)
{
    return (TAIL_Read() != 0);
}
