//
// Created by Alex Satya on 6/4/25.
//

#include <stdio.h>
#include <string.h>
#include "../account/account.h"
#include "transaction.h"
#include "../data/fileio.h"
#include "../auth/auth.h"
#include "../logger/logger.h"
#include "../utils/utils.h"

/**Admin side functions*/
void deposit_funds(void) {
    Account acc;
    int account_num;
    double amount;

    printf("\n--- Deposit Funds ---\n");
    printf("Enter account number to deposit into: ");
    scanf("%d", &account_num);
    if (find_account(&acc, account_num)) {
        // Step 2: Get the deposit amount
        printf("Account found: %s %s\n", acc.first_name, acc.last_name);
        printf("Current balance: $%.2f\n", acc.balance);
        printf("Enter amount to deposit: ");
        scanf("%lf", &amount);
        if (amount <= 0) {
            printf("Error: Deposit amount must be positive.\n");
            return;
        }
        acc.balance += amount;
        if (save_account(&acc)) {
            printf("\nSuccess! New balance is: $%.2f\n", acc.balance);
        } else {
            printf("\nError: Could not save the transaction.\n");
        }
    } else {
        printf("\nError: Account %d not found.\n", account_num);
    }
}

void withdraw_funds(void) {
    Account acc;
    int account_num;
    double amount;
    char entered_pin[5];

    printf("\n--- Withdraw Funds ---\n");
    printf("Enter account number to withdraw from: ");
    scanf("%d", &account_num);
    if (find_account(&acc, account_num)) {
        printf("Account found: %s %s\n", acc.first_name, acc.last_name);
        printf("Current balance: $%.2f\n", acc.balance);
        printf("Enter amount to withdraw: ");
        scanf("%lf", &amount);
        if (amount <= 0) {
            printf("\nError: Withdrawal amount must be positive.\n");
            return;
        }
        if (amount > acc.balance) {
            printf("\nError: Insufficient funds. You cannot withdraw more than the current balance.\n");
            return;
        }
        printf("Enter the 4-digit PIN for verification: ");
        scanf("%s", entered_pin);
        if (strcmp(entered_pin, acc.pin) != 0) {
            printf("\nError: Incorrect PIN. Transaction cancelled.\n");
            return;
        }
        printf("\nPIN accepted.\n");
        acc.balance -= amount;
        if (save_account(&acc)) {
            printf("Success! Withdrawal complete. New balance is: $%.2f\n", acc.balance);
        } else {
            printf("\nError: Could not save the transaction.\n");
        }
    } else {
        printf("\nError: Account %d not found.\n", account_num);
    }
}

void transfer_funds(void) {
    Account source_acc, dest_acc;
    int source_num, dest_num;
    double amount;
    char entered_pin[5];

    printf("\n--- Transfer Funds ---\n");
    printf("Enter source account number (from): ");
    scanf("%d", &source_num);
    printf("Enter destination account number (to): ");
    scanf("%d", &dest_num);
    printf("Enter amount to transfer: ");
    scanf("%lf", &amount);
    if (source_num == dest_num) {
        printf("\nError: Source and destination accounts cannot be the same.\n");
        return;
    }
    if (amount <= 0) {
        printf("\nError: Transfer amount must be positive.\n");
        return;
    }
    if (!find_account(&source_acc, source_num)) {
        printf("\nError: Source account %d not found.\n", source_num);
        return;
    }
    if (!find_account(&dest_acc, dest_num)) {
        printf("\nError: Destination account %d not found.\n", dest_num);
        return;
    }
    if (amount > source_acc.balance) {
        printf("\nError: Insufficient funds in source account.\n");
        return;
    }
    printf("Please enter PIN for the SOURCE account (%d) to authorize transfer: ", source_num);
    scanf("%s", entered_pin);

    if (strcmp(entered_pin, source_acc.pin) != 0) {
        printf("\nError: Incorrect PIN for source account. Transfer cancelled.\n");
        return;
    }
    printf("\nPIN accepted. Processing transfer...\n");

    source_acc.balance -= amount;
    dest_acc.balance += amount;

    if (save_account(&source_acc) && save_account(&dest_acc)) {
        printf("\nSuccess! Transfer of $%.2f complete.\n", amount);
        printf("New balance for account %d is $%.2f\n", source_acc.account_number, source_acc.balance);
        press_enter_to_continue();
    } else {
        printf("\nCRITICAL ERROR: Failed to save transaction. Please check data file.\n");
        // In a real system, you would have a recovery mechanism here.
    }
}

/** User Side functions*/
void user_deposit(void) {
    double amount;

    if (!g_is_user_logged_in) {
        printf("\nError: You must be logged in to make a deposit.\n");
        return;
    }
    printf("\n--- Deposit to Your Account ---\n");
    printf("Your current balance is: $%.2f\n", g_current_user.balance);
    printf("Enter amount to deposit: ");
    scanf("%lf", &amount);
    if (amount <= 0) {
        printf("\nError: Deposit amount must be a positive number.\n");
        return;
    }

    g_current_user.balance += amount;
    if (save_account(&g_current_user)) {
        printf("\nSuccess! Deposit of $%.2f was successful.\n", amount);
        printf("Your new balance is: $%.2f\n", g_current_user.balance);
        logging_transaction("DEPOSIT", g_current_user.account_number, 0, amount);
        press_enter_to_continue();
    } else {
        printf("\nError: Could not process your deposit. Please try again.\n");
        g_current_user.balance -= amount;
    }
}

void user_withdraw(void) {
    double amount;
    char entered_pin[5];

    if (!g_is_user_logged_in) {
        printf("\nError: You must be logged in to make a withdrawal.\n");
        return;
    }
    printf("\n--- Withdraw From Your Account ---\n");
    printf("Your current balance is: $%.2f\n", g_current_user.balance);
    printf("Enter amount to withdraw: ");
    scanf("%lf", &amount);

    if (amount <= 0) {
        printf("\nError: Withdrawal amount must be a positive number.\n");
        return;
    }
    if (amount > g_current_user.balance) {
        printf("\nError: Insufficient funds. You cannot withdraw more than your balance.\n");
        return;
    }

    printf("Please enter your 4-digit PIN to confirm: ");
    scanf("%s", entered_pin);
    if (strcmp(entered_pin, g_current_user.pin) != 0) {
        printf("\nError: Incorrect PIN. Transaction cancelled.\n");
        return;
    }
    printf("\nPIN accepted.\n");

    g_current_user.balance -= amount;
    if (save_account(&g_current_user)) {
        printf("Success! Withdrawal of $%.2f was successful.\n", amount);
        printf("Your new balance is: $%.2f\n", g_current_user.balance);
        logging_transaction("WITHDRAWAL", g_current_user.account_number, 0, amount);
        press_enter_to_continue();
    } else {
        printf("\nError: Could not process your withdrawal. Please try again.\n");
        // Revert the change if saving fails
        g_current_user.balance += amount;
    }
}

void user_transfer(void) {
    Account dest_acc;
    int dest_num;
    double amount;
    char entered_pin[5];

    if (!g_is_user_logged_in) {
        printf("\nError: You must be logged in to make a transfer.\n");
        return;
    }
    printf("\n--- Transfer Funds from Your Account ---\n");
    printf("Your current balance is: $%.2f\n", g_current_user.balance);
    printf("Enter destination account number to transfer to: ");
    scanf("%d", &dest_num);
    printf("Enter amount to transfer: ");
    scanf("%lf", &amount);
    if (g_current_user.account_number == dest_num) {
        printf("\nError: You cannot transfer money to your own account.\n");
        return;
    }
    if (amount <= 0) {
        printf("\nError: Transfer amount must be positive.\n");
        return;
    }
    if (amount > g_current_user.balance) {
        printf("\nError: Insufficient funds for this transfer.\n");
        return;
    }
    if (!find_account(&dest_acc, dest_num)) {
        printf("\nError: Destination account %d not found.\n", dest_num);
        return;
    }

    printf("Please enter your PIN to authorize the transfer: ");
    scanf("%s", entered_pin);
    if (strcmp(entered_pin, g_current_user.pin) != 0) {
        printf("\nError: Incorrect PIN. Transfer cancelled.\n");
        return;
    }
    printf("\nPIN accepted. Processing transfer...\n");

    g_current_user.balance -= amount;
    dest_acc.balance += amount;
    if (save_account(&g_current_user) && save_account(&dest_acc)) {
        printf("\nSuccess! Transfer of $%.2f to account %d was complete.\n", amount, dest_num);
        printf("Your new balance is: $%.2f\n", g_current_user.balance);
        logging_transaction("TRANSFER", g_current_user.account_number, dest_num, amount);
        press_enter_to_continue();
    } else {
        printf("\nCRITICAL ERROR: Failed to save transaction. Please check data file.\n");
        // Revert the change in memory to keep the session consistent
        g_current_user.balance += amount;
    }
}
