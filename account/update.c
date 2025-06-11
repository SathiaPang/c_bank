//
// Created by Alex Satya on 6/4/25.
//

#include <stdio.h>
#include <string.h>
#include "../account/account.h"
#include "../data/fileio.h"
#include "../views/view.h"

void update_account(void) {
    Account acc;
    int account_num;
    char entered_pin[5];

    printf("\n--- Update Account Information ---\n");
    printf("Enter account number to update: ");
    scanf("%d", &account_num);

    if (find_account(&acc, account_num)) {
        print_account_details(&acc);

        printf("\nPlease enter the account PIN to make changes: ");
        scanf("%s", entered_pin);
        if (strcmp(entered_pin, acc.pin) != 0) {
            printf("\nError: Incorrect PIN. Update failed.\n");
            return;
        }
        int choice;
        printf("\nPIN Accepted. What do you want to update?\n");
        printf("1. First Name\n");
        printf("2. Last Name\n");
        printf("3. Phone Number\n");
        printf("4. Email\n");
        printf("5. Reset PIN\n");
        printf("0. Cancel\n");
        printf("Select an option: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter new first name: ");
                scanf("%s", acc.first_name);
                break;
            case 2:
                printf("Enter new last name: ");
                scanf("%s", acc.last_name);
                break;
            case 3:
                printf("Enter new phone number: ");
                scanf("%s", acc.phone_num);
                break;
            case 4:
                printf("Enter new email: ");
                scanf("%s", acc.email);
                break;
            case 5:
                printf("Enter new 4-digit PIN: ");
                scanf("%s", acc.pin);
                break;
            case 0:
                printf("Update cancelled.\n");
                return;
            default:
                printf("Invalid option.\n");
                return;
        }
        if (save_account(&acc)) {
            printf("\nSuccess! Account has been updated.\n");
        } else {
            printf("\nError: Failed to save updated account details.\n");
        }
    } else {
        printf("\nError: Account %d not found.\n", account_num);
    }
}
