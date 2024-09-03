#ifndef BT_INPUT_PIN_H
#define BT_INPUT_PIN_H

#include "input_template.h"
class C_BT_INPUT_PIN: public C_BUTTON_INPUT{
private:
    uint8_t u8Pin;
    bool boLastState;
    bool boSend;

public:
    C_BT_INPUT_PIN(uint8_t u8Pin): u8Pin(u8Pin){};
    ~C_BT_INPUT_PIN(){};
    void vInputInit();
    void vInputLoop();
    bool bGetButton(bool* pboSend);
};


#endif