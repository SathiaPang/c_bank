//
// Created by Alex Satya on 6/2/25.
//
/*
 * Handle on creating a new bank account.
 */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "account.h"
#include "../data/fileio.h"

void get_current_date(char *date_str) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(date_str, "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
}

void create_account() {
    Account new_account;

    printf("\n--- Create New Bank Account ---\n");
    // FirstName
    printf("Enter customer's first name: ");
    scanf("%s", new_account.first_name);
    // lastName
    printf("Enter customer's last name: ");
    scanf("%s", new_account.last_name);
    // phoneNum
    printf("Enter customer's phone number: ");
    scanf("%s", new_account.phone_num);
    // Customer-email
    printf("Enter customer's email: ");
    scanf("%s", new_account.email);
    // Account type
    printf("Enter account type [Saving, Checking, Deposit]: ");
    scanf("%s", new_account.account_type);
    // PIN for an account
    printf("Enter a 4-digit PIN:");
    scanf("%4s", new_account.pin); // Read a 4-digit PIN

    //Get the next account number
    new_account.account_number = get_next_account_number();
    // Set customer_id to account_number for simplicity
    new_account.customer_id = new_account.account_number;
    // Get the current date for account creation
    get_current_date(new_account.creation_date);
    // Set default values
    new_account.balance = 0.0;
    new_account.status = 1;

    // Save the new account and check if it was successful
    if (save_account(&new_account)) {
        printf("====================================================\n");
        printf("Success! Account created.\n");
        printf("New Account Number is: %d\n", new_account.account_number);
        printf("====================================================\n");
    } else {
        printf("\nError: Could not save the account.\n");
    }
}

