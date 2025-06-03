//
// Created by Alex Satya on 6/4/25.
//

#include <stdio.h>
#include "view.h"
#include "../account/account.h"
#include "../data/fileio.h"
#include "../auth/auth.h"

// --- The "Printer" Function ---
void print_account_details(const Account *acc) {
    printf("\n--- Account Details ---\n");
    printf("Customer ID:      %d\n", acc->customer_id);
    printf("Account Number:   %d\n", acc->account_number);
    printf("Owner Name:       %s %s\n", acc->first_name, acc->last_name);
    printf("Account Type:     %s\n", acc->account_type);
    printf("Balance:          $%.2f\n", acc->balance);
    printf("Email:            %s\n", acc->email);
    printf("Phone Number:     %s\n", acc->phone_num);
    printf("Creation Date:    %s\n", acc->creation_date);
    printf("Status:           %s\n", acc->status == 1 ? "Active" : "Inactive");
    printf("------------------------\n");
}

// --- The "Display and Search" Function ---
void display_and_search_accounts(void) {
    Account acc;
    int acc_num_to_find;
    printf("\n--- Search for an Account ---\n");
    printf("Enter the account number to view: ");
    scanf("%d", &acc_num_to_find);
    if (find_account(&acc, acc_num_to_find)) {
        print_account_details(&acc);
    } else {
        printf("\nError: Account with number %d was not found.\n", acc_num_to_find);
    }
}

void view_all_accounts(void) {
    Account acc;
    FILE *file = fopen(acc_data_file, "rb");

    if (file == NULL) {
        printf("\nNo accounts exist in the system yet.\n");
        return;
    }
    printf("\n--- All Accounts Report ---\n");
    printf("=================================================================================\n");
    printf("| %-12s | %-20s | %-15s | %-10s |\n", "Account No.", "Customer Name", "Balance", "Status");
    printf("=================================================================================\n");
    while (fread(&acc, sizeof(Account), 1, file) == 1) {
        char full_name[101];
        snprintf(full_name, sizeof(full_name), "%s %s", acc.first_name, acc.last_name);
        printf("| %-12d | %-20s | $%-14.2f | %-10s |\n",
               acc.account_number,
               full_name,
               acc.balance,
               acc.status == 1 ? "Active" : "Inactive");
    }
    printf("=================================================================================\n");
    printf("--- End of Report ---\n");
    fclose(file);
}

// --- The "View My Account" Function ---
void view_my_account(void) {
    printf("\n--- Your Account Information ---\n");
    print_account_details(&g_current_user);
}
