/*
  AlarmManager.h
  Purpose: Declaration of the AlarmManager which owns/manages alarms.
*/

#ifndef ALARMMANAGER_H
#define ALARMMANAGER_H

#include "Alarm.h"

#define MAX_ALARMS 8

class AlarmManager
{
private:
    Alarm* alarms[MAX_ALARMS];
    int count;
public:
    AlarmManager();

    bool addAlarm(Alarm* alarm);

    void acknowledgeAll();



};




























#endif // MACRO
