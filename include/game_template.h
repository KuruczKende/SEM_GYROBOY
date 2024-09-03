#ifndef GAME_TEMPLATE_H
#define GAME_TEMPLATE_H

#include <Arduino.h>
#include "input_template.h"

#define EXECUTION_FREQUENCY (10000)
#define EXECUTION_PERIOD_MS (1000 / EXECUTION_FREQUENCY)
#define EXECUTION_PERIOD_US (1000000 / EXECUTION_FREQUENCY)

class C_GAME{
protected:
    bool boSetLed(uint8_t u8PosX, uint8_t u8PosY, uint32_t u8Color);
    bool boSetLedRGB(uint8_t u8PosX, uint8_t u8PosY, uint8_t u8Red, uint8_t u8Green, uint8_t u8Blue);
    bool boSetLedHSV(uint8_t u8PosX, uint8_t u8PosY, uint8_t u8Hue, uint8_t u8Sat, uint8_t u8Val);
    bool boGetLed(uint8_t u8PosX, uint8_t u8PosY, uint32_t *pu32Color);
    bool boGetLedRGB(uint8_t u8PosX, uint8_t u8PosY, uint8_t *pu8Red, uint8_t *pu8Green, uint8_t *pu8Blue);
    bool boGetLedHSV(uint8_t u8PosX, uint8_t u8PosY, uint8_t *pu8Hue, uint8_t *pu8Sat, uint8_t *pu8Val);
    bool boIsClear(uint8_t u8PosX, uint8_t u8PosY);
    void vShowLed();
    void vClearLed();
public:
    C_GAME(){};
    ~C_GAME(){};
    virtual bool boInputHandler(E_DIRECTIONS eDir, bool boButton0, bool boButton1) = 0;
    virtual void vGameInit() = 0;
    virtual void vGameLoop() = 0;
};

bool boInitLeds();

#endif