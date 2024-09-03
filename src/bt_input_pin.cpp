#include "bt_input_pin.h"
#include <Arduino.h>

void C_BT_INPUT_PIN::vInputInit(){
    pinMode(u8Pin, INPUT_PULLUP);
    boSend = false;
    boLastState = digitalRead(u8Pin) == LOW;
}

void C_BT_INPUT_PIN::vInputLoop(){
    if(boLastState != (digitalRead(u8Pin) == LOW)){
        boLastState = !boLastState;
        boSend = boLastState;
    }
}

bool C_BT_INPUT_PIN::bGetButton(bool* pboSend){
    *pboSend = boSend;
    boSend = false;
    return boLastState && *pboSend;
}