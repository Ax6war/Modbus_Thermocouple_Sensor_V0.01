#include "DeviationAlarm.h"

/*
  DeviationAlarm.cpp
  Purpose: Implements deviation alarm logic based on setpoints and modes.
*/

DeviationAlarm::DeviationAlarm(AckMode ack, float setpoint_High, float setpoint_Low, bool isAtSetpoint)
    : Alarm(ack), setpoint_High(setpoint_High), setpoint_Low(setpoint_Low), isAtSetpoint(isAtSetpoint) {
    // Initialize threshold based on whether the initial value is at setpoint     
}

void DeviationAlarm::evaluate_Alm(float value) {
    // Evaluate alarm state based on the acknowledgment mode, setpoints, and current value
if (ackmode == Auto) {
    if (isAtSetpoint) {   
        if (AtSetpoint) {
            if (value > setpoint_High || value < setpoint_Low) {
                state = Active;
                AtSetpoint = false;
            } else {
                state = Not_Active;
            }
        } else {
            if (value <= setpoint_High && value >= setpoint_Low) {
                state = Not_Active;
                AtSetpoint = true;
            } 
        }
    }else{
        if (value > setpoint_High || value < setpoint_Low) {
            state = Active;
        } else {
            state = Not_Active;
        }
    }
}

    if (ackmode == Manual) {
        if(isAtSetpoint){
        if (AtSetpoint) {
            if (value > setpoint_High || value < setpoint_Low) {
                state = Active;
                
            }
        } else {
            if (value <= setpoint_High && value >= setpoint_Low) {
                AtSetpoint = true;
            }
        }
    }else{
        if (value > setpoint_High || value < setpoint_Low) {
            state = Active;
        }
    }
    }
}

void DeviationAlarm::changeSetpoint(float newSetpoint_High, float newSetpoint_Low){
    setpoint_High = newSetpoint_High;
    setpoint_Low = newSetpoint_Low;
}

void DeviationAlarm::changeAckMode(AckMode newAckMode){
    ackmode = newAckMode;
}

void DeviationAlarm::changeIsAtSetpoint(bool newIsAtSetpoint){
    isAtSetpoint = newIsAtSetpoint;
    AtSetpoint = false;
}