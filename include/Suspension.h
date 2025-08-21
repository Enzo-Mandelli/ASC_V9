#include <ESP32Servo.h>
class Suspension{
    public:
        Suspension(Servo fr, Servo fl, Servo rr, Servo rl);
        Servo servoFrontLeft;
        Servo servoFrontRight;
        Servo servoRearRight;
        Servo servoRearLeft;
        int max;
        int min;
        void setZero(int zero);
        void setMax(int max);
        void setAngleRight(int angle);
        void setAngleLeft(int angle);
        void setAngleFront(int angle);
        void setAngleRear(int angle);
        void testing();
        Legs(Servo* ptr_ServoFL, Servo* ptr_ServoFR, Servo* ptr_ServoRL, Servo* ptr_ServoRR){
            servoFrontLeft = *ptr_ServoFL;
            servoFrontRight = *ptr_ServoFR;
            servoRearLeft = *ptr_ServoRL;
            servoRearRight = *ptr_Servo p00000000000000000000000pppç~;.l][´´´´´´´´´´p[]];
        }
        void setPosInativo();
        void setPosAtivo();
        void moveLeftSide(int angulo);
        void moveRightSide(int angulo);
        void moveFrontSide(int angulo);
        void moveBackSide(int angulo);

};