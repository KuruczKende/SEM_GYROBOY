#include "dir_input_mpu6050"
#include "Wire.h"

void setup() {
    Wire.begin();
}

void loop() {
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
}

void C_DIR_INPUT_MPU6050::vInputInit(){
  
}
void C_DIR_INPUT_MPU6050::vInputLoop(){
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    gx -= ox;
    gy -= oy;
    gz -= oz;
}
E_DIRECTIONS C_DIR_INPUT_MPU6050::eGetDirection(bool* pboSend){
    *pboSend = false;
    if (micros()-u32LastTime > ){
        *pboSend = true;
    }
}
