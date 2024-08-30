#include "snake_game.h"
#include <Arduino.h>

C_SNAKE_GAME::C_SNAKE_GAME(){}
C_SNAKE_GAME::~C_SNAKE_GAME(){}
bool C_SNAKE_GAME::boInputHandler(E_DIRECTIONS eDirection, bool boButton0, bool boButton1){
    switch (eDirection)
    {
    case eDIRLeft:
        break;
    case eDIRRight:
        break;
    case eDIRDown:
        break;
    default:
        break;
    }
    if(boButton0){
    }
    if(boButton1){
    }
    vShow();
    return false;
}
void C_SNAKE_GAME::vGameInit(){
    vClearLed();
    Serial.println("Game Init");
    randomSeed(analogRead(2));
    u16LoopCounter = EXECUTION_FREQUENCY * 48 / 60;
    u8HeadIdx = 2;
    u8Length = 3;
    pcBuffer = nullptr;
    vMakeBuffer();
    pcBuffer[2] = (C_POS){.u8PosX = 5, .u8PosY = 10};
    pcBuffer[1] = (C_POS){.u8PosX = 5, .u8PosY = 11};
    pcBuffer[0] = (C_POS){.u8PosX = 5, .u8PosY = 12};
    eDir = eDIRUp;
    vPlaceApple();
    vShow();
}
void C_SNAKE_GAME::vGameLoop(){
    if(u16LoopCounter  == 0){
        u16LoopCounter = EXECUTION_FREQUENCY * 48 / 60;
        vMove();
        vShow();
    }
    else{
        u16LoopCounter--;
    }
}
void C_SNAKE_GAME::vPlaceApple(){
  
}
void C_SNAKE_GAME::vMakeBuffer(){
    C_POS* pcTemp;
    pcTemp = new C_POS[(u8Length/40 + 1)*40];
    if(pcBuffer != nullptr){
        memcpy(pcTemp,pcBuffer,sizeof(pcBuffer));
        delete[] pcBuffer;
    }
    pcBuffer = pcTemp;
}
