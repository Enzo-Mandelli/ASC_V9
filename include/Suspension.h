#include <ESP32Servo.h>
class Suspension{
    public:
        Suspension(Servo fr, Servo fl, Servo rr, Servo rl);

        
        Suspension(Servo* ptr_ServoFL, Servo* ptr_ServoFR, Servo* ptr_ServoRL, Servo* ptr_ServoRR){
            servoFrontLeft = *ptr_ServoFL;
            servoFrontRight = *ptr_ServoFR;
            servoRearLeft = *ptr_ServoRL;
            servoRearRight = *ptr_ServoRR;
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
        Servo servoFrontLeft;
        Servo servoFrontRight;
        Servo servoRearRight;
        Servo servoRearLeft;
};