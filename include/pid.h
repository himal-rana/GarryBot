#ifndef PID_H
#define PID_H

class PID
{
public:
    PID(float kp, float ki, float kd);

    int compute(float error, float dt);

    void reset();

private:
    float kp;
    float ki;
    float kd;

    float integral;
    float previousError;
};

#endif