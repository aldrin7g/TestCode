#include "AudioGeneratorAAC.h"
#include "AudioOutputI2S.h"
#include "AudioFileSourcePROGMEM.h"
#include "sampleaac.h"

#define Bit_Clock_BCLK 27
#define Word_Select_WS 26
#define Serial_Data_SD 25

AudioFileSourcePROGMEM *in = nullptr;
AudioGeneratorAAC *aac = nullptr;
AudioOutputI2S *out = nullptr;

void setup() {
  Serial.begin(115200);
  in = new AudioFileSourcePROGMEM(sampleaac, sizeof(sampleaac));
  aac = new AudioGeneratorAAC();
  out = new AudioOutputI2S();
  out->SetGain(0.5); // Set an initial gain value
  out->SetPinout(Bit_Clock_BCLK, Word_Select_WS, Serial_Data_SD);
  aac->begin(in, out);
}

void loop() {
  if (aac->isRunning()) {
    aac->loop();
  } else {
    aac->stop();
    Serial.println("\nSound Generator");
    delay(1000);
    
    // Ask the user if they want to repeat the music
    Serial.print("Do you want to repeat the music? (y/n): ");
    while (!Serial.available()) {} // Wait for user input
    char repeatChoice = Serial.read();
    Serial.println(repeatChoice);
    char err = Serial.read();
    if (repeatChoice == 'y' || repeatChoice == 'Y') {
      // Deallocate memory and reset pointers
      delete in;
      delete aac;
      delete out;
      in = nullptr;
      aac = nullptr;
      out = nullptr;
      
      // Reinitialize audio objects
      in = new AudioFileSourcePROGMEM(sampleaac, sizeof(sampleaac));
      aac = new AudioGeneratorAAC();
      out = new AudioOutputI2S();
      out->SetGain(0.5); // Set an initial gain value
      out->SetPinout(Bit_Clock_BCLK, Word_Select_WS, Serial_Data_SD);
      aac->begin(in, out);
    }
    
    // Ask the user for the gain value
    float newGain = 0.0;
    Serial.print("Enter a new gain value (0.0 - 1.0): ");
    while (!Serial.available()) {} // Wait for user input
    newGain = Serial.parseFloat();
    Serial.println(newGain);
    err = Serial.read();
    if (newGain >= 0.0 && newGain <= 1.0) {
      out->SetGain(newGain); // Set the new gain value
    } else {
      Serial.println("Invalid gain value.");
    }
  }
}
