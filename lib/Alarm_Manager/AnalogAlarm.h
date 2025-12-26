#ifndef ANALOG_ALARM_H
#define ANALOG_ALARM_H

#include "Alarm.h"

class AnalogAlarm : public Alarm
{
private:
    float Alarm_threshold; 

public:


    AnalogAlarm(AckMode ack, float threshold);

    void evaluate_Alm(float value);


};

#endif // ANALOG_ALARM_H