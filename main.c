#include <stdio.h>

#include "account/account.h"
#include "transaction/transaction.h"
#include "menu/menu.h"
#include "views/view.h"
#include "auth/auth.h"


// Placement of delcaraing functions is here.
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
                break;
            case 2:
                // Deposit funds
                deposit_funds();
                break;
            case 3:
                // Withdraw funds
                withdraw_funds();
                break;
            case 4:
                // Transfer funds
                transfer_funds();
                break;
            case 5:
                // search and View account
                display_and_search_accounts();
                break;
            case 6:
                // Update Account Info
                update_account();
                break;
            case 7:
                // Close Account
                close_account();
                break;
            case 8:
                // View all accounts;
                view_all_accounts();
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
                break;
            case 2:
                user_withdraw();
                break;
            case 3:
                user_transfer();
                break;
            case 4: // "View My Account"
                view_my_account();
                break;
            case 5:
                user_update_account();
                break;
            case 0:
                user_logout();
                break;
            default:
                printf("\nUser feature (choice %d) not implemented yet.\n", user_choice);
                break;
        }
    } while (user_choice != 0);
}
