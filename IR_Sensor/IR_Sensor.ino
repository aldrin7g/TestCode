const int irSensorPin = 2;   // Pin where the IR sensor is connected
int sensorValue = 0;          // variable to store the value read from the sensor
const int ledPin =11;
void setup() {
  Serial.begin(9600);         // initialize serial communication at 9600 bits per second
  pinMode(irSensorPin, INPUT);
  pinMode(ledPin, OUTPUT); 
}

void loop() {
  sensorValue = digitalRead(irSensorPin);  // read the value from the sensor
  if (sensorValue == 1) {
    Serial.println("No Object detected");
    digitalWrite(ledPin,LOW);
    delay(1000);
  } else {
    Serial.println("object detected");
    digitalWrite(ledPin,HIGH);
    delay(1000);
  }
  delay(100);                    // wait for 100 milliseconds
}
