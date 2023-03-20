#pragma once
#include "driver/adc.h"

class ADC1{
    private:
        adc_unit_t unit = ADC_UNIT_1;
        adc1_channel_t channel;

    public:
        ADC1(adc1_channel_t channel):
            channel{channel}{}

        void init();
        uint16_t read();
};

class ADC2{
    private:
        adc_unit_t unit = ADC_UNIT_1;
        adc2_channel_t channel;

    public:
        ADC2(adc2_channel_t channel):
            channel{channel}{}

        void init();
        uint16_t read();
};