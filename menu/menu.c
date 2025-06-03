//
// Created by Alex Satya on 5/28/25.
//
// implementation of the menu functions body

#include <stdio.h>
#include "menu.h"

void show_login_menu(void) {
    printf("\n");
    printf("\t=========================================\n");
    printf("\t===== CLI Banking Management System =====\n");
    printf("\t=========================================\n");
    printf("\t\t1. Login as User\n");
    printf("\t\t2. Login as Admin\n");
    printf("\t\t0. Exit\n");
    printf("\t=========================================\n");
    printf("Select an option: ");
}

void show_user_menu(void) {
    printf("\n");
    printf("\t=========================================\n");
    printf("\t========== User Dashboard ===============\n");
    printf("\t=========================================\n");
    printf("\t\t1. Deposit Funds\n");
    printf("\t\t2. Withdraw Funds\n");
    printf("\t\t3. Transfer Funds\n");
    printf("\t\t4. View My Account\n");
    printf("\t\t5. Update My Account\n");
    printf("\t\t0. Logout\n");
    printf("\t=========================================\n");
    printf("Select an option: ");
}

void show_admin_menu(void) {
    printf("\n");
    printf("\t=========================================\n");
    printf("\t========== Admin Dashboard ==============\n");
    printf("\t=========================================\n");
    printf("\t\t1. Create Account\n");
    printf("\t\t2. Deposit Funds\n");
    printf("\t\t3. Withdraw Funds\n");
    printf("\t\t4. Transfer Funds\n");
    printf("\t\t5. Search & View Account\n");
    printf("\t\t6. Update Account\n");
    printf("\t\t7. Close Account\n");
    printf("\t\t8. View All Accounts\n");
    printf("\t\t0. Logout\n");
    printf("\t=========================================\n");
    printf("Select an option: ");
}

int get_choice(void) {
    int choice;
    scanf("%d", &choice);
    return choice;
}
