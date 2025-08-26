#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <ESP32Servo.h>
#include <Suspension.h>
#include <Pins.h>
//======== Configurações da rede Wi-Fi ========
const char* ssid = "e";
const char* password = "uybt4536";

//======== Endereço IP do servidor ========
const char* serverIP = "10.189.197.58"; // Substitua pelo IP do seu servidor
const int serverPort = 12345;
WiFiClient client;
// ======== Servos ========
int pin = 13;

Suspension susp(pFrontLeft, pFrontRight, pRearLeft, pRearRight);
void SetaMovimento(String message);

void setup() {
  pinMode(pFrontLeft, OUTPUT);
  pinMode(pFrontRight, OUTPUT);
  pinMode(pRearLeft, OUTPUT);
  pinMode(pRearRight, OUTPUT);
  susp.setPosInativo();
  Serial.begin(9600);
  // Conectar ao Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Conectar ao servidor
  if (!client.connected()) {
    if (client.connect(serverIP, serverPort)) {
      Serial.println("Connected to server");
    } else {
      Serial.println("Connection failed");
      delay(5000); // Esperar 5 segundos antes de tentar novamente
      return;
    }
  }

  // Enviar mensagem para o servidor
  String message = "Hello from ESP32!";
  client.print(message);
  Serial.println("Message sent to server");

  // Aguardar resposta do servidor
  if (client.available()) {
    String response = client.readStringUntil('\n');
    Serial.print("Response from server: ");
    Serial.println(response);
    SetaMovimento(response);
  }
  delay(1000);
  // Desconectar após enviar a mensagem
}

void SetaMovimento(String message){
  const char* ptr = message.c_str();
  String itensSegmentados[4] = {"","","",""};
  bool finished = true;
  short index = 0;
  while(finished){ //separa a String com todos os angulos um uma array com angulos isolados
    if(*ptr == ';') {  //verifica se a mensagem chegou ao fim
      finished = false;
      continue; // caso tenha chegado para o loop 
    }
    if(*ptr != ',') {
      itensSegmentados[index] = itensSegmentados[index] + *ptr; // caso o character não seja uma virgula soma a String de angulos individuais
    }else{
      index++;
    }
    ptr++; //percorre a array de char usando ponteiro
  }
  susp.move(pFrontRight, itensSegmentados[0].toInt());
  susp.move(pFrontLeft, itensSegmentados[1].toInt());
  susp.move(pRearRight, itensSegmentados[2].toInt());
  susp.move(pRearLeft, itensSegmentados[3].toInt());
}