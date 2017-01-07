#pragma once
#include "mbed.h"
#include "genData.h"

genData::genData(){
    p_hysteresis = false;
    p_hysteresisRateLimit = 0;
    p_lowerRateLimit = 0;
    p_upperRateLimit = 0;
    p_AVdelay = 0;
    p_AVdelayOffset = 0;
    p_rateSmoothing = 0;
    p_pacingMode = VVI;
    p_pacingState = PERMANENT;
}

void genData::chngHyst(bool chng){
    p_hysteresis = chng;   
}

bool genData::getHyst(){
    return p_hysteresis;   
}

int genData::chngHystRL(double val){
    if(val >= 30 && val <= 175){ 
        p_hysteresisRateLimit = val; 
        return 1; 
    }else{
        return 0;
    } 
}

double genData::getHystRL(){
    return p_hysteresisRateLimit;
}

int genData::chngLRL(double val){
    if(val >= 30 && val <= 175){
        p_lowerRateLimit = val;
        return 1;  
    }else{
        return 0;
    }    
}

double genData::getLRL(){
    return p_lowerRateLimit;
}

int genData::chngURL(double val){
    if(val >= 50 && val <= 175){
        p_upperRateLimit = val;
        return 1;
    }else{
        return 0;
    }
}

double genData::getURL(){
    return p_upperRateLimit;
}

int genData::chngAVdelay(double val){
    if(val >= 70 && val <= 300){
        p_AVdelay = val;
        return 1;
    }else{
        return 0;
    }
}

double genData::getAVdelay(){
    return p_AVdelay;   
}

int genData::chngAVdelayOffset(double val){
    if(val >= -10 && val <= -100){
        p_AVdelayOffset = val;
        return 1;
    }else{
        return 0;
    }
}

double genData::getAVdelayOffset(){
    return p_AVdelayOffset;
}

int genData::chngRSmooth(double val){
    
    if(val >= 3 && val <= 25){
        p_rateSmoothing = val; 
        return 1;
    }else{
        return 0;
    } 
}

double genData::getRSmooth(){
    return p_rateSmoothing;   
}

void genData::chngMode(Mode mode){
    p_pacingMode = mode;
}

genData::Mode genData::getMode(){
    return p_pacingMode;
}

void genData::chngState(State state){
    p_pacingState = state;
}

genData::State genData::getState(){
    return p_pacingState;
}



genData::~genData(){}