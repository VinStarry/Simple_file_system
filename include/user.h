//
// Created by 永鑫   徐 on 2019-02-25.
//

#ifndef VFS_USER_H
#define VFS_USER_H

#include "data_structures.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define USER_NAME_MAX_LEN 50
#define USER_PSW_MAX_LEN 50

struct user_linked_list {
    unsigned int u_id;
    char *name;
    char *psw;
    char priority;
    struct user_linked_list *next;
};

struct user_linked_list *create_usr(struct user_linked_list *usr_list_head, char *name, char *psw, char priority);
bool change_pswd(struct user_linked_list *usr_list_head, struct user *usr, char *new_psw);
bool change_user_name(struct user_linked_list *usr_list_head, struct user *usr, char *new_name);
struct user_linked_list *load_users_info(FILE *fp);
bool save_users_info(struct user_linked_list *usr_list_head, FILE *fp);
void print_user_info(struct user_linked_list *usr_list_head);

#endif //VFS_USER_H
