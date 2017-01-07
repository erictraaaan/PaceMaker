#pragma once
#include "mbed.h"
#include "hardware.h"
#include "rtos.h"
#include "queue.h"

#define START_THREAD 1

class dataStruct{
public:
    dataStruct(hardware*);
    ~dataStruct();
    double getData();

private:
    static const int N = 13;
    double k_streamPeriod;
    hardware* myHardware;
    double streamValue; 
    queue myQueue;
    static void threadStarter(void const *p);
    void storeData();
    Thread thread;
    
};