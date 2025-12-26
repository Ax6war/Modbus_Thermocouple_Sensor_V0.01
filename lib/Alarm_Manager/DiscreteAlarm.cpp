#include "DiscreteAlarm.h"

/*
  DiscreteAlarm.cpp
  Purpose: Implements discrete alarm logic (on/off transitions, ack handling).
*/

DiscreteAlarm::DiscreteAlarm(AckMode ack, bool AlarmOn) : Alarm(ack) , Alarm_value(AlarmOn){}


void DiscreteAlarm::evaluate_Alm(bool value){
    // Evaluate alarm state based on the acknowledgment mode and input value
    if(ackmode == Auto){
          if (value == Alarm_value){
        state = Active;
        }else{
         state = Not_Active;   
        }  
    }

    if (ackmode == Manual){
        if (value == Alarm_value){
        state = Active;
        }
    }
         







}