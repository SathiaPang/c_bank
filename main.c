#include <stdio.h>

#include "account/account.h"
#include "transaction/transaction.h"
#include "menu/menu.h"
#include "views/view.h"
#include "auth/auth.h"
#include "utils/utils.h"

// Function Delcarartions
void run_admin_session(void);

void run_user_session(void);


int main(void) {
    int choice;

    printf("Welcome to CLI Banking Management System!\n");
    do {
        // Admin password for login
        int admin_pass = 1234;
        int get_admin_pass;

        show_login_menu();

        choice = get_choice();
        switch (choice) {
            case 1:
                user_login();
                if (g_is_user_logged_in) {
                    run_user_session();
                }
                break;
            case 2:
                printf("\n Please enter the admin password: ");
                scanf("%d", &get_admin_pass);
                if (get_admin_pass == admin_pass) {
                    printf("Admin login successful!\n");
                    run_admin_session();
                } else {
                    printf("\nInvalid admin password! Please try again.\n");
                }
                break;
            case 0:
                printf("\nThank you for using CLI Banking Management System!\n");
                printf("Goodbye!\n");
                printf("Thank you for using CLI Banking Management System by Alex Satya\n");
                break;
            default:
                printf("\nInvalid choice! Please try again.\n");
                break;
        }
    } while (choice != 0);
    return 0;
}

void run_admin_session(void) {
    int admin_choice;
    do {
        show_admin_menu();
        admin_choice = get_choice();
        switch (admin_choice) {
            case 1:
                create_account();
                press_enter_to_continue();
                break;
            case 2:
                // Deposit funds
                deposit_funds();
                press_enter_to_continue();
                break;
            case 3:
                // Withdraw funds
                withdraw_funds();
                press_enter_to_continue();
                break;
            case 4:
                // Transfer funds
                transfer_funds();
                press_enter_to_continue();
                break;
            case 5:
                // search and View account
                display_and_search_accounts();
                press_enter_to_continue();
                break;
            case 6:
                // Update Account Info
                update_account();
                press_enter_to_continue();
                break;
            case 7:
                // Close Account
                close_account();
                press_enter_to_continue();
                break;
            case 8:
                // View all accounts;
                view_all_accounts();
                press_enter_to_continue();
                break;
            case 9:
                // View all login history
                view_all_login_history();
                press_enter_to_continue();
                break;
            case 10:
                view_all_transaction_history();
                press_enter_to_continue();
                break;
            case 0:
                printf("\nLogging out of Admin Dashboard.......\n");
                break;
            default:
                printf("\nInvalid choice! Please try again.\n");
                break;
        }
    } while (admin_choice != 0);
}

void run_user_session(void) {
    int user_choice;
    do {
        show_user_menu();
        user_choice = get_choice();

        switch (user_choice) {
            case 1:
                user_deposit();
                press_enter_to_continue();
                break;
            case 2:
                user_withdraw();
                press_enter_to_continue();
                break;
            case 3:
                user_transfer();
                press_enter_to_continue();
                break;
            case 4: // "View My Account"
                view_my_account();
                press_enter_to_continue();
                break;
            case 5:
                user_update_account();
                press_enter_to_continue();
                break;
            case 6:
                view_my_login_history(g_current_user.account_number);
                press_enter_to_continue();
                break;
            case 7:
            // view_my_transaction_history(g_current_user.account_number);
            // press_enter_to_continue();
            case 0:
                user_logout();
                break;
            default:
                printf("\nUser feature (choice %d) not implemented yet.\n", user_choice);
                break;
        }
    } while (user_choice != 0);
}
