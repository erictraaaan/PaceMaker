#pragma once
#include "mbed.h"
#include "hardware.h"
#include "chamberData.h"

class pulse{
public:
    pulse();
    pulse(chamberData*, hardware*);
    ~pulse();
    void startPulse();
    void pace_charge_shutdown();
   // void pulsegenerator_initialize ();    
   // void setChamber(chamberData*); //used in VOOR (for now; might change) - eric
    
private:
    double myPaceWidth; //mSec; width of ventricular pace
    double myPaceAmp; //mV; amplitude of ventricular pace
    double myRP; //mSec; duration of refractory period
    float p_hysteresisInterval;
    float p_lowrateInterval;
    bool p_hysteresis;
    Serial* pc;
    PwmOut* aOut;
    chamberData* myChamber;
    hardware* myIOpins;    
    void vent_pace_prime ();
    void atr_pace_prime ();
    void pace_vent (double pulse_width_us);
    void pace_atr (double pulse_width_us);
    AnalogIn atrialIn;      // Pin A0
    AnalogIn ventricleIn;      // Pin A1
    AnalogIn leadImpedence;      // Pin A2
    AnalogIn atr_rect_signal;      // Pin A3
    AnalogIn vent_rect_signal;      // Pin A4
    
    /*=== Digital In ===*/
    DigitalIn atria_cmp_detect;   // Pin D0
    DigitalIn vent_cmp_detect;   // Pin D1
    
    /*=== PWM Out ===*/
    /* DigitalOut is used for the REF Signal
     * due to absence of PWM capabilities of Pins D2 and D4
     * on the FRDM-K64F Board
     */
    PwmOut pacing_ref_pwm;    // Pin D2 (PTB9)
    DigitalOut vent_ref_pwm;    // Pin D3
    DigitalOut atria_ref_pwm;   // Pin D4
    
    
    /*=== Digital Out ===*/
    DigitalOut pace_charge_ctrl;    // Pin D5
    DigitalOut z_atria_ctrl;    // Pin D6
    DigitalOut z_vent_ctrl;    // Pin D7
    
    DigitalOut atr_pace_ctrl;  // Pin D8
    DigitalOut vent_pace_ctrl;    // Pin D9
    DigitalOut pace_grnd_ctrl;    // Pin D10
    DigitalOut atr_grnd_ctrl;    // Pin D11
    DigitalOut vent_grnd_ctrl;    // Pin D12
    DigitalOut frontend_ctrl;
};