#include <Arduino.h>
#include "arduinoFFT.h"
#include "fft.h"

const int samples = 1024;
const int sampleFrq = 40000;
const int lydInnPin = 13;
const int amplitude = 1000;
const int antallFrekBand = 6;
const int noise = 500;

// Frekvensbånd til Pin
const uint8_t frekPins[] = {27, 26, 25, 33, 32, 36};
int analogValues[] = {0, 0, 0, 0, 0, 0};
const int pinCount = 6;

int bandVerdier[] = {0, 0, 0, 0, 0, 0};
int sumBandVerdi = 0;

double vReal[samples];
double vImag[samples];

unsigned int samplingPeriodUs;
unsigned long new_time;

arduinoFFT FFT = arduinoFFT(vReal, vImag, samples, sampleFrq);


void fftSetup()
{
Serial.begin(115200);
samplingPeriodUs = round(1000000 * (1.0/sampleFrq));

pinMode(lydInnPin, INPUT);

for (int i = 0; i < pinCount; i++){
    pinMode(frekPins[i], OUTPUT);

}
}

void fftLoop()
{
sumBandVerdi = 0;

for (int i = 0; i < pinCount; i++){
    bandVerdier[i] = 0;
    analogValues[i] = 0;
}

//Sampler input-pin
for (int i = 0; i < samples; i++){
    new_time = micros();
    vReal[i] = analogRead(lydInnPin);
    vImag[i] = 0;
    while((micros() - new_time) < samplingPeriodUs) {/*venter*/}
}



//Utfører FFT (magi)
FFT.DCRemoval(); //Fjerner likespenningskomponent
FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
FFT.Compute(FFT_FORWARD);
FFT.ComplexToMagnitude();

//fordeler verdier i frekvensbånd
for (int i = 2; i < (samples/2); i ++){
    if (vReal[i] > 500){
        if (i <= 4){ bandVerdier[0] += vReal[i];}
        if (i > 4 && i <= 10){ bandVerdier[1] += vReal[i];}
        if (i > 10 && i <= 28){ bandVerdier[2] += vReal[i];}
        if (i > 28 && i <= 77){ bandVerdier[3] += vReal[i];}
        if (i > 77 && i <= 210){ bandVerdier[4] += vReal[i];}
        if (i > 210 && i <= 572){ bandVerdier[5] += vReal[i];}


    }
}
/*
for (int i = 0; i < pinCount; i++){
    Serial.println(bandVerdier[i]);
}
*/

//Serial.print(sumBandVerdi);

for (int i = 0; i < pinCount; i++){
    sumBandVerdi += bandVerdier[i];
}

//Serial.println(sumBandVerdi);


for (int i = 0; i < pinCount; i++){
    if (sumBandVerdi != 0){
        analogValues[i] = ((bandVerdier[i]*255)/sumBandVerdi);
    }
}

/*
for (int i = 0; i < pinCount; i++){
    Serial.println(bandVerdier[i]);
}
Serial.println();
Serial.println(analogValues[3]);
Serial.println();

*/
for (int i = 0; i < pinCount; i++){
    Serial.println(analogValues[i]);
}



analogWrite(frekPins[0], analogValues[0]);
analogWrite(frekPins[1], analogValues[1]);
analogWrite(frekPins[2], analogValues[2]);
analogWrite(frekPins[3], analogValues[3]);
analogWrite(frekPins[4], analogValues[4]);
analogWrite(frekPins[5], analogValues[5]);


}