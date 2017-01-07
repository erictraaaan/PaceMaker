#pragma once
#include "mbed.h"
#include "hardware.h"
#include "chamberData.h"
#include "genData.h"
#include "pulse.h"
#include "dataStruct.h"
#include "queue.h"
#include "rtos.h"

class interface{

public:
    interface();
    ~interface();
    interface(Serial*);
    interface(Serial* , pulse* , genData*, chamberData* , chamberData*, hardware*);
    void readValues();

//    void setAtrium(AnalogOut&);
//    void setVentricle(AnalogOut&);
//    void LEDon(AnalogOut*);
//    void LEDoff(AnalogOut*);

      
private:
    char* getInput();
    char buffer[128];
    char* value;
    char command;
    int* valInRange();
    char getChar();
    bool isEgram;
    double myValue;
    DigitalOut rled; 
    Serial* pc;
    pulse* interfacePulse;
    pulse* atrPulse;
    genData* generalData;
    chamberData* atrData;
    chamberData* ventData;
    dataStruct* myDataStruct;
    hardware* myHardware;
    unsigned char nTemp;
    static const int N = 13;
};