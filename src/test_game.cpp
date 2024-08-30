#include "test_game.h"
#include <Arduino.h>

void C_TEST_GAME::vGameInit(){
    u8PosX = 5;
    u8PosY = 10;
}
void C_TEST_GAME::vGameLoop(){
    vShowLed();
}
bool C_TEST_GAME::boInputHandler(E_DIRECTIONS eDir, bool boButton0, bool boButton1){
    bool boRet = false;
    switch (eDir)
    {
    case eDIRUp:
        boSetLed(u8PosX,u8PosY,0x00000000);
        u8PosY--;
        boRet = true;
        if(boSetLed(u8PosX,u8PosY,0x00FF0000) == false){
            u8PosY++;
            boSetLed(u8PosX,u8PosY,0x00FF0000);
            boRet = false;
        }
        break;
    
    case eDIRDown:
        boSetLed(u8PosX,u8PosY,0x00000000);
        u8PosY++;
        boRet = true;
        if(boSetLed(u8PosX,u8PosY,0x00FF0000) == false){
            u8PosY--;
            boSetLed(u8PosX,u8PosY,0x00FF0000);
            boRet = false;
        }
        break;
    
    case eDIRLeft:
        boSetLed(u8PosX,u8PosY,0x00000000);
        u8PosX--;
        boRet = true;
        if(boSetLed(u8PosX,u8PosY,0x00FF0000) == false){
            u8PosX++;
            boSetLed(u8PosX,u8PosY,0x00FF0000);
            boRet = false;
        }
        break;
    
    case eDIRRight:
        boSetLed(u8PosX,u8PosY,0x00000000);
        u8PosX++;
        boRet = true;
        if(boSetLed(u8PosX,u8PosY,0x00FF0000) == false){
            u8PosX--;
            boSetLed(u8PosX,u8PosY,0x00FF0000);
            boRet = false;
        }
        break;
    case eDIRNone:
    default:
        break;
    }
    return boRet;
}

C_TEST_GAME::C_TEST_GAME(){}
C_TEST_GAME::~C_TEST_GAME(){}