#include "adc_fast.h""



void ADC1::init(){
    adc1_config_channel_atten(channel, ADC_ATTEN_11db);
    adc1_config_width(ADC_WIDTH_12Bit);
}

uint16_t ADC1::read(){
    int adc_value;
    adc1_get_raw(channel);
    return adc_value;
}

void ADC2::init(){
    adc2_config_channel_atten(channel, ADC_ATTEN_11db);
}

uint16_t ADC2::read(){
    int adc_value;
    adc2_get_raw(channel, ADC_WIDTH_12Bit, &adc_value);
    return adc_value;
}


