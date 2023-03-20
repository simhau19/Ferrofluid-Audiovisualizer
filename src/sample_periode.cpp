#include <Arduino.h>
#include "arduinoFFT.h"
#include "sample_periode.h"


#define AUDIO_IN_PIN 04

int analogValue;
unsigned long newTime;

void testSetup() {
  Serial.begin(115200);
}

void testLoop() {
  newTime = micros();
  
  // Do 1 million reads and record time taken
  for (int i = 0; i < 1000; i++) {
    analogValue = analogRead(AUDIO_IN_PIN);
  }

  float conversionTime = (micros() - newTime) / 1000.0;

  Serial.print("Conversion time: ");
  Serial.print(conversionTime);
  Serial.println(" uS");

  Serial.print("Max sampling frequency: ");
  Serial.print((1.0 / conversionTime) * 1000000);
  Serial.println(" Hz");
}
