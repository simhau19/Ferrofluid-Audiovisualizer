#include <Arduino.h>
#include "arduinoFFT.h"
#include "sample_periode.h"
#include "fft.h"
#include "ADCSampler.h"

i2s_config_t adcI2SConfig = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX | I2S_MODE_ADC_BUILT_IN),
    .sample_rate = 20000,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_STAND_I2S,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 4,
    .dma_buf_len = 1024,
    .use_apll = false,
    .tx_desc_auto_clear = false,
    .fixed_mclk = 0};

ADCSampler adc(ADC_UNIT_1, ADC1_CHANNEL_0, adcI2SConfig);

void setup()
{
  Serial.begin(115200);
  Serial.println("Setup");
  adc.start();
}

void loop()
{
  const int sample_size = 1000;
  int16_t samples[sample_size];

  Serial.println("Start sampling");
  
  unsigned long last_micros = micros();
  adc.read(samples, sample_size);
  float sampling_time = ((float) micros() - last_micros) / (sample_size);

  Serial.println(sampling_time);

  delay(1000);
}

