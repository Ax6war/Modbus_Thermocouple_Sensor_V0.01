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
    Analog_Mode mode;   
    AlarmType type;             // Type of the alarm
    unsigned long ackTime;       // Time when the alarm was acknowledged
    unsigned long ackDuration = 2000;  // Duration for which the alarm remains acknowledged
    float Analog_Thresholds;
    float Deviation_Thresholds_high;
    float Deviation_Thresholds_low; 
    void evaluate_Analog(float value);
    void evaluate_Deviation(float value);
public:
    Alarm(AlarmType type , AckMode ackmode);
    virtual ~Alarm() = default;

    void evaluate_Alm(float value);
    //virtual void evaluate_Alm(bool value){};

    void acknowledge();          // Acknowledge the alarm

    AlarmState getState(); // Get the current state of the alarm

    void setType(AlarmType t);

    void changeThreshold(float threshold);

    void changeMinMax(float high, float low);

    void setMode(Analog_Mode m);

    AlarmType getType(){
        return this->type;
    };

    float getAnalogThreshold(){
        return this->Analog_Thresholds;
    };

    Analog_Mode getMode(){
        return this->mode;
    };

    AckMode getAckMode(){
        return this->ackmode;
    };
};
#endif