#include "ADCFast.h"
#include "Arduino.h"



void ADCFast::init(){
    i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX | I2S_MODE_ADC_BUILT_IN),
    .sample_rate =  adc_sample_rate,              // The format of the signal using ADC_BUILT_IN
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT, // is fixed at 12bit, stereo, MSB
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_STAND_I2S,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 8,
    .dma_buf_len = 1024,
    .use_apll = false,
    .tx_desc_auto_clear = false,
    .fixed_mclk = 0
  };

  if(i2s_driver_install(i2s_port, &i2s_config, 0, NULL) != ESP_OK){
    Serial.println("Error installing i2s driver");
  }

  if(i2s_set_adc_mode(ADC_UNIT_1, adc_channel) != ESP_OK){
    Serial.println("Error setting adc mode");
  }

  if(adc1_config_channel_atten(adc_channel, ADC_ATTEN_11db) != ESP_OK){
    Serial.println("Error setting adc attenuation");
  }

  Serial.println("I2S setup complete");

}

uint32_t ADCFast::read(){
    
    uint32_t bytes_read;
    i2s_adc_enable(i2s_port);
    if(i2s_read(i2s_port, buff, buff_size, &bytes_read, portMAX_DELAY) != ESP_OK){
        Serial.println("Error sampling adc");
    };
    i2s_adc_disable(i2s_port);
    
    return bytes_read;
}
