int sensorPin = A0; // analog input pin for MQ-135 sensor
int thresholdCO2 = 1000; // threshold value for CO2 concentration
int thresholdSmoke = 500; // threshold value for smoke concentration
int thresholdNH3 = 100; // threshold value for ammonia concentration

void setup() {
  Serial.begin(9600); // initialize serial communication
}

void loop() {
  int sensorValue = analogRead(sensorPin); // read sensor value from A0 pin

  // calculate concentration of CO2 in ppm
  float concentrationCO2 = sensorValue * (5000.0 / 1023.0) / 5.0 * 1000.0;

  // calculate concentration of smoke in ppm
  float concentrationSmoke = sensorValue * (5000.0 / 1023.0) / 5.0 * 200.0;

  // calculate concentration of ammonia in ppm
  float concentrationNH3 = sensorValue * (5000.0 / 1023.0) / 5.0 * 100.0;

  // print concentration values to serial monitor
  Serial.print("CO2: ");
  Serial.print(concentrationCO2);
  Serial.print(" ppm, Smoke: ");
  Serial.print(concentrationSmoke);
  Serial.print(" ppm, Ammonia: ");
  Serial.print(concentrationNH3);
  Serial.println(" ppm");

  // assign rating based on concentration values
  int rating = 10;
  if (concentrationCO2 > thresholdCO2) {
    rating = min(rating, 8); // assign rating 8 if CO2 concentration exceeds threshold
  }
  if (concentrationSmoke > thresholdSmoke) {
    rating = min(rating, 6); // assign rating 6 if smoke concentration exceeds threshold
  }
  if (concentrationNH3 > thresholdNH3) {
    rating = min(rating, 7); // assign rating 7 if ammonia concentration exceeds threshold
  }

  // print air quality rating to serial monitor
  Serial.print("Air quality rating: ");
  Serial.println(rating);

  delay(1000); // wait for 1 second before reading again
}
