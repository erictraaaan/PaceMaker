#pragma once
#include "mbed.h"
#include "interface.h"
#include "hardware.h"
#include "chamberData.h"
#include "genData.h"
#include "pulse.h"
#include "voor.h"
#include "rtos.h"
#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>

//CONSTRUCTORS*****************************
interface::interface():rled(LED_BLUE){
    }

interface::~interface(){
        delete myDataStruct;
    }

interface::interface(Serial* inputPC):rled(LED_BLUE){
    pc = inputPC;
    }

interface::interface(Serial* inputPC , pulse* p ,genData* genData, chamberData* atrium , chamberData* ventricle, hardware* hardw):rled(LED_BLUE){
    rled = 1;
    isEgram = true;
    generalData = genData;
    pc = inputPC;
    interfacePulse = p;
    atrData = atrium;
    ventData = ventricle; 
    myHardware = hardw;
    myDataStruct = new dataStruct(myHardware);  
    }
//********************************************


//USER INTERFACE SCREENS**************************   

void interface:: readValues(){
    bool keepStreaming = true;
    while(keepStreaming){
            isEgram = true;
            if(pc->readable()){
                command = pc->getc();
                switch (command){
                    case 0x1:{
                        rled = !rled;
                        value = getInput();
                        generalData->chngAVdelayOffset(atof(value));
                        break;
                    }
                    case 0x2:{
                        value = getInput();
                        generalData->chngLRL(atof(value));
                        break;
                    }
                    case 0x3:{
                        value = getInput();
                        generalData->chngURL(atof(value));
                        break;
                    }
                    case 0x4:{
                        value = getInput();
                        generalData->chngAVdelay(atof(value));
                        break;
                    }
                    case 0x5:{
                        value = getInput();
                        generalData->chngAVdelayOffset(atof(value));
                        break;
                    }
                    case 0x6:{
                        value = getInput();
                        generalData->chngRSmooth(atof(value));
                        break;
                    }
                    case 0x7:{
                        value = getInput();
                        atrData->chngPaceAmp(atof(value)/10);
                        break;
                    }
                    case 0x8:{
                        value = getInput();
                        atrData->chngRP(atof(value));
                        break;
                    }
                    case 0x9:{
                        value = getInput();
                        atrData->chngPaceWidth(atof(value)/100);
                        break;
                    }
                    case 0xA:{
                        value = getInput();
                        atrData->chngSensitivity(atof(value)/100);
                        double pw = atrData->getSensitivity();
                        if(pw < 0.5){
                            rled = !rled;
                        }
                        break;
                    }
                    case 0xB:{
                        value = getInput();
                        atrData->chngPaceAmp(atof(value)/10);
                        break;
                    }
                    case 0xC:{
                        value = getInput();
                        ventData->chngPaceWidth(atof(value)/10);
                        break;
                    }
                    case 0xD:{
                        value = getInput();
                        ventData->chngRP(atof(value));
                        break;
                    }
                    case 0xE:{
                        value = getInput();
                        ventData->chngSensitivity(atof(value)/10);
                        break;                       
                    }
                    case 0xF:{
    /*                        value = getInput();
                        if(genData->getMode() == value){
                          break;
                      }
                        if(value == "VOOR"){
                            break;
                        }
                        else if(value == "VVI"){
                            break;
                        }*/                           
                    }
                    case 0x7a:{
                        while(isEgram){ 
                            if(pc->readable()){
                                char command = pc->getc();
                                if(command == 0x8a){
                                    isEgram = false;
                                }
                            }
                            double myInt = (myDataStruct->getData());
                            pc->printf("%f\n", myInt);
                            pc->printf("%c\n", atrData->getMarker());
                            wait_ms(4);
                        }
                        break;
                    }
                    case 0x1E:{
                        value = getInput();
                        if((*value) == '1'){
                            generalData->chngHyst(true);
                            break;
                        }
                        else if((*value)== '0'){
                            generalData->chngHyst(false);
                            break;
                        }
                    }
                }
            }
        }
}

char* interface::getInput(){
    char buffer[5];
    fgets (buffer,5,stdin);
    return buffer;
}

char interface::getChar(){
    while(true){
        if(pc->readable()){
            char command = pc->getc();
            return command;   
            }   
        }   
}                        




//void interface::startScreen(){
//    
//    pc->printf("\n ____   _    ____ _____ __  __    _    _  _______ ____  ");
//    pc->printf("\n|  _ \\ / \\  / ___| ____|  \\/  |  / \\  | |/ / ____|  _ \\");
//    pc->printf("\n| |_) / _ \\| |   |  _| | |\\/| | / _ \\ | ' /|  _| | |_) |");
//    pc->printf("\n|  __/ ___ \\ |___| |___| |  | |/ ___ \\| . \\| |___|  _ <");
//    pc->printf("\n|_| /_/   \\_\\____|_____|_|  |_/_/   \\_\\_|\\_\\_____|_| \\_\\");
//    
//    
//    pc->printf("\nWelcome to the PACEMAKER DCM.\n");
//    pc->printf("Options:\n");
//    pc->printf("1. Start VOOR Pulse\n"); // temporary test to get VOOR working
//    pc->printf("2. View/Change data\n");
//    pc->printf("Please enter a command:");
//    char command = getChar();
//    switch (command) {
//        case '1':{
//            
//            voor v(interfacePulse, ventData); //creates new instance of voor
//            v.startPace(); //starts pacing voor the same way as it used to pace in the user interface
//            //interfacePulse->startPulse(); //problems with this method: you create the pc output twice, once in UI and once in pulse.
//            startScreen();                             //realistically we'll never need to call the serial output in pulse, it should all be done in UI
//            break;
//            }
//        case '2':
//            interface::dataScreen();
//            break;
//        default:
//            pc->printf("\nThat is not an option.\n");
//            interface::startScreen();
//            break;
//    }   
//}


//****************************

//void interface::getAPulse(){ //TODO get this to work, the wait command has issues, see pulse.cpp . wait takes in seconds as argument
//    pulse myPulse(*atr);
//    myPulse.setWidth(1);
//    myPulse.startPulse();
//    }
    
//void interface::LEDon(AnalogOut* out){
//    (*out) = 0;
////    (*pc).printf(led);
//}
//    
//void interface::LEDoff(AnalogOut* out){
//    (*out) = 1;
//}