#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include "game_template.h"

class C_SNAKE_GAME : public C_GAME
{
private:
struct C_POS{
    uint8_t u8PosX;
    uint8_t u8PosY;
};
C_POS* pcBuffer;
uint8_t u8HeadIdx;
uint8_t u8Length;
C_POS cApple;
E_DIRECTIONS eDir;
uint16_t u32LoopCounter;
uint16_t u16Offset;

void vMakeBuffer();
void vPlaceApple();
void vMove();
void vShow();
void vGameOver();

public:
    C_SNAKE_GAME();
    ~C_SNAKE_GAME();
    bool boInputHandler(E_DIRECTIONS eDir, bool boButton0, bool boButton1);
    void vGameInit();
    void vGameLoop();
};

#endif
