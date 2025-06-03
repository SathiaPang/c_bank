cmake_minimum_required(VERSION 3.31)
project(c_bank C)

set(CMAKE_C_STANDARD 11)

add_executable(c_bank main.c
        menu/menu.h
        menu/menu.c
        account/account.h
        account/create.c
        data/fileio.c
        data/fileio.h
        views/view.c
        views/view.h
        transaction/transaction.h
        transaction/transaction.c
        account/update.c
        account/delete.c
        auth/auth.c
        auth/auth.h
        account/user_account.c)
