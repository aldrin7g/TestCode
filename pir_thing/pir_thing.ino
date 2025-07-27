#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
#include <Wire.h>

// Wi-Fi Details
char ssid[] = "Virus#404";                    // Your WiFi SSID (router name)
char pass[] = "password";                     // Your WiFi router password

// ThingSpeak Channel Details
unsigned long myChannelNumber = 2125354;       // Your ThingSpeak Channel Number
const char *myWriteAPIKey = "AOQS070KYKOWT8Y6"; // Your ThingSpeak Write API Key

// Motion Sensor and LED Pins
const int pirPin = 5;        // PIR motion sensor pin
const int ledPin = 4;        // LED pin

WiFiClient client;
int pirState = LOW;           // Initial motion sensor state
int val = 0;                  // Motion sensor value

void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
  Wire.begin();
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    while (WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(ssid, pass);
      Serial.print(".");
      delay(5000);
    }
    Serial.println("\nConnected.");
  }

  val = digitalRead(pirPin); // read input value

  if (val == HIGH) // check if the input is HIGH
  {
    digitalWrite(ledPin, HIGH); // turn LED ON
    if (pirState == LOW)
    {
      Serial.println("Motion detected!"); // print on output change
      pirState = HIGH;
      delay(5000);
    }
  }
  else
  {
    digitalWrite(ledPin, LOW); // turn LED OFF
    if (pirState == HIGH)
    {
      Serial.println("Motion ended!"); // print on output change
      pirState = LOW;
    }
  }

  // Write data to ThingSpeak channel
  ThingSpeak.writeField(myChannelNumber, 1, pirState, myWriteAPIKey);
}
