//
// Created by Alex Satya on 6/4/25.
//
#include <stdio.h>
#include <string.h>
#include "account.h"
#include "../auth/auth.h"
#include "../data/fileio.h"

void user_update_account(void) {
    char entered_pin[5];

    if (!g_is_user_logged_in) {
        printf("\nError: You must be logged in to update your account.\n");
        return;
    }

    printf("\n--- Update Your Account Information ---\n");
    printf("Please enter your current PIN to make changes: ");
    scanf("%s", entered_pin);
    if (strcmp(entered_pin, g_current_user.pin) != 0) {
        printf("\nError: Incorrect PIN. No changes can be made.\n");
        return;
    }

    int choice;
    printf("\nPIN Accepted. What would you like to update?\n");
    printf("1. First Name\n");
    printf("2. Last Name\n");
    printf("3. Phone Number\n");
    printf("4. Email\n");
    printf("5. Change PIN\n");
    printf("0. Cancel\n");
    printf("Select an option: ");
    scanf("%d", &choice);

    bool changed = false;
    switch (choice) {
        case 1:
            printf("Enter new first name: ");
            scanf("%s", g_current_user.first_name);
            changed = true;
            break;
        case 2:
            printf("Enter new last name: ");
            scanf("%s", g_current_user.last_name);
            changed = true;
            break;
        case 3:
            printf("Enter new phone number: ");
            scanf("%s", g_current_user.phone_num);
            changed = true;
            break;
        case 4:
            printf("Enter new email: ");
            scanf("%s", g_current_user.email);
            changed = true;
            break;
        case 5:
            printf("Enter new 4-digit PIN: ");
            scanf("%s", g_current_user.pin);
            changed = true;
            break;
        case 0:
            printf("Update cancelled.\n");
            return;
        default:
            printf("Invalid option.\n");
            return;
    }
    if (changed) {
        if (save_account(&g_current_user)) {
            printf("\nSuccess! Your account has been updated.\n");
        } else {
            printf("\nError: Failed to save your updated details.\n");
        }
    }
}
