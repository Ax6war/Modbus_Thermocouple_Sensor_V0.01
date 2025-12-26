#ifndef ALARM_H
#define ALARM_H

#include "Alarm_Type.h"
#include <Arduino.h>



class Alarm
{
protected:
    AlarmState state;
    AckMode ackmode;
    unsigned long ackTime;
    unsigned long ackDuration = 2000;
public:
    Alarm(AckMode m);
    virtual ~Alarm() = default;

    virtual void evaluate_Alm(float value){};
    virtual void evaluate_Alm(bool value){};

    void acknowledge();

    AlarmState getState() const;



};


#endif