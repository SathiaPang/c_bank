//
// Created by Alex Satya on 6/4/25.
//

#ifndef AUTH_H
#define AUTH_H

#include "../account/account.h"
#include <stdbool.h>

extern Account g_current_user;
extern bool g_is_user_logged_in;

void user_login(void);

void user_logout(void);
#endif //AUTH_H
