/*
  Alarm.h
  Purpose: Base Alarm class declaration.
*/

#ifndef ALARM_H
#define ALARM_H

#include "Alarm_Type.h"
#include <Arduino.h>



class Alarm
{
protected:
    AlarmState state;            // Current state of the alarm
    AckMode ackmode;            // Acknowledgment mode of the alarm
    Analog_Mode mode;           // Analog mode of the alarm
    unsigned long ackTime;       // Time when the alarm was acknowledged
    unsigned long ackDuration = 2000;  // Duration for which the alarm remains acknowledged
public:
    Alarm(AckMode m);
    virtual ~Alarm() = default;

    virtual void evaluate_Alm(float value){};
    virtual void evaluate_Alm(bool value){};

    void acknowledge();          // Acknowledge the alarm

    AlarmState getState() const; // Get the current state of the alarm



};


#endif