#include "DiscreteAlarm.h"

DiscreteAlarm::DiscreteAlarm(AckMode ack, bool AlarmOn) : Alarm(ack) , Alarm_value(AlarmOn){}


void DiscreteAlarm::evaluate_Alm(bool value){
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