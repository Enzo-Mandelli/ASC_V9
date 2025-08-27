#include <SensorDistancia.h>
#include <Pins.h>
void SensorDistancia :: setId() {
  // all reset
  digitalWrite(shutDownA, LOW);    
  digitalWrite(shutDownB, LOW);
  delay(10);
  // all unreset
  digitalWrite(shutDownA, HIGH);
  digitalWrite(shutDownB, HIGH);
  delay(10);

  // activating LOX1 and resetting LOX2
  digitalWrite(shutDownA, HIGH);
  digitalWrite(shutDownB, LOW);

  // initing LOX1
  if(!sensorRL.begin(LOX1_ADDRESS)) {
    Serial.println(F("Failed to boot first VL53L0X"));
    while(1);
  }
  delay(10);

  // activating LOX2
  digitalWrite(shutDownB, HIGH);
  delay(10);

  //initing LOX2
  if(!sensorRR.begin(LOX2_ADDRESS)) {
    Serial.println(F("Failed to boot second VL53L0X"));
    while(1);
  }
}

float SensorDistancia::readRL() {
  
  return 0.0;
}

float SensorDistancia::readRR() {
  return 0.0;
}