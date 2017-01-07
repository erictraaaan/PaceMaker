#pragma once
#include "hardware.h"
#include "mbed.h"

hardware::hardware(): atrium(PTC10),ventricle(PTC11),pc(USBTX,USBRX),sense(PTB2){
    pc.baud(9600);
  }
    
hardware::~hardware(){};
    
Serial* hardware::getSerial(){
    Serial* p = &pc;
    return p;
}

PwmOut* hardware::getChamber(char chamber){
    if(chamber == 'a'){
        PwmOut* a = &atrium;
        return a;
        }
    else {
        PwmOut* v = &ventricle;
        return v;
    }
}

double hardware::getSense(){
    return sense.read();
}
