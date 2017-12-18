
#include "CurieTimerOne.h"

#define  PWM_RC_STEERING_PIN 5
#define  PWM_RC_THROTTLE_PIN 11
 
unsigned int pwm_throttle_value = 0;
unsigned int pwm_steering_value = 0;
unsigned int freq_value = 0;
unsigned int prev_throttle_time = 0;
unsigned int prev_steering_time = 0;
unsigned int prev_freq_time = 0;

int throttle_toggle = 0;
int steering_toggle = 0;
 
char buff [50] = {};

//Each 50ms, check and output value to serial link
#define OUTPUTLOOP 50000

void setup() {

  Serial.begin(115200);
  attachInterrupt(PWM_RC_THROTTLE_PIN, throttle_rising, RISING);
  attachInterrupt(PWM_RC_STEERING_PIN, steering_rising, RISING);
  CurieTimerOne.start(OUTPUTLOOP, &timedCheckOutput);  // set timer and callback

}
 
void loop() {

}

void timedCheckOutput()
{
  if ((throttle_toggle == 0) || (steering_toggle == 0)) {
    sprintf(buff, "-1,-1,-1");
  } else {
    sprintf(buff, "%d,%d,%d", pwm_throttle_value, pwm_steering_value, freq_value);
  }
 
  Serial.println(buff);
  throttle_toggle = 0;
  steering_toggle = 0;  
}

void throttle_rising() {
  attachInterrupt(PWM_RC_THROTTLE_PIN, throttle_falling, FALLING);
  prev_throttle_time = micros();
  throttle_toggle ++;
}

void steering_rising() {
  attachInterrupt(PWM_RC_STEERING_PIN, steering_falling, FALLING);
  prev_steering_time = micros();
  steering_toggle ++;
}

void throttle_falling() {
  attachInterrupt(PWM_RC_THROTTLE_PIN, throttle_rising, RISING);
  pwm_throttle_value = micros()-prev_throttle_time;
  freq_value = 1000000 / (micros()-prev_freq_time); 
  prev_freq_time = micros();
  throttle_toggle ++;
}

void steering_falling() {
  attachInterrupt(PWM_RC_STEERING_PIN, steering_rising, RISING);
  pwm_steering_value = micros()-prev_steering_time;
  steering_toggle ++;
}


