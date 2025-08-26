#include <Adafruit_VL53L0X.h>
class SensordDistanci{
    public:
        #define LOX1_ADDRESS 0x30
        #define LOX2_ADDRESS 0x31
        Adafruit_VL53L0X sensorRL = Adafruit_VL53L0X();
        Adafruit_VL53L0X sensorRR = Adafruit_VL53L0X();
        void setId();
        float readRL();
        float readRR();
        
        
};