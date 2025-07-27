// Define the sensor's input pin
const int sensorPin = 2;

// Define the LED and buzzer pins
const int ledPin = 13;
const int buzzerPin = 4;

void setup() {
  // Initialize the LED and buzzer pins as output pins
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  
  // Set the sensor pin as an input pin
  pinMode(sensorPin, INPUT);
  
  // Initialize the serial communication
  Serial.begin(9600);
}

void loop() {
  // Read the sensor's digital output from the input pin
  int sensorValue = digitalRead(sensorPin);
  
  // Convert the digital value to a raindrop level using the sensor's datasheet
  // Example conversion: If the value is LOW, it means there is a raindrop detected
  int raindropLevel = sensorValue == LOW ? 1 : 0;
  
  // If rain is detected, light up the LED and activate the buzzer
  if (raindropLevel == 1) {
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    Serial.println("Rain detected!");
  }
  else {
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);
  }
  
  // Wait for some time before reading again
  delay(1000);
}
