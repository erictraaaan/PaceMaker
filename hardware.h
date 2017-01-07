#pragma once
#include "mbed.h"

class hardware{
    public:
        hardware();
        ~hardware();
        Serial* getSerial();
        PwmOut* getChamber(char);
        double getSense();
    
    private:
        PwmOut atrium;
        PwmOut ventricle;
        Serial pc;
        AnalogIn sense;
};