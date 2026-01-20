typedef struct {
    float kp, ki, kd;
    float integral;
    float prev;
} pid_t;

float pid_update(pid_t *p, float ref, float meas);
