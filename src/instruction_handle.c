//
// Created by 永鑫   徐 on 2019-02-27.
//

#include "../include/instruction_handle.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define PRINT_LEN 100

typedef struct ___str__list {
    char *str;
    char type;
    struct ___str__list *next;
}slist;

slist *init_slist(void) {
    slist *sl = (slist *)malloc(sizeof(slist));
    sl->str = NULL;
    sl->next = NULL;
    return sl;
}

void insert_slist(slist *sl, char *str, char type) {
    slist *tmp = sl;
    while (tmp->next) {
        tmp = tmp->next;
    }
    tmp->next = (slist *)malloc(sizeof(slist));
    tmp = tmp->next;
    tmp->str = (char *)malloc(sizeof(char) * PRINT_LEN);
    tmp->type = type;
    strcpy(tmp->str, str);
    tmp->next = NULL;
}

void sort_slist(slist *sl) {
    slist *tmp = sl;
    int len = 0;
    while(tmp->next) {
        tmp = tmp->next;
        len++;
    }
    slist *base = sl;
    slist *min = base, *prev = base;
    for (int i = 0; i < len - 1; i++) {
        bool change = false;
        min = base->next;
        tmp = base;
        for (int j = i; j < len; j++) {
            if (strcmp(tmp->next->str, min->str) < 0) {
                min = tmp->next;
                prev = tmp;
                change = true;
            }
            tmp = tmp->next;
        }
        if (change) {
            prev->next = min->next;
            min->next = base->next;
            base->next = min;
        }
        base = base->next;
    }
}

void free_slist(slist **sl) {
    slist *tmp = *sl;
    slist *prev = *sl;

    while (tmp) {
        prev = tmp;
        tmp = tmp->next;
        free(prev->str);
        free(prev);
    }
    tmp = NULL;
    *sl = NULL;
}

void print_slist(slist *sl) {
    slist *tmp = sl;
    while (tmp->next) {
        tmp = tmp->next;
        if (tmp->type == __directory)
            printf(ANSI_COLOR_BLUE "%s" ANSI_COLOR_RESET "\t", tmp->str);
        else if (tmp->type == __link)
            printf(ANSI_COLOR_GREEN "%s" ANSI_COLOR_RESET "\t", tmp->str);
        else
            printf("%s\t", tmp->str);
    }
    putchar('\n');
}

instr_type raw_instruction_handle(char instr[INSTR_MAX_LEN]) {
    instr_type rtn;
    if (!strcmp(instr, "shutdown"))
        rtn = __shutdown;
    else if (!strcmp(instr, "su"))
        rtn = __swap_user;
    else if (!strcmp(instr, "ls"))
        rtn = __list_file;
    // todo:
    else if (!strcmp(instr, "mkdir"))
        rtn = __make_directory;
    // todo:
    else if (!strcmp(instr, "cp"))
        rtn = __copy_file;
    // todo:
    else if (!strcmp(instr, "ln"))
        rtn = __hard_link;
    else if (!strcmp(instr, "cd"))
        rtn = __change_directory;
    // todo:
    else if (!strcmp(instr, "mv"))
        rtn = __move_file;
    // todo:
    else if (!strcmp(instr, "rm"))
        rtn = __remove_file;
    // todo:
    else if (!strcmp(instr, "edit"))
        rtn = __edit_file;
    else if (!strcmp(instr, "clear"))
        rtn = __stdout_clear;
    else
        rtn = __error_instr;
    return rtn;
}

void ls_handle(struct dentry *dentry, char option) {
    if (option == 'n') {
        slist *str_list = init_slist();
        for (int i = 0; i < HASH_TABLE_ROW; i++) {
            struct dir_hash_table *ptr = dentry->subdirs[i];
            while(ptr->next) {
                ptr = ptr->next;
                insert_slist(str_list, ptr->dname, ptr->corres_dentry->type);
            }
        }
        sort_slist(str_list);
        print_slist(str_list);
        free_slist(&str_list);
    }

}

struct dentry *cd_handle(struct dentry *dentry, const char *path) {
    queue *dir_path = resolve_path_to_queue(path);
    if (dir_path == NULL) {
        printf("cannot resolve path: %s\n", path);
        return dentry;
    }
    struct dentry *temp = dentry;
    if (!strcmp(get_front_queue(dir_path), "/")) {
        while (temp->parent)
            temp = temp->parent;
        dequeue(dir_path);
    }
    while (!queue_empty(dir_path)) {
        char *change_to_str = get_front_queue(dir_path);
        if (!strcmp(".", change_to_str))
            temp = temp;
        else if (!strcmp("..", change_to_str))
            temp = temp->parent;
        else
            temp = search_by_str(temp, change_to_str);
        if (!temp) {
            printf("No such file or directory: %s\n", path);
            return dentry;
        }
        dequeue(dir_path);
    }
    return temp;
}


