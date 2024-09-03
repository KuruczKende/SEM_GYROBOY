#include "tetris_game.h"
#include <Arduino.h>

bool C_TETRIS_GAME::boInputHandler(E_DIRECTIONS eDir, bool boButton0, bool boButton1){
    switch (eDir)
    {
    case eDIRLeft:
        boTryMove(eLeft);
        break;
    case eDIRRight:
        boTryMove(eRight);
        break;
    case eDIRDown:
        if (boJustPlaced == false){
            boTryMove(eDown);
        }
        break;
    default:
        break;
    }
    if(boButton0){
        boTryMove(eRotateR);
    }
    else if(boButton1)
    {
        boTryMove(eRotateL);
    }
    vShow();
    
    return false;
}
void C_TETRIS_GAME::vGameInit(){
    vClearLed();
    Serial.println("Game Init");
    randomSeed(analogRead(2));
    u8AllDeletedRows = 0;
    u16Score = 0;
    u8Level = 0;
    u16LoopCounter = EXECUTION_FREQUENCY * 48 / 60;
    vNewPiece();
    vShow();
}
void C_TETRIS_GAME::vGameLoop(){
    if(u16LoopCounter  == 0){
        if(u8Level<9){
            u16LoopCounter = EXECUTION_FREQUENCY * (48-5*u8Level) / 60;
        }
        else{
            u16LoopCounter = EXECUTION_FREQUENCY / 10;
        }
        boJustPlaced = false;
        boTryMove(eDown);
        vShow();
    }
    else{
        u16LoopCounter--;
    }
}
bool C_TETRIS_GAME::boTryMove (E_ACK eAction){
  bool boRet = false;
  switch(eAction){
    case eDown:
      if(boFit(u8FP_PosX,u8FP_PosY+1,acShapes[u8FP_ShapeId].au8Look[u8FP_Orientation*2],acShapes[u8FP_ShapeId].au8Look[u8FP_Orientation*2+1])){
        u8FP_PosY++;
        boRet = true;
      }
      else{
        Serial.println("vPlace" + String(u8FP_PosX) + "," + String(u8FP_PosY));
        vPlace();
      }
      break;
    case eLeft:
      if(boFit(u8FP_PosX-1,u8FP_PosY,acShapes[u8FP_ShapeId].au8Look[u8FP_Orientation*2],acShapes[u8FP_ShapeId].au8Look[u8FP_Orientation*2+1])){
        u8FP_PosX--;
        boRet = true;
      }
      break;
    case eRight:
      if(boFit(u8FP_PosX+1,u8FP_PosY,acShapes[u8FP_ShapeId].au8Look[u8FP_Orientation*2],acShapes[u8FP_ShapeId].au8Look[u8FP_Orientation*2+1])){
        u8FP_PosX++;
        boRet = true;
      }
      break;
    case eRotateL:
      if(boFit(u8FP_PosX,u8FP_PosY,acShapes[u8FP_ShapeId].au8Look[(u8FP_Orientation*2+6)%8],acShapes[u8FP_ShapeId].au8Look[(u8FP_Orientation*2+7)%8])){
        u8FP_Orientation=(u8FP_Orientation+3)%4;
        boRet = true;
      }
      else if (boPenetrateSide(u8FP_PosX,u8FP_PosY,acShapes[u8FP_ShapeId].au8Look[(u8FP_Orientation*2+6)%8],acShapes[u8FP_ShapeId].au8Look[(u8FP_Orientation*2+7)%8])){
        Serial.println("side " + String(u8FP_PosX));
        if((u8FP_PosX == 0) && (boFit(u8FP_PosX + 1,u8FP_PosY,acShapes[u8FP_ShapeId].au8Look[(u8FP_Orientation*2+6)%8],acShapes[u8FP_ShapeId].au8Look[(u8FP_Orientation*2+7)%8]))){
            u8FP_PosX++;
            u8FP_Orientation=(u8FP_Orientation+3)%4;
            boRet = true;
        }
        else if((u8FP_PosX >= 8) && (boFit(u8FP_PosX - 1,u8FP_PosY,acShapes[u8FP_ShapeId].au8Look[(u8FP_Orientation*2+6)%8],acShapes[u8FP_ShapeId].au8Look[(u8FP_Orientation*2+7)%8]))){
            u8FP_PosX--;
            u8FP_Orientation=(u8FP_Orientation+3)%4;
            boRet = true;
        }
        else if((u8FP_PosX == 9) && (boFit(u8FP_PosX - 2,u8FP_PosY,acShapes[u8FP_ShapeId].au8Look[(u8FP_Orientation*2+6)%8],acShapes[u8FP_ShapeId].au8Look[(u8FP_Orientation*2+7)%8]))){
            u8FP_PosX-=2;
            u8FP_Orientation=(u8FP_Orientation+3)%4;
            boRet = true;
        }
      }
      break;
    case eRotateR:
      if(boFit(u8FP_PosX,u8FP_PosY,acShapes[u8FP_ShapeId].au8Look[(u8FP_Orientation*2+2)%8],acShapes[u8FP_ShapeId].au8Look[(u8FP_Orientation*2+3)%8])){
        u8FP_Orientation=(u8FP_Orientation+1)%4;
        boRet = true;
      }
      else if (boPenetrateSide(u8FP_PosX,u8FP_PosY,acShapes[u8FP_ShapeId].au8Look[(u8FP_Orientation*2+2)%8],acShapes[u8FP_ShapeId].au8Look[(u8FP_Orientation*2+3)%8])){
        Serial.println("side " + String(u8FP_PosX));
        if((u8FP_PosX == 0) && (boFit(u8FP_PosX + 1,u8FP_PosY,acShapes[u8FP_ShapeId].au8Look[(u8FP_Orientation*2+2)%8],acShapes[u8FP_ShapeId].au8Look[(u8FP_Orientation*2+3)%8]))){
            u8FP_PosX++;
            u8FP_Orientation=(u8FP_Orientation+1)%4;
            boRet = true;
        }
        else if((u8FP_PosX >= 8) && (boFit(u8FP_PosX - 1,u8FP_PosY,acShapes[u8FP_ShapeId].au8Look[(u8FP_Orientation*2+2)%8],acShapes[u8FP_ShapeId].au8Look[(u8FP_Orientation*2+3)%8]))){
            u8FP_PosX--;
            u8FP_Orientation=(u8FP_Orientation+1)%4;
            boRet = true;
        }
        else if((u8FP_PosX == 9) && (boFit(u8FP_PosX - 2,u8FP_PosY,acShapes[u8FP_ShapeId].au8Look[(u8FP_Orientation*2+2)%8],acShapes[u8FP_ShapeId].au8Look[(u8FP_Orientation*2+3)%8]))){
            u8FP_PosX-=2;
            u8FP_Orientation=(u8FP_Orientation+1)%4;
            boRet = true;
        }
      }
      break;
    case eNone:
      if(boFit(u8FP_PosX,u8FP_PosY,acShapes[u8FP_ShapeId].au8Look[u8FP_Orientation*2],acShapes[u8FP_ShapeId].au8Look[u8FP_Orientation*2+1])){
        boRet = true;
      }
      break;
    default:
      break;
  }
  return boRet;
}
bool C_TETRIS_GAME::boPenetrateSide(uint8_t u8PosX, uint8_t u8PosY, uint8_t u8LookU, uint8_t u8LookB){
  bool boRet = false;
  if((u8PosX == 0) && (((u8LookU & 0x88) | (u8LookB & 0x88)) != 0)){
    // the form protrudes to the left
    boRet = true;
  }
  if(((u8PosX == 9) && (((u8LookU & 0x33) | (u8LookB & 0x33)) != 0)) ||
     ((u8PosX == 8) && (((u8LookU & 0x11) | (u8LookB & 0x11)) != 0))){
    // the form protrudes to the right
    boRet = true;
  }
  return boRet;
}
bool C_TETRIS_GAME::boFit(uint8_t u8PosX, uint8_t u8PosY, uint8_t u8LookU, uint8_t u8LookB){
  bool boRet = true;
  if(((uint8_t)(u8PosX + 1) == 0) || u8PosX == 10){
    // not valid X position
    boRet = false;
  }
  if(boPenetrateSide(u8PosX,u8PosY,u8LookU,u8LookB) == true){
    boRet = false;
  }
  if((u8PosY == 20) || ((u8PosY == 19) && ((u8LookB & 0x0F) != 0))){
    // the form protrudes to the bottom
    boRet = false;
  }
  if(boRet == true)  {
    for(uint8_t i=0;i<4;i++){
      if(((boIsClear(u8PosX-1+i,u8PosY-2) == false) && ((u8LookU & (0x80 >> i)) != 0) && (u8PosY >= 2)) ||
         ((boIsClear(u8PosX-1+i,u8PosY-1) == false) && ((u8LookU & (0x08 >> i)) != 0) && (u8PosY >= 1)) ||
         ((boIsClear(u8PosX-1+i,u8PosY+0) == false) && ((u8LookB & (0x80 >> i)) != 0)) ||
         ((boIsClear(u8PosX-1+i,u8PosY+1) == false) && ((u8LookB & (0x08 >> i)) != 0))){
        boRet = false;
      }
    }
  }
  return boRet;
}
void C_TETRIS_GAME::vPlace(){
  bool boFullRow;
  uint32_t u32Color;
  uint8_t u8DeletedRows = 0;
  for(uint8_t i=0;i<4;i++){    
    if((acShapes[u8FP_ShapeId].au8Look[u8FP_Orientation*2  ] & (0x80 >> i)) != 0){
      if(boSetLed(u8FP_PosX+i-1,u8FP_PosY-2,(uint32_t)acShapes[u8FP_ShapeId].eColor) == false){
          vGameOver();
          return;
      }
    }
    if((acShapes[u8FP_ShapeId].au8Look[u8FP_Orientation*2  ] & (0x08 >> i)) != 0){
      if(boSetLed(u8FP_PosX+i-1,u8FP_PosY-1,(uint32_t)acShapes[u8FP_ShapeId].eColor) == false){
          vGameOver();
          return;
      }
    }
    if((acShapes[u8FP_ShapeId].au8Look[u8FP_Orientation*2+1] & (0x80 >> i)) != 0){
      boSetLed(u8FP_PosX+i-1,u8FP_PosY+0,(uint32_t)acShapes[u8FP_ShapeId].eColor);
    }
    if((acShapes[u8FP_ShapeId].au8Look[u8FP_Orientation*2+1] & (0x08 >> i)) != 0){
      boSetLed(u8FP_PosX+i-1,u8FP_PosY+1,(uint32_t)acShapes[u8FP_ShapeId].eColor);
    }
  }
  //sorellenörzések
  for(uint8_t i=0;i<20;i++){
    boFullRow = true;
    for(uint8_t j=0;j<10;j++){
        if(boIsClear(j,i)){
          boFullRow = false;
        }
    }
    if(boFullRow){
        u8DeletedRows++;
        for(uint8_t j=i;j>0;j--){
            for(uint8_t k=0;k<10;k++){
                boGetLed(k,j-1,&u32Color);
                boSetLed(k,j,u32Color);
            }
        }
        for(uint8_t k=0;k<10;k++){
            boSetLed(k,0,0x00000000);
        }
    }
  }
  if(u8DeletedRows > 0){
    switch (u8DeletedRows)
    {
    case 1: u16Score +=   40*(u8Level+1);
    case 2: u16Score +=  100*(u8Level+1);
    case 3: u16Score +=  300*(u8Level+1);
    case 4: u16Score += 1200*(u8Level+1);
    default: break;
    }
  }
  u8AllDeletedRows += u8DeletedRows;
  u8Level = u8AllDeletedRows / 10;
  vNewPiece();
  boJustPlaced = true;
  u16LoopCounter = EXECUTION_FREQUENCY * (48-5*u8Level) / 60;
}
void C_TETRIS_GAME::vNewPiece(){
    u8FP_ShapeId = random(7);
    u8FP_Orientation = random(4);
    Serial.println("id: "+String(u8FP_ShapeId)+" dir: "+String(u8FP_Orientation));
    u8FP_PosX = 4;
    u8FP_PosY = 0;
}
void C_TETRIS_GAME::vShow(){
  if(boTryMove(eNone)){
    for(uint8_t i=0;i<4;i++){
      if((acShapes[u8FP_ShapeId].au8Look[u8FP_Orientation*2  ] & (0x80 >> i)) != 0){
        boSetLed(u8FP_PosX+i-1,u8FP_PosY-2,(uint32_t)acShapes[u8FP_ShapeId].eColor);
      }
      if((acShapes[u8FP_ShapeId].au8Look[u8FP_Orientation*2  ] & (0x08 >> i)) != 0){
        boSetLed(u8FP_PosX+i-1,u8FP_PosY-1,(uint32_t)acShapes[u8FP_ShapeId].eColor);
      }
      if((acShapes[u8FP_ShapeId].au8Look[u8FP_Orientation*2+1] & (0x80 >> i)) != 0){
        boSetLed(u8FP_PosX+i-1,u8FP_PosY+0,(uint32_t)acShapes[u8FP_ShapeId].eColor);
      }
      if((acShapes[u8FP_ShapeId].au8Look[u8FP_Orientation*2+1] & (0x08 >> i)) != 0){
        boSetLed(u8FP_PosX+i-1,u8FP_PosY+1,(uint32_t)acShapes[u8FP_ShapeId].eColor);
      }
    }
    vShowLed();
    for(uint8_t i=0;i<4;i++){
      if((acShapes[u8FP_ShapeId].au8Look[u8FP_Orientation*2  ] & (0x80 >> i)) != 0){
        boSetLed(u8FP_PosX+i-1,u8FP_PosY-2,0x00000000);
      }
      if((acShapes[u8FP_ShapeId].au8Look[u8FP_Orientation*2  ] & (0x08 >> i)) != 0){
        boSetLed(u8FP_PosX+i-1,u8FP_PosY-1,0x00000000);
      }
      if((acShapes[u8FP_ShapeId].au8Look[u8FP_Orientation*2+1] & (0x80 >> i)) != 0){
        boSetLed(u8FP_PosX+i-1,u8FP_PosY+0,0x00000000);
      }
      if((acShapes[u8FP_ShapeId].au8Look[u8FP_Orientation*2+1] & (0x08 >> i)) != 0){
        boSetLed(u8FP_PosX+i-1,u8FP_PosY+1,0x00000000);
      }
    }
  }
  else{
    vShowLed();
  }
}
void C_TETRIS_GAME::vGameOver(){
    vGameInit();
}
