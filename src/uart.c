#include "uart.h"

unsigned char buffer[256] = {0};
unsigned char *a = &buffer[0];
char address = 0x01;
int fd;

void uart_write(char code, char subcode) {
    *a++ = address;
    *a++ = code;
    *a++ = subcode;
    *a++ = 4;
    *a++ = 3;
    *a++ = 3;
    *a++ = 4;
    *a++ = calcula_CRC(buffer, 7);
    *a++ = calcula_CRC(buffer, 8);

    int write_res = write(fd, buffer, 9);
    handle_error(write_res, "[UART] Erro na escrita");

    sleep(1);
    a = &buffer[0];
}

void uart_write_int(int value) {
    *a++ = address;
    *a++ = 0x16;
    *a++ = 0xD1;
    *a++ = 4;
    *a++ = 3;
    *a++ = 3;
    *a++ = 4;
    *a++ = value & 0xFF;
    *a++ = (value >> 8) & 0xFF;
    *a++ = (value >> 16) & 0xFF;
    *a++ = (value >> 24) & 0xFF;
    *a++ = calcula_CRC(buffer, 11);
    *a++ = calcula_CRC(buffer, 12);

    int write_res = write(fd, buffer, 13);
    handle_error(write_res, "[UART] Erro na escrita INT");

    sleep(1);
    a = &buffer[0];
}

int uart_read_int() {
    int ti, read_res;
    char tmp;

    read_res = read(fd, &tmp, 1);
    read_res = read(fd, &tmp, 1);
    read_res = read(fd, &tmp, 1);
    read_res = read(fd, &ti, sizeof(int));
    read_res = read(fd, &tmp, 1);
    read_res = read(fd, &tmp, 1);

    handle_error(read_res, "[UART] Erro na leitura");
    return ti;
}

float uart_read_float() {
    char tmp;
    float ti;
    int read_res;

    read_res = read(fd, &tmp, 1);
    read_res = read(fd, &tmp, 1);
    read_res = read(fd, &tmp, 1);
    read_res = read(fd, &ti, sizeof(float));
    read_res = read(fd, &tmp, 1);
    read_res = read(fd, &tmp, 1);

    handle_error(read_res, "[UART] Erro na leitura FLOAT");
    return ti;
}

void uart_open() {
    fd = open("/dev/serial0", O_RDWR | O_NOCTTY | O_NDELAY);
}

void uart_close() {
    close(fd);
}