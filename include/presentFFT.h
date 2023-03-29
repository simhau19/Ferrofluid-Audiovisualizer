#include <Arduino.h>
#include "arduinoFFT.h"
#pragma once

#define PIN_COUNT 6
#define SAMPLES 1024

class presentFFT{

private:

    const int samples = SAMPLES;
    const int sampleFrq;
    const int audioInPin;
    const int amplitude;
    const int antallFrqBand;
    const int noise;
    const int pinCount = PIN_COUNT;

public:

    int frqPins[PIN_COUNT];
    int bandValues[PIN_COUNT];
    int analogValues[PIN_COUNT];
    
    int sumBandValue = 0;
    unsigned int samplingPeriodUs;
    unsigned int newTime;

    double vReal[SAMPLES];
    double vImag[SAMPLES];

    arduinoFFT FFT = arduinoFFT(vReal, vImag, samples, sampleFrq);

    void setup();
    void collectSampleData();
    void fftMagic();
    void makeFrqBands();
    void createAnalogueValues();
    void sendAnalogueValues();
};