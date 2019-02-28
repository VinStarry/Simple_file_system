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

bool str_in_slists(slist *sl, char *str) {
    bool found = false;
    slist *tmp = sl;
    while (tmp->next) {
        tmp = tmp->next;
        if (!strcmp(tmp->str, str)) {
            found = true;
            break;
        }
    }
    return found;
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
    else if (!strcmp(instr, "mkdir"))
        rtn = __make_directory;
    else if (!strcmp(instr, "chmod"))
        rtn = __change__mode;
        // todo:
    else if (!strcmp(instr, "ln"))
        rtn = __hard_link;
    else if (!strcmp(instr, "cd"))
        rtn = __change_directory;
    else if (!strcmp(instr, "rename"))
        rtn = __rename_file;
        // todo:
    else if (!strcmp(instr, "rm"))
        rtn = __remove_file;
        // todo:
    else if (!strcmp(instr, "edit"))
        rtn = __edit_file;
    else if (!strcmp(instr, "clear"))
        rtn = __stdout_clear;
        // todo:
    else if (!strcmp(instr, "cat"))
        rtn = __cat_file;
    else
        rtn = __error_instr;
    return rtn;
}

void ls_handle(struct dentry *dentry, struct dentry *begin_dentry, char option, struct user_linked_list *head) {
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
    else if (option == 'l') {
        slist *str_list = init_slist();
        for (int i = 0; i < HASH_TABLE_ROW; i++) {
            struct dir_hash_table *ptr = dentry->subdirs[i];
            while(ptr->next) {
                ptr = ptr->next;
                if (!strcmp(ptr->dname, ".") || !strcmp(ptr->dname, ".."))
                    continue;
                char *buf = (char *)malloc(sizeof(char) * 11);
                str_get_priority(ptr->corres_dentry->d_inode, buf);

                if (ptr->corres_dentry->type == __directory) {
                    buf[0] = __directory;
                    printf("%s\t", buf);
                }
                else if (ptr->corres_dentry->type == __link) {
                    buf[0] = __link;
                    printf("%s\t", buf);
                }
                else {
                    buf[0] = __file;
                    printf("%s\t", buf);
                }

                if (ptr->corres_dentry->type == __directory || ptr->corres_dentry->type == __link)
                    printf("%lu\t%s\t%lu\t", ptr->corres_dentry->d_inode->i_nlink, get_user_by_user_id(head, ptr->corres_dentry->d_inode->i_uid),
                           sizeof(struct inode));
                else
                    printf("%lu\t%s\t%lu\t", ptr->corres_dentry->d_inode->i_nlink, get_user_by_user_id(head, ptr->corres_dentry->d_inode->i_uid)
                            ,                    ptr->corres_dentry->d_inode->i_btyes);
                print_time(ptr->corres_dentry->d_time);
                if (ptr->corres_dentry->type == __directory)
                    printf("\t" ANSI_COLOR_BLUE "%s" ANSI_COLOR_RESET "\n", ptr->dname);
                else if (ptr->corres_dentry->type == __link)
                    printf("\t" ANSI_COLOR_GREEN "%s" ANSI_COLOR_RESET "\n", ptr->dname);
                else
                    printf("\t""%s\n", ptr->dname);
            }
        }
    }
    else if (option == 'R') {
        slist *str_list = init_slist();
        queue *q = init_queue();
        enqueue(begin_dentry, q);
        q->front->aux = 0;
        int last_level = 0;
        struct dentry *cur_entry = begin_dentry;

        size_t num = 0;

        for (int i = 0; i < HASH_TABLE_ROW; i++) {
            struct dir_hash_table *ptr = cur_entry->subdirs[i];
            while (ptr->next) {
                ptr = ptr->next;
                if (!strcmp(ptr->dname, ".") || !strcmp(ptr->dname, ".."))
                    continue;
                num++;
            }
        }

        size_t num_of_first_level = 0;

        while (cur_entry != NULL) {
            struct dentry *temp_save = cur_entry;
            bool found = false;
            for (int i = 0; i < HASH_TABLE_ROW; i++) {
                struct dir_hash_table *ptr = cur_entry->subdirs[i];
                while (ptr->next) {
                    ptr = ptr->next;
                    if (!strcmp(ptr->dname, ".."))
                        continue;
                    if (!strcmp(ptr->dname, "."))
                        continue;
                    if (str_in_slists(str_list, ptr->dname)) {
                        continue;
                    }
                    enqueue(ptr->corres_dentry, q);
                    insert_slist(str_list, ptr->dname, ptr->corres_dentry->type);
                    found = true;
                    last_level++;
                    q->rear->aux = last_level;
                    cur_entry = ptr->corres_dentry;
                    break;
                }
                if (found == true)
                    break;
            }
            if (found == false) {
                cur_entry = temp_save->parent;
                last_level--;
//                hash_table_delete(cur_entry, temp_save);
            }
            if (temp_save == begin_dentry) {
                num_of_first_level++;
                if (num_of_first_level == num) {
                    break;
                }
            }
        }

        free_slist(&str_list);

        while (!queue_empty(q)) {
            for (int i = 0 ; i < q->front->aux; i++) {
                putchar('-');
            }
            if (((struct dentry *)q->front->val)->type == __directory)
                printf(ANSI_COLOR_BLUE "%s" ANSI_COLOR_RESET "\n", ((struct dentry *)q->front->val)->d_iname);
            else if (((struct dentry *)q->front->val)->type == __link)
                printf(ANSI_COLOR_GREEN "%s" ANSI_COLOR_RESET "\n", ((struct dentry *)q->front->val)->d_iname);
            else
                printf("%s\n", ((struct dentry *)q->front->val)->d_iname);
            dequeue(q);
        }
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

void chmod_handle(struct dentry *cur_dir, unsigned int mode_num, char *name) {
    struct dentry *rtn = search_by_str(cur_dir, name);
    rtn->d_inode->mode = priority_get_by_number(mode_num);
}

void str_get_priority(struct inode *inode1, char *buf) {
    char paylod[] = "-rwxrwxrwx";
    const unsigned long mask1 = 0x01;
    unsigned long t = inode1->mode;
    size_t len = strlen(paylod);
    for (int i = 0; i < 9; i++) {
        unsigned long temp = mask1 << i;
        if (((temp & t) >> i) != mask1)
            paylod[len - 1 - i] = '-';
    }
    strcpy(buf, paylod);
}

bool mkdir_handle(struct dentry *parent_dir, const char *dir_name, struct usr_ptr *user, struct super_block *sb) {
    if (search_by_str(parent_dir, dir_name) != NULL) {
        printf("file exists!\n");
        return false;
    }
    else {
        struct dentry *new_dir = (struct dentry *)malloc(sizeof(struct dentry));
        new_dir->d_inode = alloc_inode(sb);
        new_dir->d_inode->i_uid = user->u_id;
        new_dir->d_inode->mode = priority_get_by_usr(user);
        new_dir->d_inode->i_btyes = 0;
        new_dir->d_inode->i_sb = sb;
        new_dir->d_inode->i_blocks = 0;

        if (new_dir->d_inode == NULL)
            return false;
        else {
            new_dir->d_time = get_local_time();
            strcpy(new_dir->d_iname, dir_name);
            new_dir->type = __directory;
            new_dir->parent = parent_dir;
            for (int i = 0; i < HASH_TABLE_ROW; i++) {
                new_dir->subdirs[i] = (struct dir_hash_table *)malloc(sizeof(struct dir_hash_table));
                new_dir->subdirs[i]->dname = NULL;
                new_dir->subdirs[i]->next = NULL;
                new_dir->subdirs[i]->corres_dentry = NULL;
            }
            new_dir->d_sb = sb;
        }

        struct dentry *new_dir_self = (struct dentry *)malloc(sizeof(struct dentry));
        new_dir_self->parent = NULL;
        new_dir_self->d_time = new_dir->d_time;
        new_dir_self->type = __link;
        strcpy(new_dir_self->d_iname, ".");
        new_dir_self->d_inode = new_dir->d_inode;

        new_dir_self->d_inode->i_nlink++;

        hash_table_insert(new_dir, new_dir_self);

        hash_table_insert(parent_dir, new_dir);
        struct dentry *new_dir_parent = (struct dentry *)malloc(sizeof(struct dentry));
        new_dir_parent->parent = NULL;
        new_dir_parent->d_time = parent_dir->d_time;
        new_dir_parent->type = __link;

        strcpy(new_dir_parent->d_iname, "..");
        new_dir_parent->d_inode = parent_dir->d_inode;
        new_dir_parent->d_inode->i_nlink++;

        hash_table_insert(new_dir, new_dir_parent);
    }
    return true;
}

unsigned long priority_get_by_usr(struct usr_ptr *user) {
    if (user->priority == 0)
        return priority_get_by_number(751);
    else if (user->priority == 1)
        return priority_get_by_number(771);
    else
        return priority_get_by_number(777);
}

bool rename_handle(struct dentry *parent_dir, const char *dir_name, const char *new_name) {
    struct dentry *current_dir = search_by_str(parent_dir, dir_name);
    if (current_dir == NULL) {
        printf("file doesn't exist!\n");
        return false;
    }
    else {
        hash_table_delete(parent_dir, current_dir);
        strcpy(current_dir->d_iname, new_name);
        hash_table_insert(parent_dir, current_dir);
    }
    return true;
}