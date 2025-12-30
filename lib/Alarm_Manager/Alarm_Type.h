/*
  Alarm_Type.h
  Purpose: Defines alarm-related enumerations and types.
*/

#ifndef ALARM_TYPE_H
#define ALARM_TYPE_H

// Enumeration for alarm states
enum AlarmState {
    Not_Active,
    Active,
    Acknowledge
};

// Enumeration for acknowledgment modes
enum AckMode{
    Manual,
    Auto
};

// Enumeration for analog modes
enum Analog_Mode{
    HI,
    LO,
};

enum AlarmType{
    ANALOG,
    DIGITAL,
    DEVIATION
};

#endif