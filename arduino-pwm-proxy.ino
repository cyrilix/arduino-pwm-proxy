
byte PWM_RC_STEERING_PIN = 5;
byte PWM_RC_THROTTLE_PIN = 11;
  
int pwm_steering_value;
int pwm_throttle_value;
char buff [50] = {};

void setup() {
  pinMode(PWM_RC_STEERING_PIN, INPUT);
  pinMode(PWM_RC_THROTTLE_PIN, INPUT);
  Serial.begin(115200);

}
 
void loop() {
  pwm_steering_value = pulseIn(PWM_RC_STEERING_PIN, HIGH, 20000);
  pwm_throttle_value = pulseIn(PWM_RC_THROTTLE_PIN, HIGH, 20000);
  sprintf(buff, "%d,%d\n", pwm_throttle_value, pwm_steering_value);
  Serial.println(buff);
}


