#pragma once
#include "dataStruct.h"
#include "rtos.h"
#include "mbed.h"

dataStruct::dataStruct(hardware* hWare): myQueue(1,N){//,thread(&dataStruct::threadStarter){
    myHardware = hWare; 
//    thread.signal_set(START_THREAD);
    }
    
dataStruct::~dataStruct(){
    }

void dataStruct::threadStarter(void const *p){
    dataStruct *instance = (dataStruct*)p;
    instance->storeData();
    }

void dataStruct::storeData(){
//    thread.signal_wait(START_THREAD);
    while(true){
        //streamValue = myHardware->getSense();
        streamValue = 10;
        if(myQueue.GetNumberOfItems() <= N){
            myQueue.Put(&streamValue);
            }
        Thread::wait(4);
    }
}

double dataStruct::getData(){
//    queue temp = myQueue;
//    myQueue.Flush();
//    return temp;
    return myHardware->getSense();
}