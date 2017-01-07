#pragma once
#include "mbed.h"
#include "sense.h"
#include "VVI.h"

sense::sense(genData* a): mySense(PTB2){
    myGenData = a; 
    isSensed = false; 
    }
    
sense::~sense(){};

bool sense::returnedSense(){
    timeout = false;
    isSensed = false;
    mbed::Timer t;
    t.start();
    while(!timeout){
        //Here we check if we should still be sensing or if we should give up
        if(myGenData->getHyst()){       //This is the case where hysteresis is enabled, we wait the lrl plus hysteresis
            if(t.read_ms() >= (myGenData->getLRL()+myGenData->getHystRL())){
                timeout = true; 
            }
        }
        else{   //Here hysteresis isn't enabled, so its just waiting the LRL. 
            if(t.read_ms() >= myGenData->getLRL()){
                timeout = true; 
            }
        }
        //Here we have to check the pin and see if it is above threshold. 
        if(mySense.read() > 0.995){
            isSensed = true;
            timeout = true;
        }
    }
    t.stop();
    return isSensed; 
}      
        
        