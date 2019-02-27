#include <stdio.h>
#include "data_structures.h"
#include "user.h"
#include "super_block.h"
#include "../include/instruction_handle.h"

struct usr_ptr *current_usr = NULL;

int main(int argc, const char *argv[]) {
    struct super_block *sb = NULL;
    if (argc == 1) {
        sb = load_block();
    }
    else {
        sb = init_block();
    }
    struct user_linked_list *head = load_users_info();
    current_usr = (struct usr_ptr *)malloc(sizeof(current_usr));

    char init_user_name[USER_NAME_MAX_LEN];
    bool logon = false;
    while (!logon) {
        printf("please input user name!\n");
        fgets(init_user_name, USER_NAME_MAX_LEN, stdin);
        init_user_name[strlen(init_user_name) - 1] = '\0';
        logon = get_user_by_name(head, current_usr, init_user_name);
    }

    bool endSignal = false;

    while (!endSignal) {
        char line[LINE_MAX_LEN];
        char instr[INSTR_MAX_LEN];
        char input_usr_name[USER_NAME_MAX_LEN];
        char redundent[LINE_MAX_LEN];

        printf("%s: ", current_usr->name);
        fflush(stdout);

        fgets(line, LINE_MAX_LEN, stdin);
        sscanf(line, "%s", instr);
        instr_type type_instr = raw_instruction_handle(instr);

        switch (type_instr) {
            case __shutdown:
                endSignal = true;
                printf("System shut down by user :%s\n", current_usr->name);
                break;
            case __swap_user:
                if (sscanf(line, "%s%s%s", input_usr_name, input_usr_name, redundent) == 2)
                    get_user_by_name(head, current_usr, input_usr_name);
                break;
            case __error_instr:
                break;
            case __stdout_clear:
                system("clear");
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
    free_block(sb);
    fflush(stdin);
    return 0;
}