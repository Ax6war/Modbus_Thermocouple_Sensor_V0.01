#include "DeviationAlarm.h"

/*
  DeviationAlarm.cpp
  Purpose: Implements deviation alarm logic based on setpoints and modes.
*/

DeviationAlarm::DeviationAlarm(AckMode ack, float setpoint_High, float setpoint_Low, bool isAtSetpoint)
    : Alarm(ack), setpoint_High(setpoint_High), setpoint_Low(setpoint_Low) {
    // Initialize threshold based on whether the initial value is at setpoint     
}

void DeviationAlarm::evaluate_Alm(float value) {
    // Evaluate alarm state based on the acknowledgment mode, setpoints, and current value
    if (ackmode == Auto) {
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
            } else {
                state = Active;
            }
        }
    }

    if (ackmode == Manual) {
        if (AtSetpoint) {
            if (value > setpoint_High || value < setpoint_Low) {
                state = Active;
                AtSetpoint = false;
            }
        } else {
            if (value <= setpoint_High && value >= setpoint_Low) {
                state = Not_Active;
                AtSetpoint = true;
            }
        }
    }
}