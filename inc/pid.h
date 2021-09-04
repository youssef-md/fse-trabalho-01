#include <stdio.h>

#ifndef PID_H_
#define PID_H_

void pid_config_constants(double Kp_, double Ki_, double Kd_);
void pid_update_reference(float referencia_);
double pid_controll(double saida_medida);

#endif /* PID_H_ */