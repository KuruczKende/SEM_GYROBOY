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
    randomSeed(analogRead(2));
    u32LoopCounter = (uint32_t)(EXECUTION_FREQUENCY * 4UL) / 5;
    u16Offset = 0;
    u8HeadIdx = 2;
    u8Length = 3;
    pcBuffer = nullptr;
    vMakeBuffer();
    Serial.println("Game Init");
    pcBuffer[0] = (C_POS){.u8PosX = 5, .u8PosY = 12};
    pcBuffer[1] = (C_POS){.u8PosX = 5, .u8PosY = 11};
    pcBuffer[2] = (C_POS){.u8PosX = 5, .u8PosY = 10};
    eDir = eDIRUp;
    vPlaceApple();
    vShow();
    Serial.println("Game Init");
}
void C_SNAKE_GAME::vGameLoop(){
    if(u32LoopCounter  == 0){
        u32LoopCounter = 1000000;
        vMove();
        vShow();
    }
    else{
        u32LoopCounter--;
    }
}
void C_SNAKE_GAME::vPlaceApple(){
    uint8_t u8Place = random(200-u8Length);
    for(uint8_t u8Y = 0; u8Y < 20; u8Y++){
        for(uint8_t u8X = 0; u8X < 10; u8X++){
            if(boIsClear(u8X,u8Y) == true){
                if(u8Place == 0){
                    cApple = (C_POS){.u8PosX = u8X, .u8PosY = u8Y};
                    boSetLed(u8X,u8Y,0x220000);
                }
                u8Place--;
            }
        }
    }
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
void C_SNAKE_GAME::vMove(){
    C_POS cNext;
    switch (eDir)
    {
    case eDIRUp:
        cNext = (C_POS){.u8PosX = pcBuffer[u8HeadIdx].u8PosX, .u8PosY = pcBuffer[u8HeadIdx].u8PosY-1};
        break;
    case eDIRDown:
        cNext = (C_POS){.u8PosX = pcBuffer[u8HeadIdx].u8PosX, .u8PosY = pcBuffer[u8HeadIdx].u8PosY+1};
        break;
    case eDIRLeft:
        cNext = (C_POS){.u8PosX = pcBuffer[u8HeadIdx].u8PosX-1, .u8PosY = pcBuffer[u8HeadIdx].u8PosY};
        break;
    case eDIRRight:
        cNext = (C_POS){.u8PosX = pcBuffer[u8HeadIdx].u8PosX+1, .u8PosY = pcBuffer[u8HeadIdx].u8PosY};
        break;    
    default:
        break;
    }
    if(boIsClear(cNext.u8PosX,cNext.u8PosY) == true){
        u8HeadIdx = (u8HeadIdx+1)%200;
        pcBuffer[u8HeadIdx].u8PosX = cNext.u8PosX;
        pcBuffer[u8HeadIdx].u8PosY = cNext.u8PosY;
        //boSetLed(pcBuffer[(u8HeadIdx+200-u8Length)%200].u8PosX,pcBuffer[(u8HeadIdx+200-u8Length)%200].u8PosY,0x000000);
    }
    else{

    }
}
void C_SNAKE_GAME::vShow(){
    if(u8HeadIdx < u8Length - 1){
        for(uint8_t u8Idx = u8HeadIdx; u8Idx != 0; u8Idx--){
            Serial.print('.');
            boSetLedHSV(pcBuffer[u8Idx].u8PosX,pcBuffer[u8Idx].u8PosY,((u8HeadIdx - u8Idx) + u16Offset)*360/u8Length,0x88,0x88);
        }
            Serial.print('.');
        boSetLedHSV(pcBuffer[0].u8PosX,pcBuffer[0].u8PosY,(u8HeadIdx + u16Offset)*360/u8Length,0x88,0x88);
        for(uint8_t u8Idx = 199; u8Idx > 200 - u8Length + u8HeadIdx; u8Idx--){
            Serial.print('.');
            boSetLedHSV(pcBuffer[u8Idx].u8PosX,pcBuffer[u8Idx].u8PosY,((200 - u8Idx) + u16Offset)*360/u8Length,0x88,0x88);
        }
    }
    else{
        for(uint8_t u8Idx = u8HeadIdx; u8Idx != u8HeadIdx - u8Length; u8Idx--){
            //boSetLedHSV(pcBuffer[u8Idx].u8PosX,pcBuffer[u8Idx].u8PosY,0x13/*((u8HeadIdx - u8Idx) + u16Offset)*360/u8Length*/,0x88,0x88);
            Serial.println("hIdx: "+String(u8Idx)+" len: "+String(u8Length)+" x: "+String(pcBuffer[u8Idx].u8PosX)+" y: "+String(pcBuffer[u8Idx].u8PosY));
            boSetLed(pcBuffer[u8Idx].u8PosX,pcBuffer[u8Idx].u8PosY,0xFF0000);
        }
    }
    u16Offset++;
    if(u16Offset == 360){
        u16Offset = 0;
    }
    vShowLed();
}
