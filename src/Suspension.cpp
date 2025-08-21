#include <ESP32Servo.h>
#ifndef Legs.h
#include <Legs.h>
#endif
void move(Servo &servo, int angulo, bool invert);
int lowerAngle = 0;
int biggestAngle = 180;
int restAngle = 0;
int activeAngle = 90;
void Legs :: setPosInativo(){
    move(servoFrontLeft, restAngle, false);
    move(servoFrontRight, restAngle, false);
    move(servoRearLeft, restAngle, false);
    move(servoRearRight, restAngle, false);
}

void Legs :: setPosAtivo(){
    move(servoFrontLeft, activeAngle, false);
    move(servoFrontRight, activeAngle, false);
    move(servoRearLeft, activeAngle, false);
    move(servoRearRight, activeAngle, false);
}

void Legs :: moveBackSide(int angulo){
    move(servoRearLeft, angulo, false);
    move(servoRearRight, angulo, false);
}

void Legs :: moveFrontSide(int angulo){
    move(servoFrontLeft, angulo, false);
    move(servoFrontRight, angulo, false);
}

void Legs :: moveLeftSide(int angulo){
    move(servoFrontLeft, angulo, false);
    move(servoRearLeft, angulo, false);
}

void Legs :: moveRightSide(int angulo){
    move(servoFrontRight, angulo, false);
    move(servoRearRight, angulo, false);
}

void move(Servo &servo, 
