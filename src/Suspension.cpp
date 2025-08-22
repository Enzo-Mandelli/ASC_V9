#include <ESP32Servo.h>
#ifndef Suspension.h
#include <Suspension.h>
#endif
void move(Servo &servo, int angulo, bool invert);
int lowerAngle = 0;//lowest possible value
int biggestAngle = 180;//highest possible value
int restAngle = 0;//lowest usable value
int activeAngle = 90;//highest usable value
void Suspension :: setMax(int max){
    activeAngle = max;
}

void Suspension :: setZero(int min){
    activeAngle = min;
}

void Suspension :: setPosInativo(){
    servoFrontLeft.write(restAngle);
    servoFrontRight.write(restAngle);
    servoRearLeft.write(restAngle);
    servoRearRight.write(restAngle);
}

void Suspension :: setPosAtivo(){
    servoFrontLeft.write(activeAngle);
    servoFrontRight.write(activeAngle);
    servoRearLeft.write(activeAngle);
    servoRearRight.write(activeAngle);
}

void Suspension :: moveBackSide(int angulo){
    servoRearLeft.write(angulo);
    servoRearRight.write(angulo);
}

void Suspension :: moveFrontSide(int angulo){
    servoFrontLeft.write(angulo);
    servoFrontRight.write(angulo);
}

void Suspension :: moveLeftSide(int angulo){
    servoFrontLeft.write(activeAngle);
    servoRearLeft.write(activeAngle);
}

void Suspension :: moveRightSide(int angulo){
    servoFrontRight.write(activeAngle);
    servoRearRight.write(activeAngle);
}

void move(Servo &servo, int angulo) {
    servo.write(angulo);
}

void Suspension :: moveBackSideMM(int angulo){
    //tem que elaborar a aritmetica disso aqui
}

void Suspension :: moveFrontSideMM(int angulo){
    //tem que elaborar a aritmetica disso aqui
}

void Suspension :: moveLeftSideMM(int angulo){
    //tem que elaborar a aritmetica disso aqui
}

void Suspension :: moveRightSideMM(int angulo){
    //tem que elaborar a aritmetica disso aqui
}

