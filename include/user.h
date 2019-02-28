//
// Created by 永鑫   徐 on 2019-02-25.
//

#ifndef VFS_USER_H
#define VFS_USER_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define USER_NAME_MAX_LEN 50
#define USER_PSW_MAX_LEN 50

struct usr_ptr {
    unsigned int u_id;
    char *name;
    unsigned int priority;
};

struct user_linked_list {
    unsigned int u_id;
    char *name;
    char *psw;
    unsigned int priority;
    struct user_linked_list *next;
};

struct user_linked_list *create_usr(struct user_linked_list *usr_list_head, char *name, char *psw, unsigned int priority);
bool change_pswd(struct user_linked_list *usr_list_head, struct user_linked_list *usr, char *new_psw);
bool change_user_name(struct user_linked_list *usr_list_head, struct user_linked_list *usr, char *new_name);
struct user_linked_list *load_users_info(void);
bool save_users_info(struct user_linked_list *usr_list_head);
void print_user_info(struct user_linked_list *usr_list_head);
void free_user_info(struct user_linked_list *usr_list_head);

bool get_user_by_name(struct user_linked_list *user_list, struct usr_ptr *current_user, const char *name);
void print_current_user_info(struct usr_ptr *info);

char *get_user_by_user_id(struct user_linked_list *user_list, unsigned long user_id);

#endif //VFS_USER_H
