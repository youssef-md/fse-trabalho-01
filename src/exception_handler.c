#include "exception_handler.h"

void handle_error(int int_res, char *string) {
    if(int_res >= 0) return;
 
    perror(string);
    exit(1);
}