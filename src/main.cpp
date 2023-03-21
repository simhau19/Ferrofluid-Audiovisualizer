#include <Arduino.h>
#include "arduinoFFT.h"
#include "sample_periode.h"
#include "fft.h"
#include "ADCFast.h"


uint16_t adc_buffer[1024];
ADCFast adc(ADC1_CHANNEL_0, 44100, adc_buffer, sizeof(adc_buffer));

void setup()
{
  Serial.begin(115200);
  Serial.println("Setup");
  adc.init();
}

void loop()
{
  const int sample_size = 1024;
  //Serial.println("Start sampling");
  
  unsigned long last_micros = micros();
  uint32_t read = adc.read();
  float sampling_time = ((float) micros() - last_micros);

  for (int i = 0; i < 1024; i++)
  {
    Serial.print("V: ");
    Serial.println(adc_buffer[i]);
  }
  
  
  delay(1000);
}

