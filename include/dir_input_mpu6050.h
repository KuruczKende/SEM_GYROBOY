
#include "I2Cdev.h"
#include "MPU6050.h"

#include "Wire.h"

MPU6050 accelgyro;
//MPU6050 accelgyro(0x69); // <-- use for AD0 high

int16_t ax, ay, az;
int16_t gx, gy, gz;
void setup() {
    Wire.begin();
}

void loop() {
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
}
