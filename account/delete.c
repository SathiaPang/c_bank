//
// Created by Alex Satya on 6/4/25.
//
#include <stdio.h>
#include <string.h>
#include "account.h"
#include "../data/fileio.h"

void close_account(void) {
    Account acc;
    int account_num;
    char entered_pin[5];

    printf("\n--- Close Bank Account ---\n");
    printf("Enter account number to close: ");
    scanf("%d", &account_num);
    if (find_account(&acc, account_num)) {
        if (acc.status == 0) {
            printf("\nInformation: This account is already closed.\n");
            return;
        }
        if (acc.balance != 0.0) {
            printf("\nError: Account balance is not zero ($%.2f).\n", acc.balance);
            printf("Please withdraw all funds before closing the account.\n");
            return;
        }
        printf("Account balance is zero. Ready to close.\n");
        printf("Please enter the account PIN to confirm closure: ");
        scanf("%s", entered_pin);
        if (strcmp(entered_pin, acc.pin) != 0) {
            printf("\nError: Incorrect PIN. Closure failed.\n");
            return;
        }

        acc.status = 0; // 0 = inactive
        if (save_account(&acc)) {
            printf("\nSuccess! Account %d has been closed and marked as inactive.\n", acc.account_number);
        } else {
            printf("\nError: Failed to update account status.\n");
        }
    } else {
        printf("\nError: Account %d not found.\n", account_num);
    }
}
