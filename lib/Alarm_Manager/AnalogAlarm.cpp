/*
  AnalogAlarm.cpp
  Purpose: Implements analog alarm logic (HI/LO thresholds, Auto/Manual ack modes).

*/

#include "AnalogAlarm.h"

AnalogAlarm::AnalogAlarm(AckMode ack, float threshold, Analog_Mode analogMode) : Alarm(ack), Alarm_threshold(threshold) {
    mode = analogMode;
}

// Evaluate the analog alarm using the current ack mode and configured HI/LO behavior.
// - Auto ack: sets Active or Not_Active based on comparison.
// - Manual ack: only sets Active; clearing is expected to be done externally.
void AnalogAlarm::evaluate_Alm(float value)
{
    if (ackmode == Auto) {

        switch (mode)
        {
        case HI:
            if (value >= Alarm_threshold) {
                state = Active;
            } else {
                state = Not_Active;
            }
            break;
        case LO:
            if (value <= Alarm_threshold) {
                state = Active;
            } else {
                state = Not_Active;
            }
            break;
        
        default:
            break;

    }
}

    if (ackmode == Manual) {

        switch (mode)
        {
        case HI:
            if (value >= Alarm_threshold) {
                state = Active;
            } 
            break;

        case LO:
            if (value <= Alarm_threshold) {
                state = Active;
            }
            break;
        
        default:
            break;
        }
      }
    }
