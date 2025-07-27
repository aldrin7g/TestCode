#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN D8
#define RST_PIN D4

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("RFID Reader ready!");
}

void loop() {
  // Look for new cards
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    // Show some details of the card
    Serial.print("UID tag :");
    String content= "";
    byte letter;
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
      content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
      content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    Serial.println();
    Serial.print("Message : ");
    content.toUpperCase();
    if ((content.substring(1) == "DD 65 FF 30") || (content.substring(1) == "75 35 AB AC") || (content.substring(1) == "2D 88 9A 67") || (content.substring(1) == "2D A7 75 66") ) { // change XX XX XX XX with the UID of your card
      Serial.println("Authorized access");
      // add code here to perform an authorized action
    }
    else {
      Serial.println("Access denied");
    }
  }
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}
