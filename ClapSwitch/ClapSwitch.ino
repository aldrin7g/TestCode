const int clapSensor = 8;  // Pin for LM393 microphone sensor
const int ledPin = 12;  // Pin for the LED
bool ledState = false;  // Variable to store LED state
unsigned long clapTime = 0;  // Variable to store time of last clap
unsigned long clapInterval = 800;  // Interval between two claps to turn off LED

void setup() {
  pinMode(clapSensor, INPUT);  // Set microphone sensor as input
  pinMode(ledPin, OUTPUT);  // Set LED as output
}

void loop() {
  if (digitalRead(clapSensor) == HIGH) {  // Check if sound is detected
    unsigned long currentTime = millis();  // Get current time
    if (currentTime - clapTime < clapInterval) {  // Check if two claps are detected within clapInterval
      ledState = false;  // Turn off LED
    } else {
      ledState = true;  // Turn on LED
    }
    digitalWrite(ledPin, ledState);  // Update LED state
    clapTime = currentTime;  // Update clap time
    delay(100);  // Wait for 100 milliseconds
  }
}
