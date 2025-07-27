#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <MQ135.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <ThingSpeak.h>

#define DHTPIN 23
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define MQ135PIN A0
MQ135 mq135(MQ135PIN);

#define SDA 2
#define SCL 1
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

const char* ssid = "Samson"; // your network SSID (name)
const char* password = "vhik4420*"; // your network password

WiFiClient client;

unsigned long interval = 20000; // time interval in milliseconds to send data to ThingSpeak
unsigned long previousMillis = 0;

void setup() {
  Serial.begin(115200);
  lcd.init();                      // initialize the LCD
  lcd.backlight();                 // turn on backlight
  dht.begin();
  WiFi.begin(ssid, password);
  ThingSpeak.begin(client);        // initialize ThingSpeak client
}

void loop() {
  float h = dht.readHumidity();//Serial.println(h);
  float t = dht.readTemperature();//Serial.println(t);
  float r0 = mq135.getResistance();
  float ppm = mq135.getPPM();

  lcd.setCursor(0, 0); // set cursor to the first column and first row
  lcd.print("Temp:");  // print the temperature label
  lcd.print(t);  // print the temperature
  lcd.print((char)223);  // print the degree symbol
  lcd.print("C ");  // print the temperature unit
  lcd.setCursor(0, 1); // set cursor to the first column and second row
  lcd.print("Humidity: ");  // print the humidity label
  lcd.print(h);  // print the humidity
  lcd.print("% ");  // print the humidity unit
  lcd.setCursor(9, 0); 
  lcd.print(" ");
  lcd.setCursor(10, 0); // set cursor to the eleventh column and first row
  lcd.print("Air: ");  // print the air quality label
  lcd.print(ppm);  // print the air quality in ppm
  lcd.print("ppm");  // print the air quality unit

  if (WiFi.status() == WL_CONNECTED) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      ThingSpeak.setField(1, t);  // set temperature value to field 1
      ThingSpeak.setField(2, h);  // set humidity value to field 2
      ThingSpeak.setField(3, ppm);  // set air quality value to field 3
      int x = ThingSpeak.writeFields(2108861,"PDOMVJ7FPX5OADF1");  // send data to ThingSpeak
      if (x == 200) {
        Serial.println("Data sent to ThingSpeak");
      } else {
        Serial.println("Error sending data to ThingSpeak");
      }
    }
  } else {
    Serial.println("WiFi connection lost");
}
delay(2000); // delay for 2 seconds
}
