#include "TemperatureSensor.h"



TemperatureSensor::TemperatureSensor(int cs, int mosi, int miso, int clk) : MAX31856(cs, mosi, miso, clk){}

bool TemperatureSensor::init(max31856_thermocoupletype_t T_Type, max31856_conversion_mode_t T_Mode){
    thermocouple_type = T_Type;
    thermocouple_mode = T_Mode;
    if(!MAX31856.begin()){
        Serial.print("Not begin");
        return false;
    }
    MAX31856.setThermocoupleType(thermocouple_type);
    MAX31856.setConversionMode(thermocouple_mode);
    return true;
}

int16_t TemperatureSensor::readTemperature(){
    float value = MAX31856.readThermocoupleTemperature();
    return (int16_t)(value*100);


}

int16_t TemperatureSensor::readCJTtemperature(){
    float value = MAX31856.readCJTemperature();
    return (int16_t)(value*100);



}

int TemperatureSensor::readTCType(){
  max31856_thermocoupletype_t temp =  MAX31856.getThermocoupleType();
    switch (temp)
    {
    case  MAX31856_TCTYPE_B :
        return 0;
    break;

    case MAX31856_TCTYPE_E :
        return 1;
    break;

    case MAX31856_TCTYPE_J :
        return 2;
    break;

    case MAX31856_TCTYPE_K :
        return 3;
    break;

    case MAX31856_TCTYPE_N :
        return 4;
    break;

    case MAX31856_TCTYPE_R  :
        return 5;
    break;     


    case MAX31856_TCTYPE_S  :
        return 6;
    break;     


    case MAX31856_TCTYPE_T  :
        return 7;
    break;     

    case MAX31856_VMODE_G8  :
        return 8;
    break; 
    
    case MAX31856_VMODE_G32 :
        return 9;
    break; 

    default:
        return -1;
    break;
    }



}