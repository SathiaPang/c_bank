//
// Created by Alex Satya on 6/2/25.
//

#ifndef ACCOUNT_H
#define ACCOUNT_H

typedef struct {
    int customer_id; // Unique identifier for the customer
    char first_name[50];
    char last_name[50];
    char phone_num[10];
    char email[50];
    int account_number;
    char pin[5];
    double balance;
    char account_type[20];
    char creation_date[11];
    int status; // 1 for active, 0 for inactive
} Account;

/** Admin Side Functions*/
void create_account(void);

void update_account(void);

void close_account(void);

/** User Side Functions*/
void user_update_account(void);

#endif //ACCOUNT_H
