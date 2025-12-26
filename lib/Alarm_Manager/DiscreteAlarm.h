#ifndef DISCRETEALARM_H
#define DISCRETEALARM_H

#include "Alarm.h"

class DiscreteAlarm : public Alarm
{
private:
    bool Alarm_value;

public:
    DiscreteAlarm(AckMode ack,bool AlarmOn);

    void evaluate_Alm(bool value);
    
};





#endif
