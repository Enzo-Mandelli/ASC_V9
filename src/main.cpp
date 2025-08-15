#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
// Configurações da rede Wi-Fi
const char* ssid = "e";
const char* password = "uybt4536";

// Endereço IP do servidor
const char* serverIP = "10.86.172.58"; // Substitua pelo IP do seu servidor
const int serverPort = 12345;

WiFiClient client;

void setup() {
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
  }

  // Desconectar após enviar a mensagem
  delay(5000); // Esperar 5 segundos antes de enviar outra mensagem
}