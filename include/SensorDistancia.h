#ifndef SENSORDISTANCIA_H
#define SENSORDISTANCIA_H
#include <Adafruit_VL53L0X.h>
#include <Arduino.h>
class SensorDistancia{
    public:
        #define LOX1_ADDRESS 0x30
        #define LOX2_ADDRESS 0x31
        Adafruit_VL53L0X sensorRL = Adafruit_VL53L0X();
        Adafruit_VL53L0X sensorRR = Adafruit_VL53L0X();
        void setId();
        float readRL();
        float readRR();
        
        
};
#endif