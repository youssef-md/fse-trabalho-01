#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>
#include <signal.h>

#include "bme280.h"
#include "logger.h"
#include "lcd.h"
#include "menu.h"
#include "pid.h"
#include "pwm.h"
#include "uart.h"

void update_temperatures(int strategy);
void handle_on_of();
void handle_pid();
void *update_display(void *args);
void *update_csv(void *args);
void handle_interruption(int value);
void config_signals();
int main();