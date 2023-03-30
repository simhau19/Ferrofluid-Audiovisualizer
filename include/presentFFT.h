#include <Arduino.h>
#include "arduinoFFT.h"
#include "ADCFast.h"

#pragma once

#define PIN_COUNT 6
#define SAMPLES 512

class presentFFT{

private:

    const int samples = SAMPLES;
    const int sampleFrq;
    const int amplitude = 1000;
    const int noise = 500;
    const int pinCount = PIN_COUNT;
    uint16_t adc_buffer[SAMPLES];
    ADCFast adc;

public:

    presentFFT(const int sf, uint8_t pin0, uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4, uint8_t pin5);


    int getSamples() {return samples;}
    int getSampleFrq() {return sampleFrq;}
    int getAmplitude() {return amplitude;}
    int getNoise() {return noise;}
    int getPinCount() {return pinCount;}
    ADCFast getAdc() {return adc;}
    uint16_t getBufferAt(int i) {return adc_buffer[i];}

    const uint8_t frqPins[PIN_COUNT];
    int bandValues[PIN_COUNT];
    int analogValues[PIN_COUNT];
    
    int sumBandValue = 0;

    double vReal[SAMPLES];
    double vImag[SAMPLES];
    

    arduinoFFT FFT = arduinoFFT(vReal, vImag, samples, sampleFrq);

    void setup();
    void collectSampleData();
    void fftMagic();
    void makeFrqBands();
    void createAnalogueValues();
    void sendAnalogueValues();
    void resetValues();
};