#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

/**********************************************************************
 *                      GARRYBOT v1.0
 *                Hardware Configuration File
 *********************************************************************/

/******************** MPU6050 ************************/

constexpr uint8_t MPU6050_ADDRESS = 0x68;
//constexpr helps to define constants that can be used throughout the code without the risk of accidental modification. It also allows for better optimization by the compiler.

/******************** L298N Pins **********************/

// Left Motor
constexpr uint8_t LEFT_PWM = 5;
constexpr uint8_t LEFT_IN1 = 6;
constexpr uint8_t LEFT_IN2 = 9;

// Right Motor
constexpr uint8_t RIGHT_PWM = 3;
constexpr uint8_t RIGHT_IN1 = 10;
constexpr uint8_t RIGHT_IN2 = 11;


/******************** PID *****************************/

constexpr float PID_KP = 8.5f;
constexpr float PID_KI = 0.6f;
constexpr float PID_KD = 0.8f;


/******************** Robot ***************************/

constexpr float TARGET_ANGLE = 0.0f;
constexpr float MAX_TILT = 15.0f;

constexpr int MAX_PWM = 180;


/******************** Motor Calibration ***************/

constexpr int LEFT_OFFSET = 0;
constexpr int RIGHT_OFFSET = 20;


/******************** Kalman **************************/

constexpr float Q_ANGLE = 0.001f;
constexpr float Q_BIAS = 0.003f;
constexpr float R_MEASURE = 0.03f;


#endif