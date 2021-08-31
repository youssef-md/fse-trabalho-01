#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#include "crc.h"
#include "exception_handler.h"

void uart_write(char code, char subcode);
int uart_read_int();
float uart_read_float();
void uart_open();
void uart_close();
void uart_write_int(int value);