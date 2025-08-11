#include <ESP32Servo.h>
class Suspension{
    public:
        Suspension(Servo fr, Servo fl, Servo rr, Servo rl);
        Servo fr;
        Servo fl;
        Servo rr;
        Servo rl;
        int max;
        int min;
        void setZero(int zero);
        void setMax(int max);
        void setAngleRight(int angle);
        void setAngleLeft(int angle);
        void setAngleFront(int angle);
        void setAngleRear(int angle);
        void testing();

};