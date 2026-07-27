#include <Arduino.h>
#include "motor.h"

// Motor pins
const int ENA = 5;
const int IN1 = 6;
const int IN2 = 9;

const int IN3 = 10;
const int IN4 = 11;
const int ENB = 3;

// Motor calibration offsets
const float LEFT_GAIN  = 1.00;
const float RIGHT_GAIN = 0.82;   // adjust this

void Motor::begin()
{
    pinMode(ENA, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);

    pinMode(ENB, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    stop();
}

void Motor::drive(int speed)
{
    // Apply calibration offsets when removing the dead zone
    // if (speed > 0)
    //     speed += 30;
    // else if (speed < 0)
    //     speed -= 30;
    speed = constrain(speed, -255, 255);
    //PWM for left and right motors
    int ENA_PWM  = speed * LEFT_GAIN;
    int ENB_PWM = speed * RIGHT_GAIN;

    if (speed > 0)
    {
        // Forward
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);

        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);

        analogWrite(ENA, ENA_PWM);
        analogWrite(ENB, ENB_PWM
);
    }
    else if (speed < 0)
    {
        // Reverse
        speed = -speed;

        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);

        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);

        analogWrite(ENA, speed);
        analogWrite(ENB, speed);
    }
    else
    {
        stop();
    }
}

void Motor::stop()
{
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);

    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);

    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}