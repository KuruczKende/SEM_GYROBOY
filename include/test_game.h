#ifndef TEST_GAME_H
#define TEST_GAME_H

#include "game_template.h"

class C_TEST_GAME : public C_GAME
{
private:
    uint8_t u8PosX;
    uint8_t u8PosY;
public:
    C_TEST_GAME();
    ~C_TEST_GAME();
    bool boInputHandler(E_DIRECTIONS eDir, bool boButton0, bool boButton1);
    void vGameInit();
    void vGameLoop();
};

#endif