#include "filter.h"

ComplementaryFilter::ComplementaryFilter()
{
    angle = 0.0f;
}

void ComplementaryFilter::reset(float initialAngle)
{
    angle = initialAngle;
}

float ComplementaryFilter::update(float accelAngle,
                                  float gyroRate,
                                  float dt)
{
    const float alpha = 0.98f;

    angle =
        alpha * (angle + gyroRate * dt)
        +
        (1.0f - alpha) * accelAngle;

    return angle;
}