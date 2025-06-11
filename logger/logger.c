//
// Created by Alex Satya on 6/11/25.
//

#include <stdio.h>
#include <time.h>
#include "logger.h"

#include <string.h>

void logging_transaction(const char *type, int source_acc, int dest_acc, double amount) {
    FILE *log_file = fopen("transaction.log", "a");
    if (log_file == NULL) {
        return;
    }
    time_t now = time(NULL);
    char *timestamp = ctime(&now);
    timestamp[strlen(timestamp) - 1] = '\0'; // Remove newline character
    if (dest_acc == 0) {
        // For deposit and withdrawal
        fprintf(log_file, "[%s] | Type: %s, Account: %d, Amount: %.2f\n",
                timestamp, type, source_acc, amount);
    } else {
        // For transfer
        fprintf(log_file, "[%s] | Type: %s, From: %d, To: %d, Amount: %.2f\n",
                timestamp, type, source_acc, dest_acc, amount);
    }
    fclose(log_file);
}

void log_login_attempt(int account_number, const char *status) {
    FILE *log_file = fopen("login_history.log", "a");
    if (log_file == NULL) {
        return; // Cannot open log file
    }

    time_t now = time(NULL);
    char *timestamp = ctime(&now);
    timestamp[strlen(timestamp) - 1] = '\0'; // Remove newline

    fprintf(log_file, "[%s] | Account: %d, Status: %s\n",
            timestamp, account_number, status);

    fclose(log_file);
}
