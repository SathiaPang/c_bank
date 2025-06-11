//
// Created by Alex Satya on 6/11/25.
//

#ifndef LOGGER_H
#define LOGGER_H

void logging_transaction(const char *type, int source_acc, int dest_acc, double amount);

void log_login_attempt(int account_number, const char *status);

#endif //LOGGER_H
