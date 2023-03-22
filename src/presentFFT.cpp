#include "presentFFT.h"

void presentFFT::setup(){
    Serial.begin(115200);

    samplingPeriodUs = round(1000000 * (1.0/sampleFrq));
    pinMode(audioInPin, INPUT);

    for (int i = 0; i < pinCount; i++){
    pinMode(frqPins[i], OUTPUT);
    }
}

void presentFFT::collectSampleData(){

    for (int i = 0; i < samples; i++){
    newTime = micros();
    vReal[i] = analogRead(audioInPin);
    vImag[i] = 0;
    while((micros() - newTime) < samplingPeriodUs) {/*waits*/}
    }
}

void presentFFT::fftMagic(){
    FFT.DCRemoval(); //Fjerner likespenningskomponent
    FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(FFT_FORWARD);
    FFT.ComplexToMagnitude();
}

void presentFFT::makeFrqBands(){
    for (int i = 2; i < (samples/2); i ++){
        if (vReal[i] > 500){
            if (i <= 4){ bandValues[0] += vReal[i];}
            if (i > 4 && i <= 10){ bandValues[1] += vReal[i];}
            if (i > 10 && i <= 28){ bandValues[2] += vReal[i];}
            if (i > 28 && i <= 77){ bandValues[3] += vReal[i];}
            if (i > 77 && i <= 210){ bandValues[4] += vReal[i];}
            if (i > 210 && i <= 572){ bandValues[5] += vReal[i];}

        }
    }
}

void presentFFT::createAnalogueValues(){
    /*
    for (int i = 0; i < pinCount; i++){
        Serial.println(bandVerdier[i]);
    }
    */

    //Serial.print(sumBandVerdi);

    for (int i = 0; i < pinCount; i++){
        sumBandValue += bandValues[i];
    }

    //Serial.println(sumBandVerdi);


    for (int i = 0; i < pinCount; i++){
        if (sumBandValue != 0){
            analogValues[i] = ((bandValues[i]*255)/sumBandValue);
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
}

void presentFFT::sendAnalogueValues(){
    for (int i = 0; i < pinCount; i++){
        analogWrite(frqPins[i], analogValues[i]);
    }
}