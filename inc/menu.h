#include <stdio.h>
#include <ncurses.h>

#define ON_OFF 0
#define PID    1

#define TERMINAL       0
#define POTENTIOMETER  1

void menu_init();
void menu_close();
WINDOW * menu_get_ui(int size);
void menu_set_title(WINDOW * menuwin, char * title);
int menu_handler(WINDOW * menuwin, char * choices[], int size);
int menu(char* title, char* options[], int size);
int menu_strategy();
int menu_open();
void menu_show_tmp(float te, float ti, float tr);
int menu_control_strategy();
int menu_reference_source();
float menu_get_float(char * msg);
void menu_clear(WINDOW* win);