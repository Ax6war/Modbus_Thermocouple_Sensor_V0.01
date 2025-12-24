#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H



#include <Adafruit_MAX31856.h>


class TemperatureSensor{
        private:
            Adafruit_MAX31856 MAX31856;
            max31856_thermocoupletype_t thermocouple_type;
            max31856_conversion_mode_t thermocouple_mode;
            
            
            
        public:
            TemperatureSensor(int cs, int mosi, int miso, int clk);
            bool init(max31856_thermocoupletype_t T_Type, max31856_conversion_mode_t T_Mode);
            int16_t readTemperature();
            int16_t readCJTtemperature();
            int readTCType();



};

    

#endif