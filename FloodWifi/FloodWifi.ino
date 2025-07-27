#include <WiFi.h>
#include <WiFiClient.h>
#include <ThingSpeak.h>

const char* ssid = "your_SSID_here";       // Replace with your network SSID
const char* password = "your_PASSWORD_here"; // Replace with your network password

const int trigPin = 9;   // Trig pin of the Ultrasonic sensor
const int echoPin = 10;  // Echo pin of the Ultrasonic sensor
const int ledPin = 13;   // Pin connected to LED

long duration;
int distance;

unsigned long last_detected_time = 0; // Variable to keep track of the last time an object was detected
bool is_object_detected = false;      // Flag to indicate if an object is currently detected

WiFiClient client;
unsigned long lastConnectionTime = 0;  // Last time you connected to ThingSpeak
const unsigned long updateInterval = 20000; // Time interval between updates (in milliseconds)

// ThingSpeak Channel and API keys
unsigned long channelID = YOUR_CHANNEL_ID_HERE;
const char* writeAPIKey = "YOUR_WRITE_API_KEY_HERE";

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);    // Initialize Serial communication
  
  // Connect to WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  ThingSpeak.begin(client);  // Initialize ThingSpeak client
}

void loop() {
  // Send 10us pulse to the Ultrasonic sensor to trigger the measurement
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the duration of the echo signal and calculate distance
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  // If an object is detected within 20cm, turn on the LED
  if (distance < 20) {
    // If an object is not already detected, set the flag and record the time
    if (!is_object_detected) {
      is_object_detected = true;
      last_detected_time = millis();
    }
  } else {
    // If no object is detected, reset the flag and time
    is_object_detected = false;
    last_detected_time = 0;
  }

  // If an object has been continuously detected for 30 seconds, turn on the LED for 5 seconds
  if (is_object_detected && (millis() - last_detected_time) >= 30000) {
    digitalWrite(ledPin, HIGH);
    delay(5000);  // Wait for 5 seconds
    digitalWrite(ledPin, LOW);
    is_object_detected = false;
    last_detected_time = 0;
  }

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  // Send distance to ThingSpeak
  if (millis() - lastConnectionTime >= updateInterval) {
    lastConnectionTime = millis();
    ThingSpeak.writeField(channelID, 1, distance, writeAPIKey);
  }

  delay(500);   // Wait for 500ms before measuring again
}
