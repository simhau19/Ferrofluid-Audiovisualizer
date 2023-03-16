//Code for generating pwm signals to control the strength of the electromagnets

#include "Arduino.h"
#include "pwm.h"
uint8_t pwm_pins[] = {12,14,27,26,25,33,32};

void pwm_init(){
    uint8_t electromagnet_count = sizeof(pwm_pins)/sizeof(pwm_pins[0]);
    for (uint8_t i = 0; i < electromagnet_count; i++){
        ledcSetup(i, PWM_FREQ, PWM_RESOLUTION);
        ledcAttachPin(pwm_pins[i], i);
    }
}


