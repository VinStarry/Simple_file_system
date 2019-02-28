#include <stdio.h>
#include "data_structures.h"
#include "user.h"
#include "super_block.h"
#include "dentry.h"
#include "../include/instruction_handle.h"

//#define __debug_mode

struct usr_ptr *current_usr = NULL;
struct dentry *root_dir = NULL;
struct dentry *current_dir = NULL;
dlist *usr_dir_list = NULL;

int main(int argc, const char *argv[]) {

#ifdef __debug_mode
    root_dir = (struct dentry *)malloc(sizeof(struct dentry));
    root_dir->d_inode = NULL;
    struct super_block *sb = load_block(root_dir);
    struct user_linked_list *head = load_users_info();
    load_entry(root_dir);

//    struct inode *inode1 = (struct inode *)malloc(sizeof(struct inode));
//    alloc_block_for_inode(sb, inode1);
//    alloc_block_for_inode(sb, inode1);
//    alloc_block_for_inode(sb, inode1);
//    alloc_block_for_inode(sb, inode1);
//
//    free_block_for_inode(sb, inode1);
//    free_block_for_inode(sb, inode1);
//    free_block_for_inode(sb, inode1);
//    free_block_for_inode(sb, inode1);
//    alloc_block_for_inode(sb);
//    alloc_data_block(sb);

    save_users_info(head);
    free_user_info(head);
//    save_block(sb);
//    save_entry(root_dir);
    free_block(sb);
    fflush(stdin);
#endif

#ifndef __debug_mode
    struct super_block *sb = NULL;
    root_dir = (struct dentry *)malloc(sizeof(struct dentry));
    if (argc == 1) {
        sb = load_block(root_dir);
    }
    else {
        sb = init_block(root_dir);
    }
    struct user_linked_list *head = load_users_info();
    load_entry(root_dir, sb);

    current_usr = (struct usr_ptr *)malloc(sizeof(current_usr));
    current_dir = root_dir;

    usr_dir_list = init_dlist();
    packet_user_dlist(usr_dir_list, head, root_dir);

    char init_user_name[USER_NAME_MAX_LEN];
    bool logon = false;
    while (!logon) {
        printf("please input user name!\n");
        fgets(init_user_name, USER_NAME_MAX_LEN, stdin);
        init_user_name[strlen(init_user_name) - 1] = '\0';
        logon = get_user_by_name(head, current_usr, init_user_name);
    }

    current_dir = change_home_dir(usr_dir_list, current_usr);

    bool endSignal = false;

    while (!endSignal) {
        char line[LINE_MAX_LEN];
        char instr[INSTR_MAX_LEN];
        char text_dir[LINE_MAX_LEN];
        char input_usr_name[USER_NAME_MAX_LEN];
        char redundent[LINE_MAX_LEN];
        char option[LINE_MAX_LEN];
        unsigned int input_mode;

        printf("\x1b[32m""%s@vfs\t""\x1b[0m", current_usr->name);
        get_current_path_str(current_dir, text_dir);
        fflush(stdout);

        fgets(line, LINE_MAX_LEN, stdin);
        sscanf(line, "%s", instr);
        instr_type type_instr = raw_instruction_handle(instr);

        switch (type_instr) {
            case __shutdown:
                endSignal = true;
                printf("System shut down by user :%s\n", current_usr->name);
                break;
            case __change__mode:
                if (!strcmp(current_usr->name, "root")) {
                    if (sscanf(line, "%s%u%s", input_usr_name, &input_mode, input_usr_name) == 3)
                        chmod_handle(current_dir, input_mode, input_usr_name);
                    else
                        type_instr = __error_instr;
                }
                else {
                    printf("permission denied!\n");
                }
                break;
            case __swap_user:
                if (sscanf(line, "%s%s%s", input_usr_name, input_usr_name, redundent) == 2) {
                    if (get_user_by_name(head, current_usr, input_usr_name) == true)
                        current_dir = change_home_dir(usr_dir_list, current_usr);
                }
                break;
            case __stdout_clear:
                system("clear");
                break;
            case __list_file:
                if (sscanf(line, "%s%s", input_usr_name, option) == 1)
                    ls_handle(current_dir, root_dir, 'n');
                else if (strlen(option) > 1)
                    ls_handle(current_dir, current_dir, option[1]);
                else
                    type_instr = __error_instr;
                break;
            case __change_directory:
                if (sscanf(line, "%s%s", input_usr_name, redundent) == 2)
                    current_dir = cd_handle(current_dir, redundent);
                else
                    type_instr = __error_instr;
                break;
            case __error_instr:
                break;
            default:
                printf("Some unknown error occurs!\n");
                break;
        }
        if (type_instr == __error_instr)
            printf("Cannot resolve instruction %s\n", instr);
    }

    save_users_info(head);
    free_user_info(head);
    save_block(sb);
    save_entry(root_dir, sb);
    free_block(sb);
    fflush(stdin);
#endif
    return 0;
}