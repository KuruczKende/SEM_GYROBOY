
#include <MPU6050_my.h>
#include <Wire.h>

MPU6050 mpu6050(Wire);

long timer = 0;

float angleX,angleY;
bool angleYneg;

double mod(double a, int b) {
  a *= 1000;
  b *= 1000;
  return (double)((int) a % b) / 1000.0;
}
void calcanglexy() {
  angleX = mod(mpu6050.getAngleX() + 180.0, 360);
  angleY = mod(mpu6050.getAngleY(), 180);
  angleYneg = (angleY < 0);
  angleY = abs(angleY);
  if (angleY > 90.0)
    angleY = 180.0 - angleY;
  Serial.print(angleX);
  Serial.print(" ");
  Serial.println((angleYneg?-1.0:1.0)*angleY);
}

void setup() {
  Serial.begin(9600);
  delay(100);
  Wire.setClock(400000L);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
}

void loop() {
  mpu6050.update();

  if(millis() - timer > 1000){
    calcanglexy();
    timer = millis();
  }
}
