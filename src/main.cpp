#include <Arduino.h>
#include "arduinoFFT.h"
#include "sample_periode.h"
#include "fft.h"
#include "ADCSampler.h"
#include "adc.h"

ADC2 adc(ADC2_CHANNEL_0);

void setup()
{
  Serial.begin(115200);
  Serial.println("Setup");
  adc.init();
}

void loop()
{
  // const int sample_size = 1000;
  // Serial.println("Start sampling");
  
  // unsigned long last_micros = micros();
  // for (int i = 0; i < sample_size; i++)
  // {
  //   adc.read();
  // }
  
  // float sampling_time = ((float) micros() - last_micros)/sample_size;
  // Serial.println(sampling_time);
  Serial.print("CPU: ");
  Serial.print(getCpuFrequencyMhz());
  Serial.print("MHz\nXTAL: ");
  Serial.print(getXtalFrequencyMhz());
  Serial.print("MHz\nAPB: ");
  Serial.println(getApbFrequency());

  delay(1000);
}

