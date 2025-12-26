#ifndef ANALOG_ALARM_H
#define ANALOG_ALARM_H

#include "Alarm.h"

class AnalogAlarm : public Alarm
{
private:
    float Alarm_threshold; 

public:


    AnalogAlarm(AckMode ack, float threshold, Analog_Mode mode);

    void evaluate_Alm(float value);


};

#endif // ANALOG_ALARM_H