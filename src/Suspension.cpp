#include <Suspension.h>
#include <Pins.h>

//================================================================================
// DEFINIÇÃO DAS VARIÁVEIS GLOBAIS
//================================================================================

// Estas variáveis definem os angulos de controle
int lowerAngle = 0;   // Valor mínimo do angulo (geralmente 0)
int biggestAngle = 180; // Valor máximo do angulo (geralmente 180)
int restAngle = 0;    // Posição de repouso
int activeAngle = 90; // Posição ativa (90 graus como exemplo)
static int lastValueFR = 0;
static int lastValueFL = 0;
static int lastValueRR = 0;
static int lastValueRL = 0;

/*
====Ordem====
01_lastPulseFR
02_lastPulseFL
03_lastPulseRR
04_lastPulseRL
*/


//================================================================================
// IMPLEMENTAÇÃO DA FUNÇÃO MOVE
//================================================================================

// Esta funcao substitui o servo.write(), enviando pulsos PWM manualmente
void Suspension :: move(short pin, int angulo) {
    
    switch(pin){
        case pFrontLeft:
            fr.write(angulo);
            lastValueFL = angulo;
            break;
        case pFrontRight:
            fl.write(angulo);
            lastValueFR = angulo;
            break;
        case pRearLeft:
            rl.write(angulo);
            lastValueRL = angulo;
            break;
        case pRearRight:
            rr.write(angulo);
            lastValueRR = angulo;
            break;
    }
}

// Seta o valor do angulo ativo
void Suspension::setMax(int max) {
    activeAngle = max;
}

// Seta o valor do angulo de repouso (o nome original 'setZero' foi corrigido para 'setZero')
void Suspension::setZero(int min) {
    restAngle = min;
}

// Move todos os servos para a posicao de repouso
void Suspension::setPosInativo() {
    move(frontLeftPin, restAngle);
    move(frontRightPin, restAngle);
    move(rearLeftPin, restAngle);
    move(rearRightPin, restAngle);
    lastValueFL = restAngle;
    lastValueFR = restAngle;
    lastValueRL = restAngle;
    lastValueRR = restAngle;
}

// Move todos os servos para a posicao ativa
void Suspension::setPosAtivo() {
    move(frontLeftPin, activeAngle);
    move(frontRightPin, activeAngle);
    move(rearLeftPin, activeAngle);
    move(rearRightPin, activeAngle);
    lastValueFL = activeAngle;
    lastValueFR = activeAngle;
    lastValueRL = activeAngle;
    lastValueRR = activeAngle;
}

// Move a parte traseira
void Suspension::moveBackSide(int angulo) {
    move(rearLeftPin, angulo);
    move(rearRightPin, angulo);
    lastValueRL = angulo;
    lastValueRR = angulo;
}

// Move a parte frontal
void Suspension::moveFrontSide(int angulo) {
    move(frontLeftPin, angulo);
    move(frontRightPin, angulo);
    lastValueFL = angulo;
    lastValueFR = angulo;
}

// Move o lado esquerdo
void Suspension::moveLeftSide(int angulo) {
    move(frontLeftPin, angulo);
    move(rearLeftPin, angulo);
    lastValueRL = angulo;
    lastValueFL = angulo;
}

// Move o lado direito
void Suspension::moveRightSide(int angulo) {
    move(frontRightPin, angulo);
    move(rearRightPin, angulo);
    lastValueRR = angulo;
    lastValueFR = angulo;
}


void Suspension::moveBackSideMM(int angulo) {
    // Logica de aritmetica para angulos de mm aqui
}

void Suspension::moveFrontSideMM(int angulo) {
    // Logica de aritmetica para angulos de mm aqui
}

void Suspension::moveLeftSideMM(int angulo) {
    // Logica de aritmetica para angulos de mm aqui
}

void Suspension::moveRightSideMM(int angulo) {
    // Logica de aritmetica para angulos de mm aqui
}