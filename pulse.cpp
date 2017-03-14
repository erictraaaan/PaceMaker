#pragma once
#include "mbed.h"
#include "pulse.h"
#include "rtos.h"

pulse::pulse():
atrialIn(A0),      // Pin A0
 ventricleIn(A1),      // Pin A1
 leadImpedence(A2),      // Pin A2
 atr_rect_signal(A3),      // Pin A3
 vent_rect_signal(A4),      // Pin A4

/*=== Digital In ===*/
atria_cmp_detect(PTC16),   // Pin D0
vent_cmp_detect(PTC17),   // Pin D1

/*=== PWM Out ===*/
/*  is used for the REF Signal
 * due to absence of PWM capabilities of Pins D2 and D4
 * on the FRDM-K64F Board
 */
 pacing_ref_pwm(PTA1),    // Pin D2 (PTB9)
 vent_ref_pwm(PTB9),    // Pin D3
 atria_ref_pwm(PTB23),   // Pin D4


/*=== Digital Out ===*/
 pace_charge_ctrl(PTA2),    // Pin D5
 z_atria_ctrl(PTC2),    // Pin D6
 z_vent_ctrl(PTC3),    // Pin D7

 atr_pace_ctrl(PTC12),  // Pin D8
 vent_pace_ctrl(PTC4),    // Pin D9
 pace_grnd_ctrl(PTD0),    // Pin D10
 atr_grnd_ctrl(PTD2),    // Pin D11
 vent_grnd_ctrl(PTD3),    // Pin D12
 frontend_ctrl(PTD1)    // Pin D13
 {}
    
pulse::pulse(chamberData* chamber, hardware* IOpins):/*=== Analog In ===*/
 atrialIn(A0),      // Pin A0
 ventricleIn(A1),      // Pin A1
 leadImpedence(A2),      // Pin A2
 atr_rect_signal(A3),      // Pin A3
 vent_rect_signal(A4),      // Pin A4

/*=== Digital In ===*/
atria_cmp_detect(PTC16),   // Pin D0
vent_cmp_detect(PTC17),   // Pin D1

/*=== PWM Out ===*/
/*  is used for the REF Signal
 * due to absence of PWM capabilities of Pins D2 and D4
 * on the FRDM-K64F Board
 */
 pacing_ref_pwm(PTA1),    // Pin D2 (PTB9)
 vent_ref_pwm(PTB9),    // Pin D3
 atria_ref_pwm(PTB23),   // Pin D4


/*=== Digital Out ===*/
 pace_charge_ctrl(PTA2),    // Pin D5
 z_atria_ctrl(PTC2),    // Pin D6
 z_vent_ctrl(PTC3),    // Pin D7

 atr_pace_ctrl(PTC12),  // Pin D8
 vent_pace_ctrl(PTC4),    // Pin D9
 pace_grnd_ctrl(PTD0),    // Pin D10
 atr_grnd_ctrl(PTD2),    // Pin D11
 vent_grnd_ctrl(PTD3),    // Pin D12
 frontend_ctrl(PTD1)    // Pin D13
{
    myIOpins = IOpins;
    myChamber = chamber;
//    myPaceWidth = 0; //mSec, width of ventricular pace
//    myPaceAmp = 0; //mV, amplitude of ventricular pace
//    myRP = 0; //mSec, duration of refractory period
//    p_hysteresisInterval = 0;
//    p_lowrateInterval = 0;
//    p_hysteresis = false;
    
}

pulse::~pulse(){
    delete myChamber;
    delete myIOpins;
    delete pc;
    delete aOut;
}

//void pulse::setChamber(chamberData* c){
//    myChamber = c;
//    }
      
void pulse::pace_charge_shutdown() {
    /* Stage 1: Switch-OFF/Ground-ON */
    atr_pace_ctrl.write(0);
    vent_pace_ctrl.write(0);
    atr_grnd_ctrl .write(1);
    vent_grnd_ctrl.write(1);
    Thread::wait(50);
    

    /* Stage 2: Ref PWM LOW */
    pacing_ref_pwm.write(0);
    Thread::wait(100);

    /* Stage 3: Charge CTRL off */
    pace_charge_ctrl.write(0);
    Thread::wait(10);
    
    /* Stage 4: Ground OFF */
    atr_grnd_ctrl.write(0);
    vent_grnd_ctrl.write(0);
}

void pulse::vent_pace_prime() {
    /* Redundant code to close ground switches, 
     * prevents accidentally shorting the pacemaker
     */ 
    atr_grnd_ctrl .write(0);
    vent_grnd_ctrl.write(0);
    
    /* Stage 1: Ref PWM On */
    pacing_ref_pwm.write(myChamber->getPaceAmp());
    Thread::wait(10);

    /* Stage 2: Charge CTRL on */
    pace_charge_ctrl.write(1);
    Thread::wait(10);
}

void pulse::atr_pace_prime() {
    /* Redundant code to close ground switches, 
     * prevents accidentally shorting the pacemaker
     */ 
    atr_grnd_ctrl .write(0);
    vent_grnd_ctrl.write(0);
    
    /* Stage 4: Ref PWM On */
    pacing_ref_pwm.write(myChamber->getPaceAmp());
    Thread::wait(10);

    /* Stage 5: Charge CTRL on */
    pace_charge_ctrl.write(1);
    Thread::wait(10);
}

void pulse::pace_vent(double pulse_width_us) {
    vent_pace_prime();

    // Begin Pace Event Output
    vent_pace_ctrl.write(1);
    
    // Pace Duration
    wait(pulse_width_us);
    
    // Shut off Pace
    vent_pace_ctrl.write(0);
    
    pace_charge_shutdown (); 
}

void pulse::pace_atr(double pulse_width_us) {
    atr_pace_prime();

    // Begin Pace Event Output
    atr_pace_ctrl.write(1);
    
    // Pace Duration
    wait(pulse_width_us);
    
    // Shut off Pace
    atr_pace_ctrl.write(0);
        
    pace_charge_shutdown (); 
}


void pulse::startPulse(){
    pulse::pace_charge_shutdown();
    char a = myChamber->getChamberType();
    if(a == 'a'){
        pulse::pace_atr(myChamber->getPaceWidth());
    }
    else{
        pulse::pace_vent(myChamber->getPaceWidth());
    }
}
    
