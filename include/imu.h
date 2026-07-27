#ifndef IMU_H
#define IMU_H

#include <Arduino.h>

// Raw sensor data
extern int16_t accelX_raw;
extern int16_t accelY_raw;
extern int16_t accelZ_raw;

extern int16_t gyroX_raw;
extern int16_t gyroY_raw;
extern int16_t gyroZ_raw;

// Gyroscope bias
extern float gyroX_bias;
extern float gyroY_bias;

// Functions
void initializeIMU();
void readMPU6050();
void calibrateGyroscope();

#endif