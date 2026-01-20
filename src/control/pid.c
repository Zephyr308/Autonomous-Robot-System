#include "pid.h"

float pid_update(pid_t *p, float ref, float meas)
{
    float err = ref - meas;
    p->integral += err;
    float deriv = err - p->prev;
    p->prev = err;
    return p->kp*err + p->ki*p->integral + p->kd*deriv;
}
