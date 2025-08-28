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
const short quantServos = 4;
static int pulses[quantServos] = {500,500,500,500};
/*
====Ordem====
01_lastPulseFR
02_lastPulseFL
03_lastPulseRR
04_lastPulseRL
*/
int indexOrdenados[quantServos] = {0,0,0,0};
int lastValueSteeringL = 0;
int lastValueSteeringR = 0;
int delayPadrao = 400;

//================================================================================
// IMPLEMENTAÇÃO DA FUNÇÃO MOVE
//================================================================================

// Esta funcao substitui o servo.write(), enviando pulsos PWM manualmente
void Suspension :: move(short pin, int angulo) {
    // Garante que o angulo esteja dentro do range
    if (angulo < lowerAngle) angulo = lowerAngle;
    if (angulo > biggestAngle) angulo = biggestAngle;

    // Mapeia o angulo para a largura de pulso em microssegundos
    // (Padrão para servos: 0 deg = 500us, 180 deg = 2500us)
    int pulso = map(angulo, lowerAngle, biggestAngle, 500, 2500); 
    switch(pin){
        case pFrontLeft:
            lastValueFL = angulo;
            pulses[0] = pulso;
            break;
        case pFrontRight:
            lastValueFR = angulo;
            pulses[1] = pulso;
            break;
        case pRearLeft:
            lastValueRL = angulo;
            pulses[2] = pulso;
            break;
        case pRearRight:
            lastValueRR = angulo;
            pulses[3] = pulso;
            break;
    }
}

void Suspension :: keepLastValue(){
    int tempoPassado = delayPadrao;
    for(int i = 0; i < quantServos; i++){
        switch(indexOrdenados[i]){
            case 0:
                delay(pulses[i] - tempoPassado);
                digitalWrite(frontRightPin, LOW);
                break;
            case 1:
                delay(pulses[i] - tempoPassado);
                digitalWrite(frontLeftPin, LOW);
                break;
            case 2:
                delay(pulses[i] - tempoPassado);
                digitalWrite(rearRightPin, LOW);
                break;
            case 3:
                delay(pulses[i] - tempoPassado);
                digitalWrite(rearLeftPin, LOW);
                break;
        }
        tempoPassado = tempoPassado + pulses[i];
    }
    insertionSort();
    move(frontLeftPin, lastValueFL);
    move(frontRightPin, lastValueFR);
    move(rearLeftPin, lastValueRL);
    move(rearRightPin, lastValueRR);
    digitalWrite(frontLeftPin, HIGH);
    digitalWrite(frontRightPin, HIGH);
    digitalWrite(rearLeftPin, HIGH);
    digitalWrite(rearLeftPin, HIGH);
    delay(delayPadrao);
}

void desligaNaOrdem(int indexServo){
    int tempoPassado = delayPadrao;
    switch(indexServo){
        case 0:
            delay(pulses[0]);
            break;
        case 1:
            delay(pulses[1]);
            break;
        case 2:
            delay(pulses[0]);
            break;
        case 3:
            delay(pulses[0]);
            break;
    }

}

void insertionSort() {
    int n = quantServos / sizeof(pulses[0]);
    // Loop externo: Começa do segundo elemento até o final do array.
    for (int i = 1; i < n; i++) {
        int key = pulses[i];
        int index_key = indexOrdenados[i]; // Guarda o indice correspondente
        int j = i - 1;

        // Move elementos maiores para a direita
        while (j >= 0 && pulses[j] > key) {
            pulses[j + 1] = pulses[j];
            indexOrdenados[j + 1] = indexOrdenados[j]; // Move o indice 
            j = j - 1;
        }

        // Insere o elemento e o indice na posicao correta
        pulses[j + 1] = key;
        indexOrdenados[j + 1] = index_key;
    }
}




void Suspension :: start() {
    // Cria a thread.
    // O último argumento é o ponteiro para a nossa instância.
    xTaskCreate(
        threadEntry,         // Função de entrada da thread
        "Servos",   // Nome da thread
        2048,                // Tamanho da pilha em bytes
        this,                // Parâmetro a ser passado para a threadEntry (o ponteiro `this`)
        1,                   // Prioridade da thread
        NULL                 // Handle da task (opcional)
    );
}

void Suspension :: threadEntry(void* parameter){
    Suspension* instance = (Suspension*)parameter; //converte o ponteiro generico para o tipo da classe
    instance -> run(); // chama a thread
}

void Suspension :: run() {
    Serial.println("Thread da classe iniciada!");
    for(;;) {
        keepLastValue();
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