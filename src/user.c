//
// Created by 永鑫   徐 on 2019-02-25.
//

#include "../include/user.h"



struct user_linked_list *create_usr(struct user_linked_list *usr_list_head, char *name, char *psw, char priority) {
    if (!usr_list_head) {
        usr_list_head = (struct user_linked_list *) malloc(sizeof(struct user_linked_list));
        usr_list_head->priority = 0;
        usr_list_head->next = NULL;
    }
    struct user_linked_list *ptr = usr_list_head;
    while (ptr->next)
        ptr = ptr->next;
    ptr->next = (struct user_linked_list *)malloc(sizeof(struct user_linked_list));
    ptr = ptr->next;
    char *uname = (char *)malloc(sizeof(char) * USER_NAME_MAX_LEN);
    char *upsw = (char *)malloc(sizeof(char) * USER_PSW_MAX_LEN);
    strcpy(uname, name);
    strcpy(upsw, psw);
    ptr->next = NULL;
    ptr->name = uname;
    ptr->psw = upsw;
    ptr->priority = priority;
    ptr->u_id = (unsigned)usr_list_head->priority;
    usr_list_head->priority++;
    return usr_list_head;
}

bool change_pswd(struct user_linked_list *usr_list_head, struct user *usr, char *new_psw) {
    if (!usr_list_head)
        return false;
    struct user_linked_list *ptr = usr_list_head;
    while (ptr->next) {
        ptr = ptr->next;
        if (!strcmp(usr->name, ptr->name)) {
            free(ptr->psw);
            char *upsw = (char *)malloc(sizeof(char) * USER_PSW_MAX_LEN);
            strcpy(upsw, new_psw);
            ptr->psw = upsw;
            return true;
        }
    }
    return false;
}

bool change_user_name(struct user_linked_list *usr_list_head, struct user *usr, char *new_name) {
    if (!usr_list_head)
        return false;
    struct user_linked_list *ptr = usr_list_head;
    while (ptr->next) {
        ptr = ptr->next;
        if (!strcmp(usr->psw, ptr->psw)) {
            free(ptr->name);
            char *uname = (char *)malloc(sizeof(char) * USER_PSW_MAX_LEN);
            strcpy(uname, new_name);
            ptr->name = uname;
            return true;
        }
    }
    return false;
}

struct user_linked_list *load_users_info(FILE *fp) {

}

bool save_users_info(struct user_linked_list *usr_list_head, FILE *fp) {

}

void print_user_info(struct user_linked_list *usr_list_head) {
    struct user_linked_list *ptr = usr_list_head;
    if (!ptr)
        return;
    while (ptr->next) {
        ptr = ptr->next;
        printf("uid: %ud\tname: %s\t\tpsw: %s\t\tpriority: %d\n", ptr->u_id, ptr->name, ptr->psw, ptr->priority);
    }
}