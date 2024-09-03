#include <Arduino.h>
#include "tetris_game.h"
#include "snake_game.h"
#include "dir_input_mpu6050.h"
#include "bt_input_pin.h"

C_TETRIS_GAME oGame;
C_DIR_INPUT_MPU6050 oDirInput;
C_BT_INPUT_PIN oBtInput0(7);
C_BT_INPUT_PIN oBtInput1(8);
bool boMainInputHandler(E_DIRECTIONS eDir, bool boButton0, bool boButton1){return oGame.boInputHandler(eDir, boButton0, boButton1);}
C_INPUT_MANAGER oInput(boMainInputHandler, &oDirInput, &oBtInput0, &oBtInput1);

uint32_t u32LastTime;

void setup() {
  Serial.begin(115200);
  boInitLeds();
  oInput.vInputInit();
  oGame.vGameInit();

  u32LastTime = micros();
}

void loop() {
  oInput.vInputLoop();
  oGame.vGameLoop();
  while (micros()-u32LastTime < EXECUTION_PERIOD_US) {
    delayMicroseconds(1);
  }
  u32LastTime = micros();
}