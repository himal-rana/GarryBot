#include <Arduino.h>

#include "config.h"
#include "imu.h"
#include "filter.h"
#include "motor.h"
#include "pid.h"

ComplementaryFilter pitchFilter;
Motor motor;

PID pid(
    14.0f,  // Kp
    0.0f,   // Ki  
    0.35f    // Kd
);

unsigned long lastTime = 0;

void setup()
{
    Serial.begin(115200);

    Serial.println();
    Serial.println("========== GarryBot ==========");

    initializeIMU();
    motor.begin();

    calibrateGyroscope();
    readMPU6050();

    float ax = accelX_raw / 16384.0f;
    float ay = accelY_raw / 16384.0f;
    float az = accelZ_raw / 16384.0f;

    float accelPitch =
        atan2(-ax, sqrt(ay * ay + az * az))
        * 180.0f / PI;

    pitchFilter.reset(accelPitch);

    lastTime = micros();
}

//actual loop is this one, but it is commented out for now. It will be used later when we implement the balancing logic.
void loop()
{
    readMPU6050();

    //--------------------------------------------------
    // Calculate dt
    //--------------------------------------------------

    unsigned long now = micros();

    float dt = (now - lastTime) / 1000000.0f;

    lastTime = now;

    //--------------------------------------------------
    // Convert raw accelerometer to g
    //--------------------------------------------------

    float ax = accelX_raw / 16384.0f;
    float ay = accelY_raw / 16384.0f;
    float az = accelZ_raw / 16384.0f;

    //--------------------------------------------------
    // Accelerometer Pitch
    //--------------------------------------------------

    float accelPitch =
        atan2(-ax, sqrt(ay * ay + az * az))
        * 180.0f / PI;

    //--------------------------------------------------
    // Gyroscope Rate (deg/sec)
    //--------------------------------------------------

    float gyroRate =
        (gyroY_raw - gyroY_bias) / 131.0f;

    //--------------------------------------------------
    // Complementary Filter
    //--------------------------------------------------

    float pitch =
        pitchFilter.update(
            accelPitch,
            gyroRate,
            dt
        );

    //--------------------------------------------------
    // Emergency Stop
    //--------------------------------------------------
    if (abs(pitch) > MAX_TILT)
    {
        motor.stop();
        pid.reset();
        Serial.println("Emergency Stop: Tilt angle exceeded limit!");
        return; // Exit the loop to prevent further processing
    }

    //--------------------------------------------------
    // Error
    //--------------------------------------------------

    float error = -pitch;

    int pwm = pid.compute(error, dt);

    motor.drive(pwm);

    //--------------------------------------------------
    // Print
    //--------------------------------------------------

    Serial.print("Pitch : ");

    Serial.println(pitch);
    
    Serial.print("PWM : ");
    Serial.println(pwm);

    delay(20);
}