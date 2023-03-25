#include <Arduino.h>
#include "arduinoFFT.h"
#include "sample_periode.h"
#include "fft.h"
#include "ADCFast.h"


uint16_t adc_buffer[1024];
//ADCFast adc(ADC1_CHANNEL_0, 44100, adc_buffer, sizeof(adc_buffer));

void setup()
{
  Serial.begin(115200);
  Serial.println("Setup");
  //adc.init();
  fftSetup();
}

void loop()
{
  fftLoop();
}

