#include <time.h>
#include <stdio.h>

void logger_init();
void logger_write(float ti, float te, float tr, int control_signal);
void logger_close();