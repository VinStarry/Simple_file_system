//
// Created by 永鑫   徐 on 2019-02-27.
//

#ifndef VFS_INSTRUCTION_HANDLE_H
#define VFS_INSTRUCTION_HANDLE_H

#include <string.h>
#include "data_structures.h"
#include "user.h"
#include "dentry.h"

#define INSTR_MAX_LEN 50
#define LINE_MAX_LEN 2048

enum INSTR_TYPE {
    __shutdown, __swap_user, __list_file, __copy_file,
    __hard_link, __change_directory, __move_file, __remove_file,
    __edit_file, __stdout_clear, __make_directory,
    __error_instr,
};

typedef int instr_type;

instr_type raw_instruction_handle(char instr[INSTR_MAX_LEN]);
void ls_handle(struct dentry *dentry, struct dentry *begin_dentry, char option);
struct dentry *cd_handle(struct dentry *dentry, const char *path);

slist *init_slist(void);
void insert_slist(slist *sl, char *str, char type);
void sort_slist(slist *sl);
bool str_in_slists(slist *sl, char *str);
void free_slist(slist **sl);
void print_slist(slist *sl);


#endif //VFS_INSTRUCTION_HANDLE_H
