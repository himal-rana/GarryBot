#ifndef FILTER_H
#define FILTER_H

class ComplementaryFilter
{
public:

    // Constructor
    ComplementaryFilter();

    // Reset filter angle
    void reset(float angle = 0.0f);

    // Update filter
    float update(float accelAngle,
                 float gyroRate,
                 float dt);

private:

    float angle;
};

#endif