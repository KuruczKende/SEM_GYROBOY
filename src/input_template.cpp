#include "input_template.h"
#include <Arduino.h>

void C_INPUT_MANAGER::vInputInit(){
    if(pcDirectionInput != NULL){
        pcDirectionInput->vInputInit();
    }
    if(pcButton0Input != NULL){
        pcButton0Input->vInputInit();
    }
    if(pcButton1Input != NULL){
        pcButton1Input->vInputInit();
    }
}

void C_INPUT_MANAGER::vInputLoop(){
    bool boSendInput = false;
    bool boSendTemp; 
    E_DIRECTIONS eDir = eDIRNone;
    bool boButton0 = false;
    bool boButton1 = false;
    if(pcDirectionInput != NULL){
        pcDirectionInput->vInputLoop();
    }
    if(pcButton0Input != NULL){
        pcButton0Input->vInputLoop();
    }
    if(pcButton1Input != NULL){
        pcButton1Input->vInputLoop();
    }

    if(pcDirectionInput != NULL){
        eDir = pcDirectionInput->eGetDirection(&boSendTemp);
        if(boSendTemp){
            boSendInput = true;
        }
    }
    if(pcButton0Input != NULL){
        boButton0 = pcButton0Input->bGetButton(&boSendTemp);
        if(boSendTemp){
            boSendInput = true;
        }
    }
    if(pcButton1Input != NULL){
        boButton1 = pcButton1Input->bGetButton(&boSendTemp);
        if(boSendTemp){
            boSendInput = true;
        }
    }

    if(boSendInput && fpboInputHandler != NULL){
        fpboInputHandler(eDir,boButton0,boButton1);
    }
}
