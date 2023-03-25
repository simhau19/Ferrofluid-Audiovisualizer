#include <Arduino.h>
#include "arduinoFFT.h"
#include "fft.h"
#include "ADCFast.h"


#define TFT_MOSI            19
#define TFT_SCLK            18
#define TFT_CS              5
#define TFT_DC              16
#define TFT_RST             23

#define PWM_FREQ 10000
#define PWM_RESOLUTION 12

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
int maksVerdier[pinCount];
int sumBandVerdi = 0;

double vReal[samples];
double vImag[samples];

uint16_t sample_values[samples];

unsigned int samplingPeriodUs;
unsigned long new_time;

arduinoFFT FFT = arduinoFFT(vReal, vImag, samples, sampleFrq);

ADCFast adc(ADC1_CHANNEL_0, sampleFrq, sample_values, sizeof(sample_values));


void fftSetup()
{
Serial.begin(115200);
samplingPeriodUs = round(1000000 * (1.0/sampleFrq));

pinMode(lydInnPin, INPUT);

// for (int i = 0; i < pinCount; i++){
//     pinMode(frekPins[i], OUTPUT);

// }

ledcSetup(0, PWM_FREQ, PWM_RESOLUTION);
ledcAttachPin(32, 0);
adc.init();
}

void fftLoop()
{
//display.fillScreen(TFT_BLACK);
sumBandVerdi = 0;

for (int i = 0; i < pinCount; i++){
    bandVerdier[i] = 0;
    analogValues[i] = 0;
}

//Sampler input-pin
adc.read();
for (int i = 0; i < samples; i++){
    vImag[i] = 0;
    vReal[i] = sample_values[i];
}


//Utfører FFT (magi)
FFT.DCRemoval(); //Fjerner likespenningskomponent
FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
FFT.Compute(FFT_FORWARD);
FFT.ComplexToMagnitude();

//fordeler verdier i frekvensbånd
for (int i = 1; i < (samples/2); i ++){
    if (vReal[i] > 500){
        if (i <= 4){ bandVerdier[0] += vReal[i];}
        if (i > 4 && i <= 10){ bandVerdier[1] += vReal[i];}
        if (i > 10 && i <= 28){ bandVerdier[2] += vReal[i];}
        if (i > 28 && i <= 77){ bandVerdier[3] += vReal[i];}
        if (i > 77 && i <= 200){ bandVerdier[4] += vReal[i];}
        if (i > 200 && i <= 400){ bandVerdier[5] += vReal[i];}


    }
}


// for (int i = 0; i < pinCount; i++){
//     uint32_t height = bandVerdier[0]*128/50000;
//     height = i*20;
//     if(height > 128) {height = 128;}
//     display.fillRect(i*160/pinCount, 0, 160/pinCount, height, TFT_RED);
// }


//Serial.print(sumBandVerdi);

for (int i = 0; i < pinCount - 1; i++){
    sumBandVerdi += bandVerdier[i];
    if(maksVerdier[i] < bandVerdier[i]) {maksVerdier[i] = bandVerdier[i];}
}

//Serial.println(sumBandVerdi);


// for (int i = 0; i < pinCount; i++){
//     if (sumBandVerdi != 0){
//         analogValues[i] = ((bandVerdier[i]*255)/sumBandVerdi);
//     }
// }

/*
for (int i = 0; i < pinCount; i++){
    Serial.println(bandVerdier[i]);
}
Serial.println();
Serial.println(analogValues[3]);
Serial.println();*/

Serial.print(sumBandVerdi);
for (int i = 0; i < pinCount; i++){
    Serial.print(", ");
    Serial.print(maksVerdier[i]);
    
    
}
Serial.println();

uint16_t pwm_duty = (float)sumBandVerdi*4096/500000;
if(pwm_duty > 4095){pwm_duty = 4095;} 

dacWrite(25, pwm_duty/16);


// analogWrite(frekPins[0], analogValues[0]);
// analogWrite(frekPins[1], analogValues[1]);
// analogWrite(frekPins[2], analogValues[2]);
// analogWrite(frekPins[3], analogValues[3]);
// analogWrite(frekPins[4], analogValues[4]);
// analogWrite(frekPins[5], analogValues[5]);




}