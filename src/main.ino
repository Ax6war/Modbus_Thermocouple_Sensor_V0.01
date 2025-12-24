#include <Arduino.h>

//MAX31856 Library
#include <TemperatureSensor.h>

//ALarm management library
#include <Alarm_Manager/AlarmManager.h>
#include <Alarm_Manager/DiscreteAlarm.h>
#include <Alarm_Manager/AnalogAlarm.h>

//ModbusIP server With ENC28J60
#include <EtherCard.h>
#include <Modbus.h>
#include <ModbusIP_ENC28J60.h>

//CS pin For MAX31856
#define CS_PIN_MAX31856 9

//CS pin For ENC28J60 (Already in the library as 10)
//#define CS_PIN_ENC28J60 10*

//Global SPI pin
#define MAX_MOSI_PIN 6
#define MAX_MISO_PIN 7
#define MAX_CLK_PIN 8

//MAX81356 Reading register
int InputRegisterData[16];
bool DiscreteInputData[16];
int HoldingRegister[16];
bool CoilRegister[16];

unsigned long lastmillis[16];

unsigned long ts_Comm;
unsigned long ts_Serial;
unsigned long ts_Alarm;

float Temp_Reading;

bool MaxGood = false;

//Alarm declaration
DiscreteAlarm Dis_0(Manual, true);

AnalogAlarm Alm_0(Manual, 30.0);

//declaration of MAX81356 Library object (CS_Pin, MOSI_Pin, MISO_Pin, CLK_Pin)
TemperatureSensor TempSensor(CS_PIN_MAX31856, MAX_MOSI_PIN, MAX_MISO_PIN, MAX_CLK_PIN);

//Delcaration of ModbusIP Object
ModbusIP mb;

//delcaration of alarm manageer object

AlarmManager almManager;


void setup(){
    //Serial port for debug and config(9600)
    Serial.begin(9600);
    // The media access control (ethernet hardware) address for the shield
    byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
    // The IP address for the shield
    byte ip[] = { 192, 168, 0, 105 };
    //Config Modbus IP
    mb.config(mac, ip);
    //Add modbus register offset
    for(int i = 0; i < 16; i++){
    mb.addIreg(i);
    mb.addIsts(i); 
    mb.addCoil(i);
    mb.addHreg(i);
    }
    
    //Initialize the MAX31856 with Type J And continuous reading
    if(TempSensor.init(MAX31856_TCTYPE_J,MAX31856_CONTINUOUS) == true){

        MaxGood = true;

    }else{

        MaxGood = false;
    }

    almManager.addAlarm(&Dis_0);
    almManager.addAlarm(&Alm_0);


    ts_Comm = millis();
    ts_Serial = millis();
    ts_Alarm = millis();
}

void loop(){
    //Read thermocouple temperatrue and * 100 for transmition
    InputRegisterData[0] = TempSensor.readTemperature();
    //Read CJT thermocouple card and * 100 for transmition
    InputRegisterData[1] = TempSensor.readCJTtemperature();

    float TempC = InputRegisterData[0] / 100.0;

    //Discrete input gestion
    
        //Discrete input 0 : Life bit
            if(millis() > lastmillis[0] + 150){
                lastmillis[0] = millis();
                DiscreteInputData[0] = !DiscreteInputData[0];
            }

        //MAX31856 card is initialized    
                DiscreteInputData[1] = MaxGood;
        
        //

    //Coils
        
        //Coils 0 : Get TC type
          if (CoilRegister[0] == true) {InputRegisterData[2] = TempSensor.readTCType();}  
            

    
    /*if (millis() > ts_Serial + 1000) {
        ts_Serial = millis();
        Serial.print("HR:");
        for(int i= 0;i < 16;i++){            
            Serial.print(HoldingRegister[i]);
            Serial.print(",");            
        }
        Serial.println();
        Serial.print("Coils:");
        for(int i= 0;i < 16;i++){            
            Serial.print(CoilRegister[i] ? 1 : 0); 
            Serial.print(",");
        }
        Serial.println();
    }*/



    if(millis() > ts_Alarm + 1000){
        ts_Alarm = millis();
        Dis_0.evaluate_Alm(CoilRegister[0]);

        Alm_0.evaluate_Alm(TempC);

        if(CoilRegister[1] == 1){
            
            Dis_0.acknowledge();
            Alm_0.acknowledge();
        }
        
        Serial.println(String(Alm_0.getState()));
        Serial.println(TempC);
    }
    
    //Read each 750 ms
    if (millis() > ts_Comm + 250) {
       ts_Comm = millis();

       //Setting raw value (0 to TYPE_THERMOCOUPLE)
       for(int i = 0; i < 15; i++){
        mb.Ireg(i, InputRegisterData[i]);
        mb.Ists(i,DiscreteInputData[i]);       
        CoilRegister[i] = mb.Coil(i);
        HoldingRegister[i] = mb.Hreg(i);
        
        //Mb move the value to registers
        mb.task();
       }
       
      
   }

}



