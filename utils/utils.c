#include <stdio.h> // For printf() and getchar()
#include <stdlib.h> // For exit()
#include "utils.h"


void press_enter_to_continue() {
    printf("\n\nPress Enter to continue...");
    while (getchar() != '\n');
    getchar();
}
