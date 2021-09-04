#include "main.h"

pthread_t thread_display, thread_csv_logger;

float ti, te, tr;
float hysteresis;
int control_signal = 0;
int ref_temp_source;
int control_strategy;
int strategy_source;
int has_stopped = 0;
double kp, ki, kd;

void update_temperatures(int strategy) {
    te = get_external_temperature();
    uart_write(0x23, 0xC1);
    ti = uart_read_float();

    if (strategy == POTENTIOMETER) {
        uart_write(0x23, 0xC2);
        tr = uart_read_float();
        if (control_strategy == PID)
            pid_update_reference(tr);
    }

    if (tr < te) tr = te;
}

void handle_on_of() {
    float top = tr + hysteresis/2.0;
    float bottom = tr - hysteresis/2.0;

    if (ti >= top) {
        pwm_set(FAN, 100);
        control_signal = -100;
    } else if (ti <= bottom) {
        pwm_set(RESISTOR, 100);
        control_signal = 100;
    }
}

void handle_pid() {
    double pid_value = pid_controll(ti);

    if (pid_value > 0.0)
        pwm_set(RESISTOR, pid_value);
    else if(pid_value < 0.0 && pid_value > -40.0) {
        pwm_set(RESISTOR, 0);
        pwm_set(FAN, 0);
    } else
        pwm_set(FAN, pid_value * -1);

    control_signal = pid_value;
}

void *update_display(void *args) {
    while(1) {
        update_temperatures(ref_temp_source);
        write_lcd(ti, te, tr);

        if (control_strategy == ON_OFF)
            handle_on_of();
        else if (control_strategy == PID)
            handle_pid();

        uart_write_int(control_signal);
        menu_show_tmp(ti, te, tr);
        
        sleep(1);
    }
}

void *update_csv(void *args) {
    while(1) {
        logger_write(ti, te, tr, control_signal);
        sleep(2);
    }
}

void handle_interruption(int value) {
    pthread_cancel(thread_display);
    pthread_cancel(thread_csv_logger);
    pthread_join(thread_display, NULL);
    pthread_join(thread_csv_logger, NULL);
    menu_close();
    logger_close();
    uart_close();
    pwm_stop();
    exit(1);
}

void config_signals() {
    signal(SIGHUP, handle_interruption);
    signal(SIGINT, handle_interruption);
    signal(SIGTERM, handle_interruption);
    signal(SIGQUIT, handle_interruption);
    signal(SIGTSTP, handle_interruption);
}

int main() {
    config_signals();
    uart_open();
    init_i2c();
    lcd_init();
    pwm_setup(RESISTOR);
    pwm_setup(FAN);
    menu_init();

    strategy_source = menu_strategy();
    if (strategy_source == TERMINAL)
        control_strategy = menu_control_strategy();

    ref_temp_source = menu_reference_source();

    if (ref_temp_source == TERMINAL)
        tr = menu_get_float("Qual valor deseja inserir para a TR?");

    if(control_strategy == ON_OFF)
        hysteresis = menu_get_float("Qual valor deseja inserir para a histerese?");
    else if (control_strategy == PID) {
        kp = menu_get_float("Qual valor deseja inserir para o KP?");
        ki = menu_get_float("Qual valor deseja inserir para o KI?");
        kd = menu_get_float("Qual valor deseja inserir para o KD?");
        pid_config_constants(kp, ki, kd);
        pid_update_reference(tr);
    }

    logger_init();

    pthread_create(&thread_display, NULL, &update_display, NULL);
    pthread_create(&thread_csv_logger, NULL, &update_csv, NULL);
    pthread_join(thread_display, NULL);
    pthread_join(thread_csv_logger, NULL);

    menu_close();
    return 0;
}
