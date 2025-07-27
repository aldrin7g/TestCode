#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>
#include <DHT.h>

#define FIREBASE_HOST "streetlight-0707"
#define FIREBASE_AUTH "your-auth-token"
#define WIFI_SSID "your-ssid"
#define WIFI_PASSWORD "your-password"

#define DHTPIN 2           // Define the pin where the DHT11 sensor is connected
#define DHTTYPE DHT11       // Define the type of sensor (DHT11, DHT22, AM2302)

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  dht.begin();

  // Initialize Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  // Read temperature and humidity from the DHT11 sensor
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (!isnan(temperature) && !isnan(humidity)) {
    // Send data to Firebase Firestore
    Firebase.setFloat("/sensors/dht11/temperature", temperature);
    Firebase.setFloat("/sensors/dht11/humidity", humidity);
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print("°C, Humidity: ");
    Serial.print(humidity);
    Serial.println("%");
  } else {
    Serial.println("Failed to read from DHT sensor.");
  }

  delay(10000); // Adjust the delay as needed for your data update frequency
}