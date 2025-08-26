#include <ESP32Servo.h>
class Suspension{
    public:        
        Suspension(short servoFL, short servoFR, short servoRL, short servoRR){
            frontLeftPin = servoFL;
            frontRightPin = servoFR;
            rearLeftPin = servoRL;
            rearRightPin = servoRR;
        }
        void setPosInativo();
        void setPosAtivo();
        void moveLeftSide(int angulo);
        void moveRightSide(int angulo);
        void moveFrontSide(int angulo);
        void moveBackSide(int angulo);
        void moveLeftSideMM(int medida);
        void moveRightSideMM(int medida);
        void moveFrontSideMM(int medida);
        void moveBackSideMM(int medida);
        int max;
        int min;
        void setZero(int zero);
        void setMax(int max);
        void move(short pin, int angulo);
        short frontLeftPin;
        short frontRightPin;
        short rearLeftPin;
        short rearRightPin;
        void keepLastValue();
};