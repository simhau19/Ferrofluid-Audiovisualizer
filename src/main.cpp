#include <Arduino.h>
#include "arduinoFFT.h"
#include "sample_periode.h"
#include "fft.h"

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  fftLoop();
}

