//
// Created by Alex Satya on 6/2/25.
//

#ifndef FILEIO_H
#define FILEIO_H

#include "../account/account.h"

// Declaration of file
#define acc_data_file "accounts.dat"
#define login_history_file "login_history.log"
#define transaction_log_file "transaction.log"


// Function to get the next account number
int get_next_account_number();

// Function to save an account to the file
int save_account(const Account *account_to_save);

// Function to find an account by account number
int find_account(Account *acc, int account_number);


#endif //FILEIO_H

