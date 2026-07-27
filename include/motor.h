#ifndef MOTOR_H
#define MOTOR_H

class Motor
{
public:
    void begin();
    void drive(int speed);
    void stop();
};

#endif