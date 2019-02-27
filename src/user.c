//
// Created by 永鑫   徐 on 2019-02-25.
//

#include "../include/user.h"

const char * const filename = "./data/user_info.txt";

struct user_linked_list *create_usr(struct user_linked_list *usr_list_head, char *name, char *psw, unsigned int priority) {
    if (!usr_list_head) {
        usr_list_head = (struct user_linked_list *) malloc(sizeof(struct user_linked_list));
        usr_list_head->priority = 0;
        usr_list_head->psw = NULL;
        usr_list_head->name = NULL;
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

bool change_pswd(struct user_linked_list *usr_list_head, struct user_linked_list *usr, char *new_psw) {
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

bool change_user_name(struct user_linked_list *usr_list_head, struct user_linked_list *usr, char *new_name) {
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

struct user_linked_list *load_users_info(void) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        system("pwd");
        printf("failed!\n");
        return false;
    }
    struct user_linked_list *ptr = (struct user_linked_list *)malloc(sizeof(struct user_linked_list));
    struct user_linked_list *head = ptr;
    if (!ptr)
        return false;
    ptr->name = NULL;
    ptr->psw = NULL;
    ptr->priority = 0;
    char u_id[10], u_name[USER_NAME_MAX_LEN], u_psw[USER_PSW_MAX_LEN], priority[10];
    while (4 == fscanf(fp, "%s%s%s%s\n", u_id, u_name, u_psw, priority)) {
        ptr->next = (struct user_linked_list *)malloc(sizeof(struct user_linked_list));
        ptr = ptr->next;
        ptr->next = NULL;
        sscanf(u_id, "%u", &ptr->u_id);
        char *uname = (char *)malloc(sizeof(char) * USER_NAME_MAX_LEN);
        char *upsw = (char *)malloc(sizeof(char) * USER_PSW_MAX_LEN);
        strcpy(uname, u_name);
        strcpy(upsw, u_psw);
        ptr->name = uname;
        ptr->psw = upsw;
        sscanf(priority, "%u", &ptr->priority);
    }
    return head;
}

bool save_users_info(struct user_linked_list *usr_list_head) {
    struct user_linked_list *ptr = usr_list_head;
    if (!ptr)
        return false;
    FILE *fp = fopen(filename, "w");
    if (!fp)
        return false;
    while (ptr->next) {
        ptr = ptr->next;
        fprintf(fp, "%u\t%s\t%s\t%d\n", ptr->u_id, ptr->name, ptr->psw, ptr->priority);
    }
    fclose(fp);
    return true;
}

void print_user_info(struct user_linked_list *usr_list_head) {
    struct user_linked_list *ptr = usr_list_head;
    if (!ptr)
        return;
    while (ptr->next) {
        ptr = ptr->next;
        printf("uid: %u\tname: %s\t\tpsw: %s\t\tpriority: %d\n", ptr->u_id, ptr->name, ptr->psw, ptr->priority);
    }
}

void free_user_info(struct user_linked_list *usr_list_head) {
    struct user_linked_list *ptr = usr_list_head;
    if (!ptr)
        return ;
    while (ptr->next) {
        ptr = ptr->next;
        if (usr_list_head->name)
           free(usr_list_head->name);
        if (usr_list_head->psw)
            free(usr_list_head->psw);
        free(usr_list_head);
        usr_list_head = ptr;
    }
}

bool get_user_by_name(struct user_linked_list *user_list, struct usr_ptr *current_user, const char *name) {
    struct user_linked_list *ptr = user_list;
    bool found = false;
    char psw[USER_PSW_MAX_LEN];
    while (ptr) {
        ptr = ptr->next;
        if (ptr) {
            if (!strcmp(ptr->name, name)) {
                if (ptr->priority < 2) {
                    printf("input password of %s\n", ptr->name);
                    fgets(psw, USER_PSW_MAX_LEN, stdin);
                    psw[strlen(psw) - 1] = '\0';
                    if (!strcmp(psw, ptr->psw)) {
                        current_user->name = ptr->name;
                        current_user->priority = ptr->priority;
                        current_user->u_id = ptr->u_id;
                        found = true;
                        break;
                    }
                    else {
                        printf("%s\n", "sorry, try again!");
                        return found;
                    }
                }
                else {
                    current_user->name = ptr->name;
                    current_user->priority = ptr->priority;
                    current_user->u_id = ptr->u_id;
                    found = true;
                    break;
                }
            }
        }
    }
    if (!found)
        printf("soort, didn't found user: %s\n", name);
    return found;
}

void print_current_user_info(struct usr_ptr *info) {
    if (info) {
        printf("%d\t%s\t%d" ,info->u_id, info->name, info->priority);
    }
}