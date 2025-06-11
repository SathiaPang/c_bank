//
// Created by Alex Satya on 6/4/25.
//

#include <stdio.h>
#include <string.h>
#include "auth.h"
#include "../data/fileio.h"
#include "../logger/logger.h"

// Global Variables Declarations
Account g_current_user;
bool g_is_user_logged_in = false;

// Function Definitions
void user_login(void) {
    int account_num;
    char entered_pin[5];
    Account temp_acc;

    printf("\n--- User Login ---\n");
    printf("Enter your account number: ");
    scanf("%d", &account_num);
    printf("Enter your 4-digit PIN: ");
    scanf("%s", entered_pin);

    if (find_account(&temp_acc, account_num)) {
        if (temp_acc.status == 0) {
            printf("\nError: This account is closed. Please contact the bank.\n");
            log_login_attempt(account_num, "FAILED - Account Closed");
            return;
        }
        if (strcmp(entered_pin, temp_acc.pin) == 0) {
            printf("\nLogin successful! Welcome, %s.\n", temp_acc.first_name);
            g_is_user_logged_in = true;
            g_current_user = temp_acc; // Copy data to our global session variable
            log_login_attempt(account_num, "SUCCESS");
        } else {
            printf("\nError: Invalid account number or PIN.\n");
            log_login_attempt(account_num, "FAILED - Incorrect PIN");
        }
    } else {
        printf("\nError: Invalid account number or PIN.\n");
        log_login_attempt(account_num, "FAILED - Account Not Found");
    }
}

void user_logout(void) {
    g_is_user_logged_in = false;
    // We can also clear the global user struct for security
    memset(&g_current_user, 0, sizeof(Account));
    printf("\nYou have been successfully logged out.\n");
}
