#include <Arduino.h>
#include "arduinoFFT.h"
#include "sampleTest.h"
#include "fft.h"
#include "ADCFast.h"
#include "presentFFT.h"


presentFFT test(40000, 13, 12, 14, 27, 26, 25);

void setup()
{
  test.setup();

}

void loop()
{ 

  test.resetValues();
  test.collectSampleData();
  test.fftMagic();
  test.makeFrqBands();
  test.createAnalogueValues();
  test.sendAnalogueValues();

}

