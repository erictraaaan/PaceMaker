#pragma once
#include "mbed.h"
#include "voor.h"
#include "pulse.h"

voor::voor(){}

voor::voor(pulse* p){
    voorPulse = p;
    }

voor::voor(pulse* p, chamberData* c){
    voorPulse = p;
    voorChamber = c;
    
    }
voor::~voor(){};

void voor::startPace(){
    while (true){
        voorPulse->startPulse();
        wait(voorChamber->getPaceWidth());
        }
    }
    