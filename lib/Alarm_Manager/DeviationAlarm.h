#ifndef DEVIATION_ALARM_H
#define DEVIATION_ALARM_H

#include "Alarm.h"

class DeviationAlarm : public Alarm {
public:
    DeviationAlarm(AckMode ack, float setpoint_High, float setpoint_Low, bool isAtSetpoint);
    void evaluate_Alm(float value);

private:
    float setpoint_High;
    float setpoint_Low;
    float threshold;
    bool AtSetpoint;
    Analog_Mode mode;
};





























#endif