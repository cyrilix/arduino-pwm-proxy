#PWM Proxy for Arduino

Simple Arduino based PWM proxy. It is used to get the PWM orders received from Tx and sent it to the Raspberry through serial port. 
It outputs last measured pwm signal each 50ms

output format is :
<pwm throttle>,<pwm_steering>,<pwm_freq>
where :
pwm_throttle is the pwm duration of the throttle signal, in us
pwm_steering is the pwm duration of the steering signal, in us
pwm_freq is the perceived pwn frequency.

When the algorithm is unable to detect the pwm signal, it ouputs '-,-,-'

Inspired from  http://www.benripley.com/diy/arduino/three-ways-to-read-a-pwm-signal-with-arduino/ for other way.

