#include "logger.h"

FILE* fp;

void logger_init() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char filename[28];

    snprintf(filename, 28, "log/%d-%d-%d_%d:%d:%d.csv", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
    fp = fopen(filename, "w");
    fprintf(fp, "data;hora;ti;te;tr;sinal de controle\n");
}

void logger_write(float ti, float te, float tr, int control_signal) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    fprintf(fp, "%d/%d/%d;%d:%d:%d;%f;%f;%f;%d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec, ti, te, tr, control_signal);
}

void logger_close() {
    fclose(fp);
}