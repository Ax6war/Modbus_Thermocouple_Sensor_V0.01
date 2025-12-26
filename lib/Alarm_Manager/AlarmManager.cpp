/*
  AlarmManager.cpp
  Purpose: Implements AlarmManager operations (add/remove/evaluate/update).
*/

#include "AlarmManager.h"


AlarmManager::AlarmManager() : count(0) {}

bool AlarmManager::addAlarm(Alarm* alarm){
  if (count >= MAX_ALARMS) return false;
  alarms[count++] = alarm;
  return true;
}

void AlarmManager::acknowledgeAll(){

  for(int i; i < count; i++){
    alarms[i]->acknowledge();
  }



}





