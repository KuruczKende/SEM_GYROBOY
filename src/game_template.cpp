#include "game_template.h"

#include <FastLED.h>
#include <Arduino.h>

CRGBArray<200> leds;

bool C_GAME::boSetLed(uint8_t u8PosX, uint8_t u8PosY, uint32_t u32Color){
    bool boRet = true;
    if((u8PosX >= 10) || (u8PosY >= 20)){
        boRet = false;
    }
    else{
        if(u8PosY % 2 == 0){
            leds[u8PosY*10+u8PosX]=u32Color;
        }
        else{
            leds[u8PosY*10+9-u8PosX]=u32Color;
        }
    }
    return boRet;
}
bool C_GAME::boSetLedHSV(uint8_t u8PosX, uint8_t u8PosY, uint8_t u8Hue, uint8_t u8Sat, uint8_t u8Val){
    CHSV color = CHSV(u8Hue, u8Sat, u8Val);
    uint8_t* pu8Color = CRGB(color).raw;
    return boSetLed(u8PosX, u8PosY, pu8Color[0] << 16 | pu8Color[1] << 8 | pu8Color[2]);
}


bool C_GAME::boGetLed(uint8_t u8PosX, uint8_t u8PosY, uint32_t *pu32Color){
    bool boRet = true;
    if((u8PosX >= 10) || (u8PosY >= 20)){
        boRet = false;
    }
    else{
        if(u8PosY % 2 == 0){
            *pu32Color = (uint32_t)leds[u8PosY*10+u8PosX];
        }
        else{
            *pu32Color = (uint32_t)leds[u8PosY*10+9-u8PosX];
        }
    }
    return boRet;
}

bool C_GAME::boIsClear(uint8_t u8PosX, uint8_t u8PosY){
    bool boRet = true;
    if((u8PosX >= 10) || (u8PosY >= 20)){
        boRet = false;
    }
    else{
        if(u8PosY % 2 == 0){
            boRet = leds[u8PosY*10+u8PosX] == 0x00000000;
        }
        else{
            boRet = leds[u8PosY*10+9-u8PosX] == 0x00000000;
        }
    }
    return boRet;
}

void C_GAME::vShowLed(){
    FastLED.show();
}

void C_GAME::vClearLed(){
    FastLED.clear(true);
}

bool boInitLeds(){
    FastLED.addLeds<NEOPIXEL,6>(leds, 200);
}