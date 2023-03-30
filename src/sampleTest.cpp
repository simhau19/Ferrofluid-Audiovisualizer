#include <Arduino.h>
#include "arduinoFFT.h"
#include "sampleTest.h"
#include "ADCFast.h"


#define AUDIO_IN_PIN 35

  int analogValue;
  unsigned long newTime;

  uint16_t adc_buffer[512];
  ADCFast adc(ADC1_CHANNEL_5, 44100, adc_buffer, sizeof(adc_buffer));
  float vReal1[512];

void testSetup() {
  Serial.begin(115200);

  adc.init();

}

void testLoop() {

  adc.read();

  // Do 1 million reads and record time taken
  for (int i = 0; i < 512; i++) {
    vReal1[i] = adc_buffer[i];
  }

  float conversionTime = (micros() - newTime) / 1000000.0;

  Serial.print("Conversion time: ");
  Serial.print(conversionTime);
  Serial.println(" uS");

  Serial.print("Max sampling frequency: ");
  Serial.print((1.0 / conversionTime) * 1000000);
  Serial.println(" Hz");
}


