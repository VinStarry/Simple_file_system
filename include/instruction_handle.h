//
// Created by 永鑫   徐 on 2019-02-27.
//

#ifndef VFS_INSTRUCTION_HANDLE_H
#define VFS_INSTRUCTION_HANDLE_H

#include <string.h>
#include "data_structures.h"
#include "user.h"
#include "dentry.h"
#include "super_block.h"

#define INSTR_MAX_LEN 50
#define LINE_MAX_LEN 2048
#define DEFAULT_FILE_BLK 64

enum INSTR_TYPE {
    __shutdown, __swap_user, __list_file, __rename_file,
    __change_directory, __remove_file,  __change__mode,
    __edit_file, __stdout_clear, __make_directory, __cat_file,
    __error_instr,
};

typedef int instr_type;

instr_type raw_instruction_handle(char instr[INSTR_MAX_LEN]);
void ls_handle(struct dentry *dentry, struct dentry *begin_dentry, char option, struct user_linked_list *head);
struct dentry *cd_handle(struct dentry *dentry, const char *path);
void chmod_handle(struct dentry *cur_dir, unsigned int mode_num, char *name);

slist *init_slist(void);
void insert_slist(slist *sl, char *str, char type);
void sort_slist(slist *sl);
bool str_in_slists(slist *sl, char *str);
void free_slist(slist **sl);
void print_slist(slist *sl);
bool mkdir_handle(struct dentry *parent_dir, const char *dir_name, struct usr_ptr *user, struct super_block *sb);
bool rename_handle(struct dentry *parent_dir, const char *dir_name, const char *new_name);
bool rm_handle(struct dentry *parent_dir, const char *dir_name, struct super_block *sb, struct usr_ptr *user);
bool edit_handle(struct dentry *parent_dir, const char *dir_name, struct super_block *sb, struct usr_ptr *user);
bool cat_handle(struct dentry *parent_dir, const char *dir_name, struct super_block *sb, struct usr_ptr *user);

void str_get_priority(struct inode *inode1, char *buf);
unsigned long priority_get_by_usr(struct usr_ptr *user);
bool permit_write(u_mode_t f_mode, unsigned long priority);
bool permit_read(u_mode_t f_mode, unsigned long priority);

#endif //VFS_INSTRUCTION_HANDLE_H