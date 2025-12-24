
#include "AnalogAlarm.h"

AnalogAlarm::AnalogAlarm(AckMode ack, float threshold) : Alarm(ack), Alarm_threshold(threshold) {}


void AnalogAlarm::evaluate_Alm(float value)
{
    if (ackmode == Auto) {
        if (value >= Alarm_threshold) {
            state = Active;
        } else {
            state = Not_Active;
        }
    }

    if (ackmode == Manual) {
        if (value >= Alarm_threshold) {
            state = Active;
        }
    }
}