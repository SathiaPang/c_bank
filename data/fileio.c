//
// Created by Alex Satya on 6/2/25.
//

#include <stdio.h>
#include "fileio.h"
#include "../account/account.h"

// Function to save an account to the file
int get_next_account_number() {
    Account account;
    FILE *f1;
    f1 = fopen(acc_data_file, "r");
    if (f1 == NULL) {
        return 101;
    }
    fseek(f1, -sizeof(Account), SEEK_END);
    fread(&account, sizeof(Account), 1, f1);
    fclose(f1);
    return account.account_number + 1;
}

int save_account(const Account *acc_to_save) {
    long position = -1;
    Account temp_acc;
    FILE *file = fopen(acc_data_file, "r+b");
    if (file == NULL) {
        file = fopen(acc_data_file, "wb");
        if (file == NULL) {
            printf("Error: Could not open or create file.\n");
            return 0;
        }
    }
    while (fread(&temp_acc, sizeof(Account), 1, file) == 1) {
        if (temp_acc.account_number == acc_to_save->account_number) {
            position = ftell(file) - sizeof(Account);
            break;
        }
    }
    if (position != -1) {
        fseek(file, position, SEEK_SET);
    } else {
        fseek(file, 0, SEEK_END);
    }
    fwrite(acc_to_save, sizeof(Account), 1, file);
    fclose(file);
    return 1;
}

int find_account(Account *acc, int account_number) {
    FILE *file = fopen(acc_data_file, "rb");
    if (file == NULL) {
        return 0;
    }
    while (fread(acc, sizeof(Account), 1, file) == 1) {
        if (acc->account_number == account_number) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}
