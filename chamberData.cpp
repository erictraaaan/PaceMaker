#pragma once
#include "mbed.h"
#include "chamberData.h"

chamberData::chamberData(){
}

chamberData::chamberData(char chamberType){
    mychamber = chamberType;
    if(mychamber == 'v'){
        p_PaceAmp = 3.75; //decimal value between 0 and 1 which is a factor applied to 3.3V output.  ie. 0.5 will give 0.5(3.3) V of output
        p_PaceWidth = 0.4;
        p_RP = 320;
        p_Sensitivity = 2.5;
    }
    else{
       p_PaceAmp = 0.5;
       p_PaceWidth = 0.05;
       p_RP = 250;
       p_Sensitivity = 0.75;
    }
}
char chamberData::getChamberType(){
    return mychamber;
}

int chamberData::chngPaceAmp(double amp){
    if(mychamber == 'a'){
        if(amp>3.2 || amp<0.5){
            return 0; 
        }else{
            p_PaceAmp = (amp-0)/(7-0);
            return 1;
        }
    }else{
        if(amp>7 || amp<3.5){
            return 0;
        }else{
            p_PaceAmp = (amp-0)/(7-0);
            return 1;
        }
    }
}

double chamberData::getPaceAmp(){
    return p_PaceAmp;
}

int chamberData::chngPaceWidth(double width){
    if(mychamber == 'a'){
        if(width!=0.05){
            return 0;
        }else{
            p_PaceWidth = width;
            return 1;
        }
    }else{
        if(width>1.9 || width< 0.1){
            return 0;
        }else{
            p_PaceWidth = width;
            return 1;
        }
    }
}

double chamberData::getPaceWidth(){
    return p_PaceWidth;
}

int chamberData::chngRP(double RP){
    if(mychamber == 'a'){
        if(RP>500 || RP<150){
            return 0;
        }else{
            p_RP = RP;
            return 1;
        }
    }else{
        if(RP>500 || RP< 150){
            return 0;
        }else{
            p_RP = RP;
            return 1;
        }
    }
}

double chamberData::getRP(){
    return p_RP;
}

int chamberData::chngSensitivity(double sensitivity){
   if(mychamber == 'a'){
        if(sensitivity <0.05 || sensitivity > 0.75){
            return 0;
        }else{
            p_Sensitivity = sensitivity;
            return 1;
        }
    }else{
        if(sensitivity>10 || sensitivity< 1){
            return 0;
        }else{
            p_Sensitivity = sensitivity;
            return 1;
        }
    }
}

double chamberData::getSensitivity(){
    return p_Sensitivity;
}

void chamberData::setMarker(char a){
    f_marker = a;
}

char chamberData::getMarker(){
    return f_marker;
}
chamberData::~chamberData(){}