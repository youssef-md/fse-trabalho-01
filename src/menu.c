#include "menu.h"

void menu_init() {
    initscr();
    cbreak();
}

void menu_close() {
    endwin();
}

WINDOW * menu_get_ui(int size) {
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    WINDOW * menuwin = newwin(size, xMax-12, yMax-8, 5);
    box(menuwin, 0, 0);
    refresh();
    wrefresh(menuwin);

    keypad(menuwin, true);

    return menuwin;
}

void menu_set_title(WINDOW * menuwin, char * title) {
    wattron(menuwin, A_BOLD);
    mvwprintw(menuwin, 1, 1, title);
    wattroff(menuwin, A_BOLD);
}

int menu_handler(WINDOW * menuwin, char * choices[], int size) {
    int choice;
    int highlight = 0;

    while(1) {
        for(int i = 0; i < size; i++) {
            if (i == highlight)
                wattron(menuwin, A_REVERSE);
            mvwprintw(menuwin, i+2, 1, choices[i]);
            wattroff(menuwin, A_REVERSE);
        }
        choice = wgetch(menuwin);

        switch(choice) {
            case KEY_UP:
                if (highlight > 0) 
                    highlight--;
                break;
            case KEY_DOWN:
            if (highlight < size - 1)
                    highlight++;
                break;
            default:
                break;
        }
        if(choice == 10)
            return highlight;
    }
}

int menu(char* title, char* options[], int size) {
    WINDOW * menuwin = menu_get_ui(size+3);

    menu_set_title(menuwin, title);
    return menu_handler(menuwin, options, size);
}

int menu_strategy() {
    char* options[2] = {"Terminal", "Chave"};
    return menu("Como deseja escolher a estratégia de controle?", options, 2);
}

int menu_open() {
    char* options[] = {"Estratégia de controle", "Temperatura de referência", "Histerese", "kp", "ki", "kd"};
    return menu("O que deseja alterar?", options, 6);
}

void menu_show_tmp(float ti, float te, float tr) {
    refresh();
    WINDOW* tempwin = menu_get_ui(5);
    mvwprintw(tempwin, 1, 1, "TI: %4.2f", ti);
    mvwprintw(tempwin, 2, 1, "TE: %4.2f", te);
    mvwprintw(tempwin, 3, 1, "TR: %4.2f", tr);
    refresh();
    wrefresh(tempwin);
}

int menu_control_strategy() {
    char* options[2] = {"On/Off", "PID"};
    return menu("Qual estratégia de controle deseja usar?", options, 2);
}

int menu_reference_source() {
    char* options[2] = {"Terminal", "Potenciômetro"};
    return menu("A temperatura de referência deve ser inserida via terminal ou potenciômetro?", options, 2);
}

float menu_get_float(char * msg) {
    WINDOW * menuwin = menu_get_ui(5);
    menu_set_title(menuwin, msg);
    float tmp;
    mvwscanw(menuwin, 2, 1, "%f", &tmp);
    menu_clear(menuwin);
    return tmp;
}

void menu_clear(WINDOW* win) {
    wclear(win);
}