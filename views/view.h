//
// Created by Alex Satya on 6/4/25.
//

#ifndef VIEW_H
#define VIEW_H
#include "../account/account.h"

/** Admin Side Function */
void display_and_search_accounts(void);

void print_account_details(const Account *acc);

void view_all_accounts(void);

void view_all_login_history(void);

void view_all_transaction_history(void);


/** User Side Function */
void view_my_account(void);

void view_my_login_history(int account_number);

void view_my_transaction_history(int account_number);

#endif //VIEW_H
