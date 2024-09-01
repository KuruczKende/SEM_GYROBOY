#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

#include "game_template.h"

class C_TETRIS_GAME : public C_GAME
{
private:
enum E_COLOR{
  eBlack = 0x000000,
  eRed = 0xFF0000,
  eGreen = 0x00FF00,
  eBlue = 0x0000FF,
  eOrange = 0xFF8800,
  eYellow = 0xFFFF00,
  ePurple = 0xFF00FF,
  eCyan = 0x00FFFF,
};

enum E_ACK{
  eNone = 0,
  eDown,
  eLeft,
  eRight,
  eRotateL,
  eRotateR,
};
#define eRotate eRotateR

struct C_SHAPE{
  E_COLOR eColor;
  uint8_t au8Look[2*4];
};

const C_SHAPE acShapes[7]={
  {.eColor=eRed,   .au8Look={0x02,0x64,0x0C,0x60,0x02,0x64,0x0C,0x60}}, // Z
  {.eColor=eGreen, .au8Look={0x04,0x62,0x06,0xC0,0x04,0x62,0x06,0xC0}}, // S
  {.eColor=eBlue,  .au8Look={0x0C,0x88,0x0E,0x20,0x02,0x26,0x00,0x8E}}, // J
  {.eColor=eOrange,.au8Look={0x08,0x8C,0x0E,0x80,0x06,0x22,0x00,0x2E}}, // L
  {.eColor=eYellow,.au8Look={0x06,0x60,0x06,0x60,0x06,0x60,0x06,0x60}}, // O
  {.eColor=ePurple,.au8Look={0x04,0x64,0x00,0xE4,0x04,0xC4,0x04,0xE0}}, // T
  {.eColor=eCyan,  .au8Look={0x44,0x44,0x00,0xF0,0x44,0x44,0x00,0xF0}}  // I
};

uint8_t u8FP_ShapeId;
uint8_t u8FP_Orientation;
uint8_t u8FP_PosX;
uint8_t u8FP_PosY;

uint16_t u16Score;
uint8_t u8Level;
uint8_t u8AllDeletedRows;
uint16_t u16LoopCounter;
bool boJustPlaced;

bool boTryMove (E_ACK eAction);
bool boFit(uint8_t u8PosX, uint8_t u8PosY, uint8_t u8LookU, uint8_t u8LookB);
void vPlace();
void vNewPiece();
void vShow();
void vGameOver();

public:
    C_TETRIS_GAME();
    ~C_TETRIS_GAME();
    bool boInputHandler(E_DIRECTIONS eDir, bool boButton0, bool boButton1);
    void vGameInit();
    void vGameLoop();
};

#endif