
#define PWM_FREQ 10000
#define PWM_RESOLUTION 12

//renaming ledcWrite function
#define pwm_write(x, y) ledcWrite(x,y) 