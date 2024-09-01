#ifndef INPUT_TEMPLATE_H
#define INPUT_TEMPLATE_H

#include <Arduino.h>

enum E_DIRECTIONS{
    eDIRUp = 0,
    eDIRDown,
    eDIRLeft,
    eDIRRight,
    eDIRNone
};

typedef  void (*T_IHF)(E_DIRECTIONS eDir, bool boButton0, bool boButton1);

class C_DIRECTION_INPUT{
public:
    C_DIRECTION_INPUT();
    ~C_DIRECTION_INPUT();
    virtual void vInputInit() = 0;
    virtual void vInputLoop() = 0;
    virtual E_DIRECTIONS eGetDirection(bool* pboSend) = 0;
};
class C_BUTTON_INPUT{
public:
    C_BUTTON_INPUT();
    ~C_BUTTON_INPUT();
    virtual void vInputInit() = 0;
    virtual void vInputLoop() = 0;
    virtual bool bGetButton(bool* pboSend) = 0;
};
class C_INPUT{
protected:
    T_IHF fpvInputHandler;
public:
    C_INPUT(T_IHF fpvInputHandler):fpvInputHandler(fpvInputHandler){};
    ~C_INPUT(){};
    virtual void vInputInit() = 0;
    virtual void vInputLoop() = 0;
};
class C_INPUT_MANAGER : public C_INPUT{
protected:
    C_DIRECTION_INPUT* const pcDirectionInput;
    C_BUTTON_INPUT* const pcButton0Input;
    C_BUTTON_INPUT* const pcButton1Input;
public:
    C_INPUT_MANAGER(T_IHF fpvInputHandler, C_DIRECTION_INPUT* pcDI, C_BUTTON_INPUT* pcBI0, C_BUTTON_INPUT* pcBI1):C_INPUT(fpvInputHandler),pcDirectionInput(pcDI),pcButton0Input(pcBI0),pcButton1Input(pcBI1){};
    ~C_INPUT_MANAGER();
    virtual void vInputInit() = 0;
    virtual void vInputLoop() = 0;
};

#endif