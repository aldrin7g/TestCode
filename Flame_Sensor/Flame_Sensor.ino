// Pin assignments
const int FLAME_SENSOR_PIN = 3;  // Flame sensor connected to digital pin D3
const int LED_PIN = 2;          // LED connected to digital pin D2
const int BUZZER = 4;
void setup() {
  pinMode(FLAME_SENSOR_PIN, INPUT);  // Set flame sensor pin as input
  pinMode(LED_PIN, OUTPUT);          // Set LED pin as output
  pinMode(BUZZER, OUTPUT);
  Serial.begin(9600);                // Initialize serial communication at 9600 baud rate
}

void loop() {
  int flameValue = digitalRead(FLAME_SENSOR_PIN);  // Read flame sensor value
  Serial.print("Flame sensor value: ");
  Serial.println(flameValue);                      // Print flame sensor value to serial monitor

  if (flameValue == HIGH) {    // If flame is detected
    digitalWrite(LED_PIN, HIGH);  // Turn on LED
    digitalWrite(BUZZER, LOW);
  } else {
    digitalWrite(LED_PIN, LOW);   // Turn off LED
    digitalWrite(BUZZER, HIGH);
    delay(3000);
  }
  
  delay(100);  // Delay for 100 milliseconds
}
