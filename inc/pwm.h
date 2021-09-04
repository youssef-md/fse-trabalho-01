#include <softPwm.h>
#include <wiringPi.h>

#define RESISTOR  4
#define FAN 5

void pwm_setup(int pin);
void pwm_set(int pin, int value);
void pwm_init();
void pwm_stop();