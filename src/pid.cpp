#include "pid.h"

PID::PID(float kp, float ki, float kd)
{
    this->kp = kp;
    this->ki = ki;
    this->kd = kd;

    integral = 0.0f;
    previousError = 0.0f;
}

int PID::compute(float error, float dt)
{
    // Integral term
    integral += error * dt;

    // Prevent integral windup
    if (integral > 100) integral = 100;
    if (integral < -100) integral = -100;

    // Derivative term
    float derivative = (error - previousError) / dt;
    previousError = error;

    // PID output
    float output =
        kp * error +
        ki * integral +
        kd * derivative;

    // Limit PWM
    if (output > 255) output = 255;
    if (output < -255) output = -255;

    return (int)output;
}

void PID::reset()
{
    integral = 0.0f;
    previousError = 0.0f;
}