// Arduino main sketch - cleaned formatting and added comments.
// Functionality and symbol names unchanged.

#include <Arduino.h>

// MAX31856 Temperature sensor library
#include <TemperatureSensor.h>

// Alarm management library
#include <AlarmManager.h>
#include <DiscreteAlarm.h>
#include <AnalogAlarm.h>

// ModbusIP server with ENC28J60
#include <EtherCard.h>
#include <Modbus.h>
#include <ModbusIP_ENC28J60.h>

// CS pin for MAX31856
#define CS_PIN_MAX31856 9

// CS pin for ENC28J60 (Already in the library as 10)
//#define CS_PIN_ENC28J60 10*

// Global SPI pins for MAX31856
#define MAX_MOSI_PIN 6
#define MAX_MISO_PIN 7
#define MAX_CLK_PIN 8

// Modbus registers / coils / inputs
int InputRegisterData[16];
bool DiscreteInputData[16];
int HoldingRegister[16];
bool CoilRegister[16];

constexpr int REG_COUNT = 16;

// Last toggles / timestamps
unsigned long lastmillis[16];

unsigned long ts_Comm;
unsigned long ts_Serial;
unsigned long ts_Alarm;

float Temp_Reading;

bool MaxGood = false;

// Alarm declarations
DiscreteAlarm Dis_0(Manual, true);
AnalogAlarm Alm_0(Manual, 30.0, HI);

// MAX31856 sensor object (CS_Pin, MOSI_Pin, MISO_Pin, CLK_Pin)
TemperatureSensor TempSensor(CS_PIN_MAX31856, MAX_MOSI_PIN, MAX_MISO_PIN, MAX_CLK_PIN);

// ModbusIP object
ModbusIP mb;

// Alarm manager
AlarmManager almManager;

void setup() {
    // Serial for debug and configuration
    Serial.begin(9600);

    // MAC and static IP for ENC28J60
    byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
    byte gateway[] = { 0, 0, 0, 0};
    byte dns[] = { 0, 0, 0, 0};
    byte subnet[] = { 255, 255, 255, 0 };
    byte ip[]  = { 192, 168, 0, 105 };

    // Configure Modbus IP
    mb.config(mac, ip, dns, gateway, subnet);

    // Add Modbus registers/inputs/coils/holding registers
    for (int i = 0; i < REG_COUNT; i++) {
        mb.addIreg(i);
        mb.addIsts(i);
        mb.addCoil(i);
        mb.addHreg(i);
    }

    // Initialize arrays to safe defaults
    for (int i = 0; i < REG_COUNT; ++i) {
        InputRegisterData[i] = 0;
        HoldingRegister[i] = 0;
        DiscreteInputData[i] = false;
        CoilRegister[i] = false;
        lastmillis[i] = 0;
    }

    // Initialize the MAX31856 with Type J and continuous reading
    if (TempSensor.init(MAX31856_TCTYPE_J, MAX31856_CONTINUOUS) == true) {
        MaxGood = true;
    } else {
        MaxGood = false;
    }

    // Add alarms to manager
    almManager.addAlarm(&Dis_0);
    almManager.addAlarm(&Alm_0);

    // Initialize timestamps
    ts_Comm = millis();
    ts_Serial = millis();
    ts_Alarm = millis();
}

void loop() {
    // Read thermocouple temperature (stored as integer * 100)
    InputRegisterData[0] = TempSensor.readTemperature();

    // Read cold-junction thermometer (CJT)
    InputRegisterData[1] = TempSensor.readCJTtemperature();

    float TempC = InputRegisterData[0] / 100.0;

    // Discrete input management
    // Discrete input 0: life (heartbeat) bit toggled ~150 ms
    if (millis() > lastmillis[0] + 250) {
        lastmillis[0] = millis();
        DiscreteInputData[0] = !DiscreteInputData[0];

        // If coil 0 requests TC type, update input register 2
        if (CoilRegister[0]) {
            if (MaxGood) InputRegisterData[2] = TempSensor.readTCType();
            else InputRegisterData[2] = 0;
        }

        // Indicate whether MAX31856 card is initialized
        DiscreteInputData[1] = MaxGood;
    }

    // Periodic serial debug output (~1s)
   /* if (millis() > ts_Serial + 1000) {
        ts_Serial = millis();

        Serial.print("HR:");
        for (int i = 0; i < 16; i++) {
            Serial.print(HoldingRegister[i]);
            Serial.print(",");
        }
        Serial.println();

        Serial.print("Coils:");
        for (int i = 0; i < 16; i++) {
            Serial.print(CoilRegister[i] ? 1 : 0);
            Serial.print(",");
        }
        Serial.println();
    }
*/

    // Alarm evaluation every 1 second
    if (millis() > ts_Alarm + 1000) {
        ts_Alarm = millis();

        Dis_0.evaluate_Alm(CoilRegister[0]);
        Alm_0.evaluate_Alm(TempC);

        if(Alm_0.getState() == Active){
            DiscreteInputData[3] = true;
        }else{
            DiscreteInputData[3] = false;
        }

        // If coil 1 is set, acknowledge alarms
        if (CoilRegister[1]) {
            Dis_0.acknowledge();
            Alm_0.acknowledge();
        }
    }

    // Communication / Modbus task handling (~250 ms)
    if (millis() > ts_Comm + 250) {
        ts_Comm = millis();

        // Update Modbus registers and read coil/holding values
        for (int i = 0; i < 16; i++) {
            mb.Ireg(i, InputRegisterData[i]);
            mb.Ists(i, DiscreteInputData[i]);
            CoilRegister[i] = mb.Coil(i);
            HoldingRegister[i] = mb.Hreg(i);
        }

        // Let Modbus stack run its tasks
        mb.task();
    }
}




