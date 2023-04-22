#include <Arduino.h>
#include "arduinoFFT.h"
#include "sampleTest.h"
#include "fft.h"
#include "ADCFast.h"
#include "presentFFT.h"


presentFFT test(40000, 19, 14, 13, 18, 12, 4);

int var = 5;
bool sw = 0;
int counter = 0;



void setup()
{
  test.setup();

}

void loop()
{ 

  if (sw == 0){
    test.drag(var);
    Serial.println(var);

    if (var == 255){
      sw = 1;
      var = 150;
    }
  }

  else if (sw = 1){
    test.run();
  }  
  
}

