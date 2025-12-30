/*
  Alarm.cpp
  Purpose: Implementation of base Alarm behavior.
*/

#include "Alarm.h"

Alarm::Alarm(AlarmType type, AckMode ack){
  this->ackmode = ack;
  this->type = type;
  this->state = Not_Active;
}



void Alarm::acknowledge(){

    if(state == Active && ackmode == Manual){
        state = Acknowledge;
        ackTime = millis();
    }
}

AlarmState Alarm::getState(){
    if (state == Acknowledge &&
      millis() - ackTime >= ackDuration) {
    return Not_Active;
  }
    return state;
}

void Alarm::evaluate_Alm(float value){

switch (type)
{   
    case ANALOG:
    evaluate_Analog(value);

    break;

    case DEVIATION:
    evaluate_Deviation(value);

    break;

    case DIGITAL:

    break;
}
}

void Alarm::evaluate_Analog(float value){



      if (ackmode == Auto) {

        switch (mode)
        {
        case HI:
            if (value >= Analog_Thresholds) {
                this->state = Active;
            } 
            else {
                this->state = Not_Active;
            }
            break;

        case LO:
            if (value <= Analog_Thresholds) {
                this->state = Active;
            } 
            else {
                this->state = Not_Active;
            }
            break;

        default:

            break;
        }
      
      }
        if (ackmode == Manual) {

            switch (mode)
            {
            case HI:
                if (value >= Analog_Thresholds) {
                    this->state = Active;
                } 
                break;

            case LO:
                if (value <= Analog_Thresholds) {
                    this->state = Active;
                }
                break;
            
            default:
                break;
            }
          }
      
}

void Alarm::evaluate_Deviation(float value){

      if (ackmode == Auto) {

        if (value >= Deviation_Thresholds_high || value <= Deviation_Thresholds_low) {
            this->state = Active;
        } 
        else {
            this->state = Not_Active;
        }
      
      }
        if (ackmode == Manual) {

            if (value >= Deviation_Thresholds_high || value <= Deviation_Thresholds_low) {
                this->state = Active;
            } 
          }
      }

void Alarm::setType(AlarmType t){
   this->type = t;
}

void Alarm::changeThreshold(float threshold){
    this->Analog_Thresholds = threshold;
}

void Alarm::changeMinMax(float high, float low){
    this->Deviation_Thresholds_high = high;
    this->Deviation_Thresholds_low = low;
}

void Alarm::setMode(Analog_Mode m){
    this->mode = m;
}