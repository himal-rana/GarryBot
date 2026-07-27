/**********************************************************************
 * imu.cpp
 *
 * MPU6050 Driver
 * Reads raw accelerometer and gyroscope data over I2C
 *********************************************************************/

#include <Arduino.h>
#include <Wire.h>

#include "config.h"
#include "imu.h"

// =====================================================
// Global Variables
// =====================================================

int16_t accelX_raw = 0;
int16_t accelY_raw = 0;
int16_t accelZ_raw = 0;

int16_t gyroX_raw = 0;
int16_t gyroY_raw = 0;
int16_t gyroZ_raw = 0;

float gyroX_bias = 0.0f;
float gyroY_bias = 0.0f;


// =====================================================
// Initialize MPU6050
// =====================================================

void initializeIMU()
{
    Wire.begin();

    // Wake up MPU6050
    Wire.beginTransmission(MPU6050_ADDRESS);
    Wire.write(0x6B);      // Power Management Register
    Wire.write(0x00);      // Wake up sensor
    Wire.endTransmission(true);

    Serial.println("MPU6050 Initialized");
}


// =====================================================
// Read Raw Sensor Data
// =====================================================

void readMPU6050()
{
    Wire.beginTransmission(MPU6050_ADDRESS);
    Wire.write(0x3B);              // ACCEL_XOUT_H
    Wire.endTransmission(false);

    Wire.requestFrom(MPU6050_ADDRESS, 14, true);

    accelX_raw = (Wire.read() << 8) | Wire.read();
    accelY_raw = (Wire.read() << 8) | Wire.read();
    accelZ_raw = (Wire.read() << 8) | Wire.read();

    Wire.read();   // Temperature High
    Wire.read();   // Temperature Low

    gyroX_raw = (Wire.read() << 8) | Wire.read();
    gyroY_raw = (Wire.read() << 8) | Wire.read();
    gyroZ_raw = (Wire.read() << 8) | Wire.read();
}


// =====================================================
// Gyroscope Calibration
// =====================================================

void calibrateGyroscope()
{
    Serial.println("Calibrating Gyroscope...");
    Serial.println("Keep robot still.");

    const int samples = 1000;

    int32_t gx_sum = 0;
    int32_t gy_sum = 0;

    for (int i = 0; i < samples; i++)
    {
        readMPU6050();

        gx_sum += gyroX_raw;
        gy_sum += gyroY_raw;

        delay(2);
    }

    gyroX_bias = gx_sum / (float)samples;
    gyroY_bias = gy_sum / (float)samples;

    Serial.println("Calibration Complete");

    Serial.print("Gyro X Bias: ");
    Serial.println(gyroX_bias);

    Serial.print("Gyro Y Bias: ");
    Serial.println(gyroY_bias);
}