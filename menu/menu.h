//
// Created by Alex Satya on 5/28/25.
//

//Please note the header file (.h) is for declaring functions like the name and its parameters.
//The implementation of the function is in the corresponding source file (.c).

#ifndef MENU_H
#define MENU_H

// Menu display functions
void show_login_menu(void);
void show_user_menu(void);
void show_admin_menu(void);

// Input function
int get_choice(void);

#endif //MENU_H