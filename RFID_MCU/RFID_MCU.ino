#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
//#define TXp2 17

#define RST_PIN 9 // Define the reset pin for the RC522 RFID module
#define SS_PIN 10 // Define the SS (Slave Select) pin for the RC522 RFID module

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create an instance of the MFRC522 RFID module

void setup() {
  Serial.begin(9600); // Start the serial communication
  SPI.begin(); // Start the SPI communication
  mfrc522.PCD_Init(); // Initialize the MFRC522 RFID module
  Serial.println("Ready to read RFID tags...");
}

void loop() {
 // Look for new cards
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
  
    String uid = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      uid.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
      uid.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    uid.toUpperCase();
    Serial.println(uid);

    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
  }
}
