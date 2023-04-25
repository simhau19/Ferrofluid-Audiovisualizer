#include "presentFFT.h"


presentFFT::presentFFT(const int sf, uint8_t pin0, uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4, uint8_t pin5):
    sampleFrq{sf},
    adc{ADCFast(ADC1_CHANNEL_6, sf, adc_buffer, sizeof(adc_buffer))},
    frqPins{pin0, pin1, pin2, pin3, pin4, pin5} {
    
    for (int i = 0; i < pinCount; i++){
        bandValues[i], analogValues[i] = 0;
    }
}


void presentFFT::setup(){
    Serial.begin(115200);

    adc.init();

    for (int i = 0; i < pinCount; i++){
        pinMode(frqPins[i], OUTPUT);
    }
}

void presentFFT::collectSampleData(){

    adc.read();

    for (int i = 0; i < samples; i++){

        vReal[i] = adc_buffer[i];
        vImag[i] = 0;
    }
}

void presentFFT::fftMagic(){
    FFT.DCRemoval(); //Fjerner likespenningskomponent
    FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(FFT_FORWARD);
    FFT.ComplexToMagnitude();
}

void presentFFT::makeFrqBandsOG(){
    for (int i = 0; i < (samples/2); i ++){
        if (vReal[i] > 1000){
            if (i <= 0){ bandValues[0] += vReal[i];}
            if (i > 2 && i <= 5){ bandValues[1] += vReal[i];}
            if (i > 5 && i <= 13){ bandValues[2] += vReal[i];}
            if (i > 13 && i <= 34){ bandValues[3] += vReal[i];}
            if (i > 34 && i <= 88){ bandValues[4] += vReal[i];}
            if (i > 88 && i <= 232){ bandValues[5] += vReal[i];}

        }
    }
}

void presentFFT::makeFrqBandsHalf(){
    for (int i = 2; i < (samples/2); i ++){
        if (vReal[i] > 1000){
            if (i <= 2){ bandValues[0] += vReal[i];}
            if (i > 2 && i <= 4){ bandValues[1] += vReal[i];}
            if (i > 6 && i <= 11){ bandValues[2] += vReal[i];}
            if (i > 17 && i <= 30){ bandValues[3] += vReal[i];}
            if (i > 48 && i <= 81){ bandValues[4] += vReal[i];}
            if (i > 130 && i <= 237){ bandValues[5] += vReal[i];}

        }
    }
}


void presentFFT::createanalogValues1(){

    for (int j = 0; j < pinCount; j++){
        sumBandValue += bandValues[j];
    }


    for (int k = 0; k < pinCount; k++){
        if (sumBandValue != 0){
            analogValues[k] = (255*bandValues[k])/sumBandValue;
        }
    }
}

void presentFFT::createanalogValues2(){

    int divider;
    for (int k = 0; k < pinCount; k++){
        if (k == 0){
            divider = 20000;
        }
        else{
            divider = 30000;
        }

        if (bandValues[k] < divider){
            analogValues[k] = (255*bandValues[k])/divider;
        }
        else{
            analogValues[k] = 255;
        }
    }
}

void presentFFT::createanalogValues3(){


    for (int k = 0; k < pinCount; k++){
        if ((bandValues[k] * 0.9) <= prevBandValues[k] < (bandValues[k] * 1.1) && (prevBandValues[k] != 0) && (bandValues[k] != 0)){
            analogValues [k] = prevAnalogValues[k];
        }

        else if (bandValues[k] < 30000){
            analogValues[k] = (255*bandValues[k])/30000;
        }
        else{
            analogValues[k] = 255;
        }

    }
}



void presentFFT::sendanalogValues(){
    for (int i = 0; i < pinCount; i++){
        analogWrite(frqPins[i], analogValues[i]);
    }
}

void presentFFT::resetValues(){

for (int i = 0; i < pinCount; i++){
    prevBandValues[i] = bandValues[i];
    prevAnalogValues[i] = analogValues[i];
    bandValues[i] = 0;
    analogValues[i] = 0;
    }
}

void presentFFT::printValues(){
    for (int i = 0; i < pinCount; i++){

        
        Serial.print("Bandvalues ");
        Serial.print(i);
        Serial.print(": ");
        Serial.println(bandValues[i]);
        

        Serial.print("Analogvalues");
        Serial.print(i);
        Serial.print(": ");
        Serial.println(analogValues[i]);
        Serial.println(sumBandValue);
        Serial.println("\n");

    }
}

void presentFFT::plotValues(){
    Serial.print("Bandvalue ");
    Serial.print("0: ");
    Serial.println(bandValues[0]);
    Serial.println("\n");
}

void presentFFT::run(){

  resetValues();
  collectSampleData();
  fftMagic();
  makeFrqBandsOG();
  createanalogValues2();
  sendanalogValues();

}

void presentFFT::drag(int &x){
    analogWrite(33, x);
    x += 5;
    delay(200);
}
