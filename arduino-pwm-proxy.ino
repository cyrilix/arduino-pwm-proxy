
//#include "CurieTimerOne.h"
#include <SimpleTimer.h>
// the timer object
SimpleTimer timer;

#define  PWM_RC_STEERING_PIN 11
#define  PWM_RC_THROTTLE_PIN 5
 
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
  Serial1.begin(115200);
  attachInterrupt(PWM_RC_THROTTLE_PIN, throttle_rising, RISING);
  attachInterrupt(PWM_RC_STEERING_PIN, steering_rising, RISING);
  timer.setInterval(50, timedCheckOutput);
  //CurieTimerOne.start(OUTPUTLOOP, &timedCheckOutput);  // set timer and callback

}
 
void loop() {
   timer.run();
}

void timedCheckOutput()
{
  boolean validData = false;
  if ((throttle_toggle == 0) || (steering_toggle == 0)) {
    sprintf(buff, "-1,-1,-1");
    validData=true;
  } else {
    if (pwm_steering_value > 900 && 
        pwm_steering_value < 2100 &&
        pwm_throttle_value > 900 && 
        pwm_throttle_value < 2200) {
          sprintf(buff, "%d,%d,%d", pwm_steering_value, pwm_throttle_value, freq_value);    
          validData=true;
        }
  }

  if (validData) {
    Serial.println(buff);    
    Serial1.println(buff);    
  }
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


