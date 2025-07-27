#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// NodeMCU pin connected to soil moisture sensor
const int soilSensorPin = A0;

// LCD module address
const int lcdAddress = 0x27;

LiquidCrystal_I2C lcd(lcdAddress, 16, 2);  // Initialize the LCD

void setup() {
  Serial.begin(9600);
  lcd.backlight();
  lcd.init();
  lcd.begin(16, 2);  // Initialize the LCD columns and rows
  pinMode(soilSensorPin, INPUT);
}

void loop() {
  // Read the soil moisture value
  int moistureValue = analogRead(soilSensorPin);

  // Invert the moisture value to represent moisture content
  int moistureContent = map(moistureValue, 500, 1024, 100, 0);

  // Determine the soil condition based on moisture value
  String soilCondition;
  if (moistureValue < 700) {
    soilCondition = "Wet";
  } else if ((moistureValue > 659)&&(moistureValue < 950)) {
    soilCondition = "Moist";
  } else if (moistureValue > 949) {
    soilCondition = "Dry";
  }
  //else{soilCondition = ".....";}

  // Print the moisture value and soil condition to the serial monitor
  Serial.print("Moisture value: ");
  Serial.print(moistureValue);
  Serial.print("\tMoisture content: ");
  Serial.print(moistureContent);
  Serial.print("%\tSoil condition: ");
  Serial.println(soilCondition);

  // Display the moisture content and soil condition on the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Moisture: ");
  lcd.print(moistureContent);
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("Condition: ");
  lcd.print(soilCondition);

  delay(1000); // Delay for 1 second
}
