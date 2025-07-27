#include "ESP8266Pin.h"
#include<dht11.h>
dht22 DHT22;
#define PIN 8
void setup(){
  Serial.begin(9600);
}
void loop(){
  int chk = DHT11.read(PIN);
  Serial.print("\nTemperature: ");
  Serial.println(DHT11.temperature);
  Serial.print("Humidity: ");
  Serial.println(DHT11.humidity);
  delay(3000);
}
