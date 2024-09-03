#include "dir_input_mpu6050.h"
#include "Wire.h"
#include <Arduino.h>

void C_DIR_INPUT_MPU6050::vInputInit(){
    Wire.begin();
    Wire.beginTransmission(0x68);
    Wire.write(0x6B);  // Access the power management register
    Wire.write(0);     // Wake up the MPU-6050
    Wire.endTransmission(true);

    vReadMPU6050();
    unsigned long currentTime = micros();
    delayMicroseconds(1000);
    dt = (micros() - currentTime) / 1000000.0;
    // Calculate roll and pitch angles from accelerometer
    float accRoll = atan2(accY, accZ) * 180 / PI;
    float accPitch = (atan2(-accX, sqrt(accY * accY + accZ * accZ)) * 180 / PI);
    kalmanFilter(angleRoll, biasRoll, gyroX, accRoll);
    kalmanFilter(anglePitch, biasPitch, gyroY, accPitch);

    if (angleRoll > 150 || angleRoll < -150) {
        fAngleOffset = 5.0;
        boHorizontal = true;
        boVertical = false;
    }
    else if (angleRoll > 60 && angleRoll < 130) {
        fAngleOffset = 0.0;
        boVertical = true;
        boHorizontal = false;
    }
    else{
        boVertical = false;
        boHorizontal = false;
    }

    previousTime = micros();
    lasttimed = micros();
    lasttimes = micros();
}
void C_DIR_INPUT_MPU6050::vInputLoop(){
    uint32_t nowTime;
    vReadMPU6050();
    // Calculate elapsed time
    unsigned long currentTime = micros();
    dt = (currentTime - previousTime) / 1000000.0;
    previousTime = currentTime;
    // Calculate roll and pitch angles from accelerometer
    float accRoll = atan2(accY, accZ) * 180 / PI;
    float accPitch = (atan2(-accX, sqrt(accY * accY + accZ * accZ)) * 180 / PI);
    // Kalman filter for roll
    kalmanFilter(angleRoll, biasRoll, gyroX, accRoll);
    // Kalman filter for pitch
    kalmanFilter(anglePitch, biasPitch, gyroY, accPitch);

    nowTime = micros();
    anglePitch -= fAngleOffset;
    //Serial.println("Pitch: " + String(anglePitch) + " Roll: " + String(angleRoll));
    if (anglePitch < 75 && anglePitch >= 15) {
        if(nowTime - lasttimes > 1000000 / pow(2.0, anglePitch / 20.0)){
            Serial.println("Left");
            eLastDirection = eDIRLeft;
            lasttimes = nowTime;
            boSend = true;
        }
    }
    else if (anglePitch > -75.0 && anglePitch <= -15.0) {
        if(nowTime - lasttimes > 1000000 / pow(2.0, anglePitch / -20.0)){
            Serial.println("Right");
            eLastDirection = eDIRRight;
            lasttimes = nowTime;
            boSend = true;
        }
    }
    anglePitch += fAngleOffset;
    if (boHorizontal && angleRoll > 100.0 && angleRoll <= 160.0) {
        if (nowTime - lasttimed > 1000000 / pow(2.0, (angleRoll - 175.0) / -20.0)) {
            Serial.println("Down");
            eLastDirection = eDIRDown;
            lasttimed = nowTime;
            boSend = true;
        }
        else{
            eLastDirection = eDIRNone;
        }
    }
    else if (boVertical && angleRoll > 30.0 && angleRoll <= 90.0) {
        if (nowTime - lasttimed > 1000000 / pow(2.0, (angleRoll - 105.0) / -20.0)) {
            Serial.println("Down");
            eLastDirection = eDIRDown;
            lasttimed = nowTime;
            boSend = true;
        }
        else{
            eLastDirection = eDIRNone;
        }
    }
}
E_DIRECTIONS C_DIR_INPUT_MPU6050::eGetDirection(bool* pboSend){
    *pboSend = boSend;
    boSend = false;
    return eLastDirection;
}
void C_DIR_INPUT_MPU6050::vReadMPU6050() {
    // Read accelerometer and gyroscope data
    Wire.beginTransmission(0x68);
    Wire.write(0x3B);  // Starting register address for accelerometer data
    Wire.endTransmission(false);
    Wire.requestFrom(0x68, 14, true);  // Request 14 bytes of data

    // Read accelerometer data
    accX = (Wire.read() << 8 | Wire.read()) / 16384.0;  // Convert to g
    accY = (Wire.read() << 8 | Wire.read()) / 16384.0;
    accZ = (Wire.read() << 8 | Wire.read()) / 16384.0;

    // Read gyroscope data
    gyroX = (Wire.read() << 8 | Wire.read()) / 131.0;   // Convert to °/s
    gyroY = (Wire.read() << 8 | Wire.read()) / 131.0;
    gyroZ = (Wire.read() << 8 | Wire.read()) / 131.0;
}

void C_DIR_INPUT_MPU6050::kalmanFilter(float &angle, float &bias, float gyroRate, float measuredAngle) {
    // Prediction
    angle += (gyroRate - bias) * dt;

    // Update estimation error covariance matrix
    P[0][0] += dt * (dt * P[1][1] - P[0][1] - P[1][0] + Q_angle);
    P[0][1] -= dt * P[1][1];
    P[1][0] -= dt * P[1][1];
    P[1][1] += Q_bias * dt;

    // Kalman gain
    float S = P[0][0] + R_measure;
    float K[2];
    K[0] = P[0][0] / S;
    K[1] = P[1][0] / S;

    // Update estimate
    float y = measuredAngle - angle;
    angle += K[0] * y;
    bias += K[1] * y;

    // Update the error covariance matrix
    float P00_temp = P[0][0];
    float P01_temp = P[0][1];

    P[0][0] -= K[0] * P00_temp;
    P[0][1] -= K[0] * P01_temp;
    P[1][0] -= K[1] * P00_temp;
    P[1][1] -= K[1] * P01_temp;
}
