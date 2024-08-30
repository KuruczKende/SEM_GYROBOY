#include <Arduino.h>
#include "tetris_game.h"

C_TETRIS_GAME oGame;
E_DIRECTIONS eDir;

uint32_t u32LastTime;

void setup() {
  Serial.begin(115200);
  boInitLeds(5);
  oGame.vGameInit();

  u32LastTime = micros();
}

void loop() {
  uint16_t x = analogRead(0);
  uint16_t y = analogRead(1);
  //Serial.println("x: "+String(x)+" y: "+String(y));
  if(y>973 && eDir == eDIRNone){
    eDir = eDIRUp;
    oGame.boInputHandler(eDir, false, false);
  }
  else if(y<50 && eDir == eDIRNone){
    eDir = eDIRDown;
    oGame.boInputHandler(eDir, false, false);
  }
  else if(x>973 && eDir == eDIRNone){
    eDir = eDIRLeft;
    oGame.boInputHandler(eDir, false, false);
  }
  else if(x<50 && eDir == eDIRNone){
    eDir = eDIRRight;
    oGame.boInputHandler(eDir, false, false);
  }
  else if(x>311 && x<711 && y>311 && y<711){
    eDir = eDIRNone;
  }
  //oGame.boInputHandler(eDIRNone, true, false);
  oGame.vGameLoop();
  while (micros()-u32LastTime < EXECUTION_PERIOD_US) {
    delayMicroseconds(1);
  }
  u32LastTime = micros();
}