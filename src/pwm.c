#include "pwm.h"

void pwm_setup(int pin) {
    wiringPiSetup();
    pinMode(pin, OUTPUT);
    softPwmCreate(pin, 0, 100);
}

void pwm_set(int pin, int value) {
    if (pin == RESISTOR) {
        if (value > 0) softPwmWrite(FAN, 0);
        softPwmWrite(pin, value);
    } else if (pin == FAN) {
        if (value > 0) softPwmWrite(RESISTOR, 0);
        softPwmWrite(pin, value);
    }
}

void pwm_init() {
    pwm_setup(RESISTOR);
    pwm_setup(FAN);
}

void pwm_stop() {
    softPwmStop(RESISTOR);
    softPwmStop(FAN);
}