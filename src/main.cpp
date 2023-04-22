#include <Arduino.h>
#include "arduinoFFT.h"
#include "sampleTest.h"
#include "fft.h"
#include "ADCFast.h"
#include "presentFFT.h"


presentFFT test(40000, 19, 14, 13, 18, 12, 4);

void setup()
{
  test.setup();

}

void loop()
{ 

  test.run();
}

