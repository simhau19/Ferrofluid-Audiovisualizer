#pragma once
#include "driver/i2s.h"

class ADCFast{
    private:
        i2s_port_t i2s_port = I2S_NUM_0;
        uint32_t adc_sample_rate;
        adc1_channel_t adc_channel;
        uint16_t* buff;
        const size_t buff_size;

    public:
        ADCFast(adc1_channel_t channel, uint32_t sample_rate, uint16_t* adc_buffer, size_t adc_buffer_size):
            adc_channel{channel},
            adc_sample_rate{sample_rate},
            buff{adc_buffer},
            buff_size{adc_buffer_size}
            {}

        void init();
        uint32_t read();
}; 