#include "Alarm.h"

Alarm::Alarm(AckMode ack) : state(Not_Active),ackmode(ack){}

void Alarm::acknowledge(){

    if(state == Active && ackmode == Manual){
        state = Acknowledge;
        ackTime = millis();
    }
}

AlarmState Alarm::getState() const{
    if (state == Acknowledge &&
      millis() - ackTime >= ackDuration) {
    return Not_Active;
  }
    return state;
}